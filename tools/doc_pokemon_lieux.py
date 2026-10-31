#!/usr/bin/env python3
"""Génère docs/OU-TROUVER-LES-POKEMON.md (guide pour les joueurs, PokemonNative3G) depuis les données du jeu :
rencontres sauvages (src/data/wild_encounters.json, avec méthode, niveaux et %), dons, combats fixes et œufs des
scripts, échanges en jeu, chiens légendaires errants, évolutions et œufs de pension. Ordre du Pokédex national.
Relancer après tout changement de rencontres ou de scripts.
Usage : python tools/doc_pokemon_lieux.py   (depuis la racine du projet)
"""
import glob
import json
import os
import re

OUT = 'docs/OU-TROUVER-LES-POKEMON.md'


def read(p):
    return open(p, encoding='utf-8', errors='ignore').read()


# --- noms -------------------------------------------------------------------------------------------------------
def species_name(sp):
    return NAMES.get(sp, sp[len('SPECIES_'):].title())


NAMES = dict(re.findall(r'\[(SPECIES_\w+)\]\s*=\s*_\("([^"]*)"\)', read('src/data/text/species_names.h')))
ITEM_NAMES = {}
for m in re.finditer(r'\[(ITEM_\w+)\]\s*=\s*\{\s*\.name\s*=\s*_\("([^"]*)"\)', read('src/data/items.h')):
    ITEM_NAMES[m.group(1)] = m.group(2)
dex_order = re.findall(r'^\s*NATIONAL_DEX_(\w+),', read('include/constants/pokedex.h'), re.M)
DEX = ['SPECIES_' + n for n in dex_order if n != 'NONE'][:386]

SECTIONS = {s['id']: s['name'] for s in json.load(open('src/data/region_map/region_map_sections.json', encoding='utf-8'))['map_sections']}
groups = json.load(open('data/maps/map_groups.json', encoding='utf-8'))
MAP_DIR, MAP_REGION, MAP_NAME = {}, {}, {}
for g in groups['group_order']:
    for name in groups[g]:
        j = json.load(open(f'data/maps/{name}/map.json', encoding='utf-8'))
        MAP_DIR[j['id']] = name
        MAP_REGION[name] = 'Kanto' if 'Kanto' in g else 'Hoenn'
        MAP_NAME[name] = SECTIONS.get(j['region_map_section'], name)


def place(map_dir):
    """Nom lisible : section de la carte, plus l'étage ou la partie quand le nom du dossier en dit plus."""
    base = MAP_NAME.get(map_dir, map_dir)
    # Seuls l'étage et la partie (zone Safari) disent quelque chose de plus ; le reste du nom de dossier est anglais
    parts = []
    for word in map_dir.split('_')[1:]:
        if re.fullmatch(r'B?\d+F', word):
            parts.append(word)
        elif word in CARDINAL:
            parts.append(CARDINAL[word])
    return f'{base} ({", ".join(parts)})' if parts else base


CARDINAL = {'North': 'nord', 'South': 'sud', 'East': 'est', 'West': 'ouest', 'Center': 'centre'}


# --- rencontres sauvages ----------------------------------------------------------------------------------------
METHODS = {'land_mons': 'herbes / grotte', 'water_mons': 'Surf', 'rock_smash_mons': 'Éclate-Roc'}
ROD = {'old_rod': 'Canne', 'good_rod': 'Super Canne', 'super_rod': 'Méga Canne'}
found = {}   # espèce -> liste de lignes
wild = json.load(open('src/data/wild_encounters.json', encoding='utf-8'))
for grp in wild['wild_encounter_groups']:
    if grp['label'] != 'gWildMonHeaders':
        continue   # Zone de Combat (Pyramide, Pike) : à part
    fields = {f['type']: f for f in grp['fields']}
    for enc in grp['encounters']:
        mdir = MAP_DIR.get(enc['map'])
        if mdir is None:
            continue
        for key, f in fields.items():
            if key not in enc:
                continue
            rates = f['encounter_rates']
            mons = enc[key]['mons']
            parts = [(METHODS.get(key), range(len(mons)))] if key != 'fishing_mons' else \
                [(ROD[r], idx) for r, idx in f['groups'].items()]
            for label, idx in parts:
                total = sum(rates[i] for i in idx)
                per = {}
                for i in idx:
                    m = mons[i]
                    lo, hi, pc = per.get(m['species'], (99, 0, 0))
                    per[m['species']] = (min(lo, m['min_level']), max(hi, m['max_level']), pc + rates[i])
                for sp, (lo, hi, pc) in per.items():
                    lv = f'N.{lo}' if lo == hi else f'N.{lo}-{hi}'
                    found.setdefault(sp, []).append((MAP_REGION[mdir], place(mdir), f'{label}, {lv}, {round(100 * pc / total)} %'))

