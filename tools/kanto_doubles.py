#!/usr/bin/env python3
"""Objets donnés deux fois, derniers cas (PokemonNative3G, 2026-10-24). Relançable.
- Météorite de Kanto : icône rougeâtre (palette dérivée de celle d'Émeraude).
- PASSE BATEAU de Kanto -> PASS OCEANE (ITEM_OCEAN_PASS, image et description de RF).
- Cherch'Objet de l'assistant de la Route 11 -> AUTO-REPOUSSE (ITEM_AUTO_REPEL) : quand un REPOUSSE se dissipe,
  propose d'en utiliser un autre du sac (data/scripts/repel.inc, src/fusion_events.c).
- Boîte Jetons (Céladopole) : l'homme a tout perdu ; easter-egg 9999 jetons -> LEVEINARD chromatique.
- Pot Poudre (Azuria) : avec celui de Hoenn, assortiment de baies ; sinon il indique Poivressel.
Usage : python tools/kanto_doubles.py   (depuis la racine du projet)
"""
import colorsys, json, re, shutil

RF = '../decomps/pokerougefeu/'


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b, cnt=1):
    t = rd(p)
    if '\r\n' in t:
        a = a.replace('\n', '\r\n'); b = b.replace('\n', '\r\n')
    if b in t:
        return
    assert t.count(a) == cnt, (p, a[:80], t.count(a))
    wr(p, t.replace(a, b))


def set_text(p, label, body):
    """Remplace le texte d'un label (jusqu'au $)."""
    t = rd(p)
    m = re.search(r'(^%s::?\s*\n)(.*?\$"\s*\n)' % re.escape(label), t, re.M | re.S)
    assert m, (p, label)
    nl = '\r\n' if '\r\n' in t else '\n'
    wr(p, t[:m.start(2)] + body.replace('\n', nl) + nl + t[m.end(2):])


# ---------- objets ----------
once('include/constants/items.h', '#define ITEM_KANTO_METEORITE 379\n\n#define ITEMS_COUNT 380\n',
     '#define ITEM_KANTO_METEORITE 379\n#define ITEM_OCEAN_PASS 380\n#define ITEM_AUTO_REPEL 381\n\n#define ITEMS_COUNT 382\n')
once('src/data/text/item_descriptions.h', 'static const u8 sRoom1KeyDesc[] = _(',
     'static const u8 sOceanPassDesc[] = _( // RF (PASSE BATEAU)\n    "Un ticket pour\\n"\n    "embarquer sur\\n"\n    "l\'OCEANE.");\n\n'
     'static const u8 sAutoRepelDesc[] = _(\n    "Propose un autre\\n"\n    "REPOUSSE quand\\n"\n    "l\'effet se dissipe.");\n\nstatic const u8 sRoom1KeyDesc[] = _(')
once('src/data/items.h', '    [ITEM_FIRE_STONE] =\n', '''    [ITEM_OCEAN_PASS] = // PokemonNative3G : PASSE BATEAU de RF (Léo, Route 25), distinct de celui d'Émeraude
    {
        .name = _("PASS OCEANE"),
        .itemId = ITEM_OCEAN_PASS,
        .price = 0,
        .description = sOceanPassDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_AUTO_REPEL] = // PokemonNative3G : à la place du Cherch'Objet de Kanto (Route 11)
    {
        .name = _("AUTO-REPOUSSE"),
        .itemId = ITEM_AUTO_REPEL,
        .price = 0,
        .description = sAutoRepelDesc,
        .importance = 1,
        .pocket = POCKET_KEY_ITEMS,
        .type = ITEM_USE_BAG_MENU,
        .fieldUseFunc = ItemUseOutOfBattle_CannotUse,
    },

    [ITEM_FIRE_STONE] =
''')

# icônes : PASS OCEANE = ss_ticket de RF ; AUTO-REPOUSSE = Max Repousse en vert ; Météorite de Kanto en rouge
shutil.copy(RF + 'graphics/items/icons/ss_ticket.png', 'graphics/items/icons/ocean_pass.png')
shutil.copy(RF + 'graphics/items/icon_palettes/ss_ticket.pal', 'graphics/items/icon_palettes/ocean_pass.pal')


def recolor(src, dst, fn):
    lines = open(src).read().split('\n')
    out = lines[:3]
    for l in lines[3:19]:
        r, g, b = (int(v) for v in l.split())
        out.append('%d %d %d' % fn(r, g, b))
    open(dst, 'w', newline='\r\n').write('\n'.join(out) + '\n')


