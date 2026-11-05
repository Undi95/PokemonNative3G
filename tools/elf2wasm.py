#!/usr/bin/env python3
"""Convertit les données assemblées (objets ELF 32 bits de GNU as) en objets WebAssembly (version navigateur).

Les scripts, cartes et autres tables de data/ (et les musiques, sound/songs/midi) sont écrits pour GNU as, avec des
macros que l'assembleur de clang ne sait pas évaluer. Comme pour macOS (tools/elf2macho), on les assemble avec GNU as,
en 32 bits (as --32 : pointeurs de 4 octets, ceux de wasm32), puis cet outil les convertit (docs/NAVIGATEUR.md) :

- chaque section ELF (allouée) devient un segment de données wasm, d'un seul tenant (un script peut continuer dans
  le label suivant) ; ses octets sont repris tels quels (.incbin d'un fichier .bin écrit à côté) ;
- chaque symbole (label) devient un symbole de données au même endroit du segment ;
- chaque pointeur (relocation R_386_32, addend implicite dans les octets) devient `.int32 cible+addend` : relocation
  R_WASM_MEMORY_ADDR_I32 vers une donnée, ou R_WASM_TABLE_INDEX_I32 vers une fonction C (special, callnative...).
  Une fonction référencée doit être déclarée avec sa signature exacte (.functype), sinon wasm-ld la remplace par un
  piège : les signatures sont relevées dans les objets C déjà compilés (sections type, import, function et la table
  des symboles de la section « linking »).

Le texte produit (assembleur wasm de LLVM) est assemblé par emcc. Usage (règle de lien `make web`, Makefile) :
    elf2wasm.py --sigs SIGS.txt --cc emcc --jobs N --c-objs LISTE_C.txt -- donnees1.o donnees2.o ...
écrit donnees1.o.wasm.o, etc. Un objet n'est reconverti que s'il est plus récent que sa sortie ou si les signatures
des fonctions qu'il référence ont changé.
"""
import argparse
import concurrent.futures
import os
import re
import struct
import subprocess
import sys

# --- ELF 32 bits ------------------------------------------------------------------------------------------------

SHT_PROGBITS, SHT_SYMTAB, SHT_NOBITS, SHT_REL, SHT_RELA = 1, 2, 8, 9, 4
SHF_WRITE, SHF_ALLOC = 0x1, 0x2
SHN_UNDEF, SHN_ABS, SHN_COMMON = 0, 0xFFF1, 0xFFF2
STB_LOCAL, STB_GLOBAL, STB_WEAK = 0, 1, 2
STT_SECTION, STT_FILE = 3, 4
R_386_NONE, R_386_32 = 0, 1


class Section:
    def __init__(self, index, name, typ, flags, offset, size, link, info, align):
        self.index, self.name, self.type, self.flags = index, name, typ, flags
        self.offset, self.size, self.link, self.info, self.align = offset, size, link, info, align


class Symbol:
    def __init__(self, name, value, size, bind, typ, other, shndx):
        self.name, self.value, self.size, self.bind, self.type, self.other, self.shndx = \
            name, value, size, bind, typ, other, shndx