# --- dons, combats fixes, légendaires (scripts) : expliqués à la main ----------------------------------------
# (région, lieu, explication). Le générateur vérifie que chaque espèce donnée ou combattue dans un script a son
# explication ici (sinon il s'arrête : à compléter).
L_KANTO = 'après la Ligue de Kanto et le RUBIS et le SAPHIR rendus à CÉLIO (Île 1)'
L_BOTH = 'après les deux Ligues'
GIFT_NOTES = {
    'SPECIES_BULBASAUR': [('Kanto', 'BOURG PALETTE, labo du Prof. Chen', 'cadeau : un des trois starters de Kanto au choix')],
    'SPECIES_CHARMANDER': [('Kanto', 'BOURG PALETTE, labo du Prof. Chen', 'cadeau : un des trois starters de Kanto au choix')],
    'SPECIES_SQUIRTLE': [('Kanto', 'BOURG PALETTE, labo du Prof. Chen', 'cadeau : un des trois starters de Kanto au choix')],
    'SPECIES_TREECKO': [('Hoenn', 'ROUTE 101, sac du Prof. Seko', 'cadeau : un des trois starters de Hoenn au choix')],
    'SPECIES_TORCHIC': [('Hoenn', 'ROUTE 101, sac du Prof. Seko', 'cadeau : un des trois starters de Hoenn au choix')],
    'SPECIES_MUDKIP': [('Hoenn', 'ROUTE 101, sac du Prof. Seko', 'cadeau : un des trois starters de Hoenn au choix')],
    'SPECIES_CHIKORITA': [('Hoenn', 'BOURG-EN-VOL, labo du Prof. Seko', 'cadeau : un des trois starters de Johto au choix, après la Ligue de Hoenn et le Pokédex de Hoenn complété')],
    'SPECIES_CYNDAQUIL': [('Hoenn', 'BOURG-EN-VOL, labo du Prof. Seko', 'cadeau : un des trois starters de Johto au choix, après la Ligue de Hoenn et le Pokédex de Hoenn complété')],
    'SPECIES_TOTODILE': [('Hoenn', 'BOURG-EN-VOL, labo du Prof. Seko', 'cadeau : un des trois starters de Johto au choix, après la Ligue de Hoenn et le Pokédex de Hoenn complété')],
    'SPECIES_EEVEE': [('Kanto', 'CELADOPOLE, toit du Céladon Condos', 'cadeau : Évoli N.25 posé sur la table')],
    'SPECIES_ABRA': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS')],
    'SPECIES_CLEFAIRY': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS')],
    'SPECIES_DRATINI': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS')],
    'SPECIES_SCYTHER': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS')],
    'SPECIES_PINSIR': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS')],
    'SPECIES_PORYGON': [('Kanto', 'CELADOPOLE, boutique de lots du Casino', 'lot contre des JETONS (le plus cher)')],
    'SPECIES_HITMONLEE': [('Kanto', 'SAFRANIA, Dojo', 'cadeau : Kicklee OU Tygnon au choix, après avoir battu le Maître du Dojo (l\'autre : œuf de Debugant à la pension)')],
    'SPECIES_HITMONCHAN': [('Kanto', 'SAFRANIA, Dojo', 'cadeau : Kicklee OU Tygnon au choix, après avoir battu le Maître du Dojo (l\'autre : œuf de Debugant à la pension)')],
    'SPECIES_LAPRAS': [('Kanto', 'SYLPHE SARL, 7e étage', 'cadeau : Lokhlass N.25 d\'un employé, après avoir battu le rival')],
    'SPECIES_MAGIKARP': [('Kanto', 'ROUTE 4, Centre Pokémon', 'achat : Magicarpe à 500₽ chez un vendeur')],
    'SPECIES_OMANYTE': [('Kanto', 'CRAMOIS\'ÎLE, labo (salle des expériences)', 'fossile ressuscité : NAUTILE (Mont Sélénite, choix contre l\'autre fossile)')],
    'SPECIES_KABUTO': [('Kanto', 'CRAMOIS\'ÎLE, labo (salle des expériences)', 'fossile ressuscité : DOME FOSSILE (Mont Sélénite, choix contre l\'autre fossile)')],
    'SPECIES_AERODACTYL': [('Kanto', 'CRAMOIS\'ÎLE, labo (salle des expériences)', 'fossile ressuscité : VIEIL AMBRE (Musée d\'Argenta)')],
    'SPECIES_LILEEP': [('Hoenn', 'MEROUVILLE, Devon SARL 2e étage', 'fossile ressuscité : FOSSILE RACINE (Désert de la Route 111, choix contre l\'autre)')],
    'SPECIES_ANORITH': [('Hoenn', 'MEROUVILLE, Devon SARL 2e étage', 'fossile ressuscité : FOSSILE GRIFFE (Désert de la Route 111, choix contre l\'autre)')],
    'SPECIES_CASTFORM': [('Hoenn', 'ROUTE 119, Institut Météo 2e étage', 'cadeau : Morphéo N.25 après avoir chassé la Team Aqua')],
    'SPECIES_BELDUM': [('Hoenn', 'ALGATIA, maison de Pierre', 'cadeau : Terhal N.5 laissé par Pierre, après la Ligue de Hoenn')],
    'SPECIES_WYNAUT': [('Hoenn', 'VERMILAVA', 'œuf offert par une vieille dame (aussi : œuf de Qulbutoké à la pension, parent tenant ENCENS DOUX)')],
    'SPECIES_TOGEPI': [('Kanto', 'ÎLE 5, Labyrinthe d\'Eau', 'œuf offert par le vieil homme si le Pokémon en tête d\'équipe l\'aime beaucoup')],
    'SPECIES_ELECTRODE': [('Hoenn', 'REPAIRE AQUA', 'combat fixe : les « objets » Électrode'), ('Kanto', 'CENTRALE', 'combat fixe : les « objets » Électrode')],
    'SPECIES_VOLTORB': [('Hoenn', 'NEW LAVERRE', 'combat fixe : les « objets » Voltorbe')],
    'SPECIES_SUDOWOODO': [('Hoenn', 'ZONE DE COMBAT (est)', 'combat fixe : l\'arbre bizarre, avec l\'ARROSOIR WAILMER')],
    'SPECIES_KECLEON': [('Hoenn', 'ROUTE 119 / ROUTE 120', 'combat fixe : Kecleon invisibles, révélés avec le DEVON SCOPE')],
    'SPECIES_SNORLAX': [('Kanto', 'ROUTE 12 et ROUTE 16', 'combat fixe : les deux Ronflex endormis, réveillés à la POKé FLÛTE')],
    'SPECIES_MAROWAK': [('Kanto', 'TOUR POKéMON, 6e étage', 'combat fixe : le SPECTRE (avec le SCOPE SYLPHE) ; non capturable, comme dans RF')],
    'SPECIES_HYPNO': [('Kanto', 'ÎLE 3, Forêt Baies', 'combat fixe : Hypnomade qui a enlevé la petite fille')],
    # Légendaires
    'SPECIES_ARTICUNO': [('Kanto', 'ÎLES ÉCUME (B4F)', 'légendaire, N.50 : au fond, Surf et Force pour arrêter les courants')],
    'SPECIES_ZAPDOS': [('Kanto', 'CENTRALE (Route 10)', 'légendaire, N.50 : accès par Surf')],
    'SPECIES_MOLTRES': [('Kanto', 'MONT BRAISE, sommet (Île 1)', 'légendaire, N.50 : accès aux Îles Sevii après la Ligue de Kanto')],
    'SPECIES_MEWTWO': [('Kanto', 'CAVERNE AZURÉE (B1F)', 'légendaire, N.70 : la caverne s\'ouvre ' + L_KANTO)],
    'SPECIES_RAIKOU': [('Kanto', 'routes de Kanto', 'légendaire errant, N.50 : apparaît ' + L_KANTO + ' ; les trois chiens errent en même temps')],
    'SPECIES_ENTEI': [('Kanto', 'routes de Kanto', 'légendaire errant, N.50 : apparaît ' + L_KANTO + ' ; les trois chiens errent en même temps')],
    'SPECIES_SUICUNE': [('Kanto', 'routes de Kanto', 'légendaire errant, N.50 : apparaît ' + L_KANTO + ' ; les trois chiens errent en même temps')],
    'SPECIES_REGIROCK': [('Hoenn', 'RUINES DU DÉSERT (Route 111)', 'légendaire, N.40 : déchiffrer le braille du CAVEAU SCELLÉ (Plongée, Route 134) avec Relicanth et Wailord dans l\'équipe')],
    'SPECIES_REGICE': [('Hoenn', 'GROTTE DE L\'ÎLE (Route 105)', 'légendaire, N.40 : CAVEAU SCELLÉ ouvert, puis faire le tour de la salle (braille)')],
    'SPECIES_REGISTEEL': [('Hoenn', 'TOMBEAU ANCIEN (Route 120)', 'légendaire, N.40 : CAVEAU SCELLÉ ouvert, puis Vol au centre de la salle (braille)')],
    'SPECIES_GROUDON': [('Hoenn', 'GROTTE TERRESTRE', 'légendaire, N.70 : après la Ligue de Hoenn ; l\'entrée change de route, les infos sont à l\'Institut Météo')],
    'SPECIES_KYOGRE': [('Hoenn', 'GROTTE MARINE', 'légendaire, N.70 : après la Ligue de Hoenn ; l\'entrée (sous l\'eau) change de route, infos à l\'Institut Météo')],
    'SPECIES_RAYQUAZA': [('Hoenn', 'PILIER CÉLESTE (sommet)', 'légendaire, N.70 : après la Ligue de Hoenn, VÉLO CROSS pour les sols fragiles')],
    'SPECIES_LATIAS': [('Hoenn', 'routes de Hoenn', 'légendaire errant, N.40 : après la Ligue de Hoenn, choisi à la télé de la maison (ROUGE = Latias)'),
                       ('Hoenn', 'ÎLE DU SUD', 'légendaire, N.50 : l\'autre du duo, avec le PASSE EON (CADEAU MYSTÈRE), ferry de Nénucrique')],
    'SPECIES_LATIOS': [('Hoenn', 'routes de Hoenn', 'légendaire errant, N.40 : après la Ligue de Hoenn, choisi à la télé de la maison (BLEU = Latios)'),
                       ('Hoenn', 'ÎLE DU SUD', 'légendaire, N.50 : l\'autre du duo, avec le PASSE EON (CADEAU MYSTÈRE), ferry de Nénucrique')],
    'SPECIES_MEW': [('Hoenn', 'ÎLE LOINTAINE', 'légendaire, N.30 : VIEILLE CARTE (CADEAU MYSTÈRE), ferry de Nénucrique ; Mew se cache dans les herbes')],
    'SPECIES_LUGIA': [('Kanto', 'ROC NOMBRI (en bas)', 'légendaire, N.70 : TICKET MYSTIK (CADEAU MYSTÈRE), ferry de Nénucrique ou de Carmin sur Mer')],
    'SPECIES_HO_OH': [('Kanto', 'ROC NOMBRI (sommet)', 'légendaire, N.70 : TICKET MYSTIK (CADEAU MYSTÈRE), ferry de Nénucrique ou de Carmin sur Mer')],
    'SPECIES_DEOXYS': [('Kanto', 'ÎLE AURORE', 'légendaire, N.30 : TICKET AURORA (CADEAU MYSTÈRE), ferry de Nénucrique ou de Carmin sur Mer ; résoudre le triangle')],
    'SPECIES_CELEBI': [('Kanto', 'FORÊT BAIES (Île 3)', 'légendaire, N.30 : ' + L_BOTH + ', examiner l\'autel en bois en haut à droite ; vaincu = parti, fuite = il revient')],
    'SPECIES_JIRACHI': [('Hoenn', 'CHUTES MÉTÉORE (B1F, salle de la CT Dracogriffe)', 'légendaire, N.30 : ' + L_BOTH + ' (flash spécial à la télé), Surf + Cascade, jouer de la POKé FLÛTE devant la météorite')],
    'SPECIES_FEEBAS': [('Hoenn', 'ROUTE 119', 'pêche : seulement sur 6 cases d\'eau secrètes de la rivière (elles changent avec les tendances de Nénucrique)')],
}
FUSION_EGGS = 'cadeau : œuf de l\'assistant de la pension (Route 117 à Hoenn, Île 4 à Kanto), après la Ligue de la région, si jamais attrapé'
for sp in ('SPECIES_BULBASAUR', 'SPECIES_CHARMANDER', 'SPECIES_SQUIRTLE', 'SPECIES_TREECKO', 'SPECIES_TORCHIC',
           'SPECIES_MUDKIP', 'SPECIES_CHIKORITA', 'SPECIES_CYNDAQUIL', 'SPECIES_TOTODILE'):
    GIFT_NOTES[sp].append(('', 'pensions', FUSION_EGGS))