def hue(dh, sat=1.0):
    def f(r, g, b):
        h, s, v = colorsys.rgb_to_hsv(r / 255, g / 255, b / 255)
        r2, g2, b2 = colorsys.hsv_to_rgb((h + dh) % 1, min(1, s * sat), v)
        return int(r2 * 255), int(g2 * 255), int(b2 * 255)
    return f


def reddish(r, g, b):
    return min(255, int(r * 1.15 + 40)), int(g * 0.6), int(b * 0.55)


shutil.copy('graphics/items/icons/repel.png', 'graphics/items/icons/auto_repel.png')
recolor('graphics/items/icon_palettes/max_repel.pal', 'graphics/items/icon_palettes/auto_repel.pal', hue(0.33))
recolor('graphics/items/icon_palettes/meteorite.pal', 'graphics/items/icon_palettes/kanto_meteorite.pal', reddish)
DECLS = [('gItemIcon_OceanPass', 'graphics/items/icons/ocean_pass.png', '.4bpp.lz'),
         ('gItemIconPalette_OceanPass', 'graphics/items/icon_palettes/ocean_pass.pal', '.gbapal.lz'),
         ('gItemIcon_AutoRepel', 'graphics/items/icons/auto_repel.png', '.4bpp.lz'),
         ('gItemIconPalette_AutoRepel', 'graphics/items/icon_palettes/auto_repel.pal', '.gbapal.lz'),
         ('gItemIconPalette_KantoMeteorite', 'graphics/items/icon_palettes/kanto_meteorite.pal', '.gbapal.lz')]
for sym, path, ext in DECLS:  # PokemonNative3G : un symbole à la fois (relançable)
    if sym + '[]' not in rd('src/data/graphics/items.h'):
        once('src/data/graphics/items.h', 'const u32 gItemIcon_OldSeaMap[]',
             'const u32 %s[] = INCGFX_U32("%s", "%s"); // PokemonNative3G\nconst u32 gItemIcon_OldSeaMap[]' % (sym, path, ext))
    if sym + '[]' not in rd('include/graphics.h'):
        once('include/graphics.h', 'extern const u32 gItemIcon_OldSeaMap[];\n',
             'extern const u32 gItemIcon_OldSeaMap[];\nextern const u32 %s[];\n' % sym)
once('src/data/item_icon_table.h', '    [ITEM_KANTO_METEORITE] = {gItemIcon_Meteorite, gItemIconPalette_Meteorite}, // même icône dans RF\n',
     '    [ITEM_KANTO_METEORITE] = {gItemIcon_Meteorite, gItemIconPalette_KantoMeteorite}, // même icône que RF, en rougeâtre\n'
     '    [ITEM_OCEAN_PASS] = {gItemIcon_OceanPass, gItemIconPalette_OceanPass},\n'
     '    [ITEM_AUTO_REPEL] = {gItemIcon_AutoRepel, gItemIconPalette_AutoRepel},\n')

# ---------- PASS OCEANE ----------
K = 'data/kanto/data/maps/'
once(K + 'Route25_SeaCottage/scripts.inc', 'ITEM_SS_TICKET', 'ITEM_OCEAN_PASS', 2)
for p in (K + 'Route25_SeaCottage/text_fr.inc', K + 'VermilionCity/text_fr.inc'):
    wr(p, rd(p).replace('PASSE BATEAU', 'PASS OCEANE'))

# ---------- AUTO-REPOUSSE ----------
p = K + 'Route11_EastEntrance_2F/scripts.inc'
wr(p, rd(p).replace('ITEM_ITEMFINDER', 'ITEM_AUTO_REPEL'))
t = K + 'Route11_EastEntrance_2F/text_fr.inc'
set_text(t, 'Route11_EastEntrance_2F_Text_GiveItemfinderIfCaught30', '''	.string "Salut! Tu te rappelles de moi?\\n"
	.string "Je suis un assistant du PROF. CHEN!\\p"
	.string "Si tu as attrapé au moins\\n"
	.string "{STR_VAR_1} sortes de POKéMON,\\l"
	.string "je dois te donner ceci: {STR_VAR_2}!\\p"
	.string "Alors {PLAYER}, as-tu attrapé\\n"
	.string "au moins {STR_VAR_1} POKéMON différents?$"''')
set_text(t, 'Route11_EastEntrance_2F_Text_ReceivedItemfinderFromAide', '''	.string "{PLAYER} reçoit\\n"
	.string "l'AUTO-REPOUSSE!$"''')