def lire_elf(chemin):
    data = open(chemin, 'rb').read()
    if data[:4] != b'\x7fELF' or data[4] != 1 or data[5] != 1:
        raise SystemExit('%s : pas un objet ELF 32 bits petit-boutiste' % chemin)
    shoff, = struct.unpack_from('<I', data, 0x20)
    shentsize, shnum, shstrndx = struct.unpack_from('<HHH', data, 0x2E)
    brutes = [struct.unpack_from('<10I', data, shoff + i * shentsize) for i in range(shnum)]
    noms = brutes[shstrndx]

    def chaine(table_off, off):
        fin = data.index(b'\0', table_off + off)
        return data[table_off + off:fin].decode('latin-1')

    sections = [Section(i, chaine(noms[4], b[0]), b[1], b[2], b[4], b[5], b[6], b[7], b[8])
                for i, b in enumerate(brutes)]
    symboles = []
    rels = {}
    for s in sections:
        if s.type == SHT_SYMTAB:
            strtab = sections[s.link]
            for i in range(s.size // 16):
                n, v, sz, info, other, shndx = struct.unpack_from('<IIIBBH', data, s.offset + i * 16)
                symboles.append(Symbol(chaine(strtab.offset, n), v, sz, info >> 4, info & 15, other, shndx))
        elif s.type == SHT_RELA:
            raise SystemExit('%s : relocations RELA inattendues (%s)' % (chemin, s.name))
    for s in sections:
        if s.type == SHT_REL:
            liste = rels.setdefault(s.info, [])
            for i in range(s.size // 8):
                off, info = struct.unpack_from('<II', data, s.offset + i * 8)
                liste.append((off, info >> 8, info & 0xFF))
    return data, sections, symboles, rels


# --- Objets wasm (signatures des fonctions C) -------------------------------------------------------------------

VALTYPES = {0x7F: 'i32', 0x7E: 'i64', 0x7D: 'f32', 0x7C: 'f64', 0x7B: 'v128'}


def leb(data, pos):
    res = shift = 0
    while True:
        b = data[pos]
        pos += 1
        res |= (b & 0x7F) << shift
        shift += 7
        if not b & 0x80:
            return res, pos


def nom_wasm(data, pos):
    n, pos = leb(data, pos)
    return data[pos:pos + n].decode('utf-8'), pos + n


def signatures_objet(chemin):
    """{fonction globale définie : '(i32, i32) -> (i32)'} d'un objet wasm (relocatable) produit par clang."""
    data = open(chemin, 'rb').read()
    if data[:4] != b'\0asm':
        raise SystemExit('%s : pas un objet wasm' % chemin)
    pos = 8
    types, fonctions, nb_importees = [], [], 0
    sigs = {}
    while pos < len(data):
        sid = data[pos]
        taille, pos = leb(data, pos + 1)
        fin = pos + taille
        if sid == 1:  # types
            n, p = leb(data, pos)
            for _ in range(n):
                if data[p] != 0x60:
                    raise SystemExit('%s : type de fonction inconnu' % chemin)
                np_, p = leb(data, p + 1)
                params = [VALTYPES[data[p + i]] for i in range(np_)]
                p += np_
                nr, p = leb(data, p)
                res = [VALTYPES[data[p + i]] for i in range(nr)]
                p += nr
                types.append('(%s) -> (%s)' % (', '.join(params), ', '.join(res)))
        elif sid == 2:  # imports
            n, p = leb(data, pos)
            for _ in range(n):
                _, p = nom_wasm(data, p)
                _, p = nom_wasm(data, p)
                kind = data[p]
                p += 1
                if kind == 0:
                    _, p = leb(data, p)
                    nb_importees += 1
                elif kind == 1:  # table : type, limites
                    p += 1
                    fl, p = leb(data, p)
                    _, p = leb(data, p)
                    if fl & 1:
                        _, p = leb(data, p)
                elif kind == 2:  # mémoire : limites
                    fl, p = leb(data, p)
                    _, p = leb(data, p)
                    if fl & 1:
                        _, p = leb(data, p)
                elif kind == 3:  # global : type, mutabilité
                    p += 2
                elif kind == 4:  # tag
                    p += 1
                    _, p = leb(data, p)
        elif sid == 3:  # fonctions définies : index de type
            n, p = leb(data, pos)
            for _ in range(n):
                t, p = leb(data, p)
                fonctions.append(t)
        elif sid == 0:  # section personnalisée
            nom, p = nom_wasm(data, pos)
            if nom == 'linking':
                _, p = leb(data, p)  # version
                while p < fin:
                    sous, p = data[p], p + 1
                    long_, p = leb(data, p)
                    sfin = p + long_
                    if sous == 8:  # table des symboles
                        n, q = leb(data, p)
                        for _ in range(n):
                            kind = data[q]
                            flags, q = leb(data, q + 1)
                            undefined = flags & 0x10
                            if kind in (0, 2, 4, 5):
                                index, q = leb(data, q)
                                nom_s = None
                                if not undefined or flags & 0x40:
                                    nom_s, q = nom_wasm(data, q)
                                if kind == 0 and not undefined and not flags & 0x2 and nom_s is not None:
                                    sigs[nom_s] = types[fonctions[index - nb_importees]]
                            elif kind == 1:
                                _, q = nom_wasm(data, q)
                                if not undefined:
                                    for _ in range(3):
                                        _, q = leb(data, q)
                            elif kind == 3:
                                _, q = leb(data, q)
                    p = sfin
        pos = fin
    return sigs


# --- Conversion -------------------------------------------------------------------------------------------------

NOM_SIMPLE = re.compile(r'^[A-Za-z_.][A-Za-z0-9_.$]*$')


def nom_asm(nom):
    return nom if NOM_SIMPLE.match(nom) else '"%s"' % nom.replace('\\', '\\\\').replace('"', '\\"')


def convertir(entree, sortie_s, sigs):
    """Écrit le texte assembleur wasm de l'objet ELF `entree` (et ses .bin) ; renvoie les fonctions référencées."""
    data, sections, symboles, rels = lire_elf(entree)
    base = os.path.basename(entree)
    jeton = re.sub(r'[^A-Za-z0-9_]', '_', os.path.relpath(entree))
    allouees = [s for s in sections if s.flags & SHF_ALLOC and s.type in (SHT_PROGBITS, SHT_NOBITS)]
    par_section = {}
    for sym in symboles:
        if sym.type in (STT_SECTION, STT_FILE) or not sym.name or sym.shndx in (SHN_UNDEF, SHN_ABS):
            continue
        if sym.shndx == SHN_COMMON:
            raise SystemExit('%s : symbole COMMON %s' % (entree, sym.name))
        par_section.setdefault(sym.shndx, []).append(sym)
    lignes = []
    fonctions = set()

    def cible(sym_index, addend, ou):
        sym = symboles[sym_index]
        if sym.shndx == SHN_ABS:
            return None, (sym.value + addend) & 0xFFFFFFFF
        if sym.shndx == SHN_UNDEF:
            if sym.name in sigs:
                if addend != 0:
                    raise SystemExit('%s : pointeur vers la fonction %s + %d (%s)' % (entree, sym.name, addend, ou))
                fonctions.add(sym.name)
                return nom_asm(sym.name), None
            return nom_asm(sym.name) + ('%+d' % addend if addend else ''), None
        # Défini dans cet objet : par le symbole de début de sa section
        off = (sym.value if sym.type != STT_SECTION else 0) + addend
        return '__e2w_%s_%d' % (jeton, sym.shndx) + ('%+d' % off if off else ''), None

    for s in allouees:
        nom_sec = '__e2w_%s_%d' % (jeton, s.index)
        prefixe = '.bss' if s.type == SHT_NOBITS else ('.data' if s.flags & SHF_WRITE else '.rodata')
        lignes.append('\t.section\t%s.%s,"",@' % (prefixe, nom_sec))
        align = max(s.align, 1)
        lignes.append('\t.p2align\t%d' % (align.bit_length() - 1))
        syms = sorted(par_section.get(s.index, []), key=lambda x: x.value)
        offsets = sorted({x.value for x in syms} | {s.size})
        relocs = {}
        for off, si, typ in rels.get(s.index, []):
            if typ == R_386_NONE:
                continue
            if typ != R_386_32:
                raise SystemExit('%s : relocation de type %d dans %s+0x%x' % (entree, typ, s.name, off))
            relocs[off] = si
        # Les octets de la section, dans un fichier à part (inclus par .incbin)
        if s.type == SHT_PROGBITS and s.size:
            binaire = sortie_s + '.%d.bin' % s.index
            with open(binaire, 'wb') as f:
                f.write(data[s.offset:s.offset + s.size])
            chemin_bin = os.path.abspath(binaire).replace('\\', '/')
        lignes.append('%s:' % nom_sec)
        coupures = sorted(set(offsets) | set(relocs) | {o + 4 for o in relocs})
        par_offset = {}
        for sym in syms:
            par_offset.setdefault(sym.value, []).append(sym)
        pos = 0
        for c in coupures:
            if c > s.size:
                break
            if c > pos:
                if s.type == SHT_NOBITS:
                    lignes.append('\t.skip\t%d' % (c - pos))
                else:
                    lignes.append('\t.incbin\t"%s", %d, %d' % (chemin_bin, pos, c - pos))
                pos = c
            for sym in par_offset.get(c, []):
                nom = nom_asm(sym.name)
                if sym.bind == STB_GLOBAL:
                    lignes.append('\t.globl\t%s' % nom)
                elif sym.bind == STB_WEAK:
                    lignes.append('\t.weak\t%s' % nom)
                if sym.other & 3 == 2:
                    lignes.append('\t.hidden\t%s' % nom)
                lignes.append('\t.type\t%s,@object' % nom)
                lignes.append('%s:' % nom)
            if c in relocs and c < s.size:
                if s.type == SHT_NOBITS:
                    raise SystemExit('%s : relocation dans une section vide %s' % (entree, s.name))
                addend, = struct.unpack_from('<i', data, s.offset + c)
                texte, valeur = cible(relocs[c], addend, '%s+0x%x' % (s.name, c))
                lignes.append('\t.int32\t%s' % (texte if texte is not None else '0x%x' % valeur))
                pos = c + 4
        # Tailles : jusqu'au symbole suivant (ou la fin de la section)
        for sym in syms:
            suivant = next(o for o in offsets if o > sym.value) if sym.value < s.size else s.size
            lignes.append('\t.size\t%s, %d' % (nom_asm(sym.name), suivant - sym.value))
        lignes.append('\t.size\t%s, %d' % (nom_sec, s.size))
    for f in sorted(fonctions):
        lignes.append('\t.functype\t%s %s' % (nom_asm(f), sigs[f]))
    with open(sortie_s, 'w', encoding='utf-8') as f:
        f.write('# %s, converti par tools/elf2wasm.py\n' % base)
        f.write('\n'.join(lignes) + '\n')
    return fonctions


def tache(entree, cc, sigs, forcer):
    sortie = entree + '.wasm.o'
    texte = entree + '.wasm.s'
    if not forcer and os.path.exists(sortie) and os.path.getmtime(sortie) >= os.path.getmtime(entree):
        return None
    convertir(entree, texte, sigs)
    r = subprocess.run(cc + ['-c', texte, '-o', sortie], capture_output=True, text=True)
    if r.returncode != 0:
        return '%s :\n%s%s' % (entree, r.stdout, r.stderr)
    return None


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--c-objs', required=True, help='fichier : la liste des objets C (wasm), un par ligne')
    ap.add_argument('--sigs', required=True, help='fichier des signatures relevées (pour ne reconvertir que si besoin)')
    ap.add_argument('--cc', default='emcc', help='assembleur (défaut : emcc)')
    ap.add_argument('--jobs', type=int, default=os.cpu_count())
    ap.add_argument('objets', nargs='+')
    args = ap.parse_args()

    sigs = {}
    for obj in open(args.c_objs).read().split():
        sigs.update(signatures_objet(obj))
    texte = ''.join('%s %s\n' % kv for kv in sorted(sigs.items()))
    ancien = open(args.sigs).read() if os.path.exists(args.sigs) else None
    forcer = ancien != texte
    if forcer:
        with open(args.sigs, 'w') as f:
            f.write(texte)
    cc = args.cc.split()
    erreurs = []
    with concurrent.futures.ThreadPoolExecutor(max_workers=args.jobs) as ex:
        for err in ex.map(lambda o: tache(o, cc, sigs, forcer), args.objets):
            if err:
                erreurs.append(err)
    if erreurs:
        sys.stderr.write('\n'.join(erreurs))
        sys.exit(1)


if __name__ == '__main__':
    main()