GIFT = re.compile(r'^\s*(?:givemon|giveegg|setwildbattle|seteventmon)\s+(SPECIES_\w+)|^\s*setvar\s+VAR_TEMP_1,\s*(SPECIES_\w+)', re.M)
scripted = set()
for f in glob.glob('data/**/maps/*/scripts.inc', recursive=True):
    for m in GIFT.finditer(read(f)):
        scripted.add(m.group(1) or m.group(2))
unexplained = sorted(scripted - set(GIFT_NOTES))
assert not unexplained, 'dons de scripts sans explication (GIFT_NOTES) : %s' % unexplained
for sp, rows in GIFT_NOTES.items():
    found.setdefault(sp, []).extend(rows)

# --- échanges en jeu (avec le lieu : la carte dont le script lance l'échange) -----------------------------------
trade_place = {}
for f in glob.glob('data/**/maps/*/scripts.inc', recursive=True):
    mdir = f.replace(os.sep, '/').split('/maps/')[1].split('/')[0]
    for t in re.findall(r'\b(?:KANTO_)?INGAME_TRADE_(\w+)', read(f)):
        trade_place[t] = mdir
for p in ('src/data/trade.h', 'src/data/kanto_ingame_trades_entries.h'):
    for key, blk in re.findall(r'\[(?:KANTO_)?INGAME_TRADE_(\w+)\]\s*=\s*\{(.*?)\n    \}', read(p), re.S):
        g = re.search(r'\.species\s*=\s*(SPECIES_\w+)', blk)
        r = re.search(r'\.requestedSpecies\s*=\s*(SPECIES_\w+)', blk)
        if g and r:
            mdir = trade_place.get(key)
            where = place(mdir) if mdir else 'échange en jeu'
            region = MAP_REGION.get(mdir, 'Kanto' if 'kanto' in p else 'Hoenn')
            found.setdefault(g.group(1), []).append((region, where, f'échange : donner un {species_name(r.group(1))}'))