set_text(t, 'Route11_EastEntrance_2F_Text_ExplainItemfinder', '''	.string "Quand l'effet d'un REPOUSSE se\\n"
	.string "dissipe, l'AUTO-REPOUSSE te propose\\l"
	.string "d'en utiliser un autre de ton SAC.\\p"
	.string "Plus besoin d'ouvrir le SAC à\\n"
	.string "chaque fois!$"''')
once('data/scripts/repel.inc', 'EventScript_RepelWoreOff::\n\tmsgbox Text_RepelWoreOff, MSGBOX_SIGN\n\tend\n',
     '''EventScript_RepelWoreOff::
	specialvar VAR_0x8004, AutoRepel_Check @ PokemonNative3G : AUTO-REPOUSSE (Kanto, Route 11)
	goto_if_ne VAR_0x8004, ITEM_NONE, Fusion_EventScript_AutoRepel
	msgbox Text_RepelWoreOff, MSGBOX_SIGN
	end

Fusion_EventScript_AutoRepel::
	lockall
	msgbox Fusion_Text_AutoRepelAsk, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Fusion_EventScript_AutoRepelNo
	special AutoRepel_Use
	playse SE_REPEL
	msgbox Fusion_Text_AutoRepelUsed, MSGBOX_DEFAULT
Fusion_EventScript_AutoRepelNo::
	releaseall
	end

Fusion_Text_AutoRepelAsk:
	.string "L'effet de REPOUSSE se dissipe…\\p"
	.string "AUTO-REPOUSSE: utiliser un autre\\n"
	.string "{STR_VAR_1}?$"

Fusion_Text_AutoRepelUsed:
	.string "{PLAYER} utilise\\n"
	.string "{STR_VAR_1}.$"
''')
once('data/kanto/kanto_specials.inc', '\tdef_special SetStarterEggGiven\n',
     '\tdef_special SetStarterEggGiven\n\tdef_special AutoRepel_Check\n\tdef_special AutoRepel_Use\n\tdef_special GiveShinyChansey\n')

# ---------- Boîte Jetons ----------
p = K + 'CeladonCity_Restaurant/scripts.inc'
once(p, '''CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	goto_if_set FLAG_KANTO_GOT_COIN_CASE, CeladonCity_Restaurant_EventScript_AlreadyGotCoinCase
	msgbox CeladonCity_Restaurant_Text_TakeThisImBusted
	checkitemspace ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_NoRoomForCoinCase
	giveitem_msg CeladonCity_Restaurant_Text_ReceivedCoinCaseFromMan, ITEM_COIN_CASE
	setflag FLAG_KANTO_GOT_COIN_CASE
	release
	end
''', '''@ PokemonNative3G : il a tout perdu, même sa BOITE JETONS (celle de Hoenn suffit). 9999 jetons : LEVEINARD chromatique
CeladonCity_Restaurant_EventScript_CoinCaseMan::
	lock
	faceplayer
	setflag FLAG_KANTO_GOT_COIN_CASE
	checkitem ITEM_COIN_CASE
	goto_if_eq VAR_RESULT, FALSE, CeladonCity_Restaurant_EventScript_CoinCaseManSad
	checkcoins VAR_0x8004
	goto_if_lt VAR_0x8004, 9999, CeladonCity_Restaurant_EventScript_CoinCaseManSad
	msgbox Fusion_Text_CoinCaseManSad, MSGBOX_DEFAULT
	msgbox Fusion_Text_CoinCaseManOffer, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, CeladonCity_Restaurant_EventScript_CoinCaseManRelease
	getpartysize
	goto_if_eq VAR_RESULT, PARTY_SIZE, CeladonCity_Restaurant_EventScript_CoinCaseManNoRoom
	removecoins 9999
	msgbox Fusion_Text_CoinCaseManThanks, MSGBOX_DEFAULT
	special GiveShinyChansey
	playfanfare MUS_OBTAIN_ITEM
	msgbox Fusion_Text_ReceivedChansey, MSGBOX_DEFAULT
	waitfanfare
	msgbox Fusion_Text_CoinCaseManBye, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	removeobject VAR_LAST_TALKED
	fadescreen FADE_FROM_BLACK
	release
	end

CeladonCity_Restaurant_EventScript_CoinCaseManSad::
	msgbox Fusion_Text_CoinCaseManSad, MSGBOX_DEFAULT
CeladonCity_Restaurant_EventScript_CoinCaseManRelease::
	release
	end

CeladonCity_Restaurant_EventScript_CoinCaseManNoRoom::
	msgbox Fusion_Text_CoinCaseManNoRoom, MSGBOX_DEFAULT
	release
	end

Fusion_Text_CoinCaseManSad:
	.string "J'ai tout perdu aux machines…\\p"
	.string "Mes jetons, mes économies…\\n"
	.string "Même ma BOITE JETONS!\\p"
	.string "Je n'ai plus rien… Snif…$"

Fusion_Text_CoinCaseManOffer:
	.string "Hein? Ta BOITE JETONS est pleine?\\n"
	.string "Tu… tu me donnerais tes jetons?$"

Fusion_Text_CoinCaseManThanks:
	.string "C'est vrai?! Merci, merci!\\p"
	.string "Tiens, prends mon plus grand trésor.\\n"
	.string "Il m'a toujours porté chance!$"

Fusion_Text_ReceivedChansey:
	.string "{PLAYER} reçoit\\n"
	.string "un LEVEINARD!$"

Fusion_Text_CoinCaseManBye:
	.string "Cette fois, je ne jouerai plus\\n"
	.string "jamais… Adieu!$"

Fusion_Text_CoinCaseManNoRoom:
	.string "Ton équipe est pleine…\\n"
	.string "Je ne peux rien te donner.$"
''')
once('include/constants/flags.h', '#define FLAG_UNUSED_0x029    0x29 // Unused Flag',
     '#define FLAG_COIN_CASE_MAN_GONE 0x29 // PokemonNative3G : l\'homme de la Boîte Jetons (Céladopole) est parti')