# --- évolutions et œufs -----------------------------------------------------------------------------------------
EVO_TEXT = {
    'EVO_LEVEL': lambda p: f'niveau {p}', 'EVO_ITEM': lambda p: ITEM_NAMES.get(p, p),
    'EVO_FRIENDSHIP': lambda p: 'bonheur', 'EVO_FRIENDSHIP_DAY': lambda p: 'bonheur, le jour (6 h - 20 h)',
    'EVO_FRIENDSHIP_NIGHT': lambda p: 'bonheur, la nuit (20 h - 6 h)', 'EVO_TRADE': lambda p: 'CÂBLE LINK',
    'EVO_TRADE_ITEM': lambda p: f'CÂBLE LINK en tenant {ITEM_NAMES.get(p, p)}', 'EVO_BEAUTY': lambda p: f'beauté {p}',
    'EVO_LEVEL_ATK_GT_DEF': lambda p: f'niveau {p}, Attaque > Défense',
    'EVO_LEVEL_ATK_LT_DEF': lambda p: f'niveau {p}, Attaque < Défense',
    'EVO_LEVEL_ATK_EQ_DEF': lambda p: f'niveau {p}, Attaque = Défense',
    'EVO_LEVEL_SILCOON': lambda p: f'niveau {p} (selon la personnalité)', 'EVO_LEVEL_CASCOON': lambda p: f'niveau {p} (selon la personnalité)',
    'EVO_LEVEL_NINJASK': lambda p: f'niveau {p}', 'EVO_LEVEL_SHEDINJA': lambda p: f'niveau {p}, place libre et POKé BALL dans le sac',
}
evolves_from = {}
# Une entrée par espèce, éventuellement sur plusieurs lignes (Évoli, Ortide…) : jusqu'à l'entrée suivante
for m in re.finditer(r'\[(SPECIES_\w+)\]\s*=\s*(.*?)(?=\n\s*\[SPECIES_|\n\};)', read('src/data/pokemon/evolution.h'), re.S):
    for e in re.finditer(r'\{(EVO_\w+),\s*(\w+),\s*(SPECIES_\w+)\}', m.group(2)):
        evolves_from.setdefault(e.group(3), []).append((m.group(1), EVO_TEXT.get(e.group(1), lambda p: e.group(1))(e.group(2))))