p = 'data/maps/CeladonCity_Restaurant/map.json'
m = json.loads(rd(p))
for o in m['object_events']:
    if o['script'] == 'CeladonCity_Restaurant_EventScript_CoinCaseMan':
        o['flag'] = 'FLAG_COIN_CASE_MAN_GONE'
t = rd(p)
nl = '\r\n' if '\r\n' in t else '\n'
wr(p, json.dumps(m, indent=2, ensure_ascii=False).replace('\n', nl) + nl)

# ---------- Pot Poudre ----------
p = K + 'CeruleanCity_House5/scripts.inc'
once(p, '''	goto_if_unset FLAG_KANTO_SYS_GOT_BERRY_POUCH, CeruleanCity_House5_EventScript_NoBerries
	msgbox CeruleanCity_House1_Text_HaveJustTheThing
	setflag FLAG_KANTO_GOT_POWDER_JAR
	giveitem ITEM_POWDER_JAR
	goto_if_eq VAR_RESULT, FALSE, EventScript_BagIsFull
	msgbox CeruleanCity_House1_Text_GoCrushBerriesAtDirectCorner
	release
	end
''', '''	checkitem ITEM_POWDER_JAR @ PokemonNative3G : le POT POUDRE vient de Hoenn ; s'il l'a, assortiment de baies
	goto_if_eq VAR_RESULT, FALSE, CeruleanCity_House5_EventScript_PowderJarAtHoenn
	msgbox Fusion_Text_HaveJarTakeBerries
	setflag FLAG_KANTO_GOT_POWDER_JAR
	giveitem ITEM_SITRUS_BERRY, 3
	giveitem ITEM_LUM_BERRY, 3
	giveitem ITEM_LEPPA_BERRY, 3
	giveitem ITEM_LIECHI_BERRY
	giveitem ITEM_PETAYA_BERRY
	msgbox CeruleanCity_House1_Text_GoCrushBerriesAtDirectCorner
	release
	end

CeruleanCity_House5_EventScript_PowderJarAtHoenn::
	msgbox Fusion_Text_PowderJarAtHoenn
	release
	end

Fusion_Text_HaveJarTakeBerries:
	.string "Oh! Tu as déjà un POT POUDRE?\\n"
	.string "Tu es un vrai connaisseur!\\p"
	.string "Alors prends ces BAIES de ma\\n"
	.string "collection, elles te seront utiles!$"

Fusion_Text_PowderJarAtHoenn:
	.string "Pour garder la POUDRE BAIE, il te\\n"
	.string "faut un POT POUDRE.\\p"
	.string "On en donne au marché de\\n"
	.string "POIVRESSEL, à HOENN.\\p"
	.string "Reviens me voir avec, j'aurai\\n"
	.string "un cadeau pour toi!$"
''')
print('ok')