# Bébés : œuf d'un parent (pension), avec l'encens quand il le faut
BABIES = {'SPECIES_PICHU': 'SPECIES_PIKACHU', 'SPECIES_CLEFFA': 'SPECIES_CLEFAIRY', 'SPECIES_IGGLYBUFF': 'SPECIES_JIGGLYPUFF',
          'SPECIES_TOGEPI': None, 'SPECIES_TYROGUE': 'SPECIES_HITMONLEE', 'SPECIES_SMOOCHUM': 'SPECIES_JYNX',
          'SPECIES_ELEKID': 'SPECIES_ELECTABUZZ', 'SPECIES_MAGBY': 'SPECIES_MAGMAR', 'SPECIES_AZURILL': 'SPECIES_MARILL',
          'SPECIES_WYNAUT': 'SPECIES_WOBBUFFET'}
INCENSE = {'SPECIES_AZURILL': 'ENCENS MER', 'SPECIES_WYNAUT': 'ENCENS DOUX'}
for baby, parent in BABIES.items():
    if parent:
        what = f'œuf de {species_name(parent)} à la pension'
        if baby == 'SPECIES_TYROGUE':
            what = 'œuf de Kicklee, Tygnon ou Kapoera à la pension'
        if baby in INCENSE:
            what += f' (parent tenant {INCENSE[baby]})'
        found.setdefault(baby, []).append(('', 'pension', what))

# --- écriture ---------------------------------------------------------------------------------------------------
out = ['# Où trouver les Pokémon (PokemonNative3G)', '',
       'Guide généré depuis les données du jeu (`tools/doc_pokemon_lieux.py`). Pour chaque Pokémon : lieux de '
       'rencontre (méthode, niveaux, chance d\'apparition), dons, combats fixes, échanges en jeu, puis comment '
       'l\'obtenir par évolution. Les évolutions par échange se font seul avec le CÂBLE LINK (vendu 2100₽ dans '
       'toutes les boutiques). Pas de Johto : ses Pokémon se trouvent à Hoenn et à Kanto (Zone Safari, îles Sevii, '
       'pensions, échanges, chiens errants, Celebi).', '']
missing = []
for n, sp in enumerate(DEX, 1):
    rows = found.get(sp, [])
    evo = evolves_from.get(sp, [])
    out.append(f'## {n:03d} {species_name(sp)}')
    if not rows and not evo:
        missing.append(sp)
        out.append('- (aucune source trouvée par le générateur : à vérifier)')
    for region in ('Hoenn', 'Kanto', ''):
        lines = sorted(set((p, w) for r, p, w in rows if r == region))
        for p, w in lines:
            out.append(f'- {region + " · " if region else ""}{p} : {w}')
    for src, how in evo:
        out.append(f'- évolution de {species_name(src)} ({how})')
    out.append('')
open(OUT, 'w', encoding='utf-8', newline='\n').write('\n'.join(out))
print(OUT, ':', len(DEX), 'Pokémon,', len(missing), 'sans source :', ' '.join(missing))
