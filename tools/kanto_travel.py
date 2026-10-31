#!/usr/bin/env python3
"""Passage Hoenn <-> Kanto (PokemonNative3G, 2026-10-24), scripts : data/scripts/fusion_kanto_travel.inc
- Port de Poivressel / Nénucrique, Ligue de Hoenn finie : KANTO dans le menu du ferry. 1er voyage = aller simple vers Bourg
  Palette ; l'équipe part au PC ; les POKéMON de Hoenn y sont grisés et ne peuvent pas rejoindre l'équipe tant que la
  Ligue de Kanto n'est pas finie et le Rubis/Saphir rendu (CanFlyBetweenRegions, comme le vol ; tools/kanto_travel_pc.py) ;
- ensuite (débloqué) : Poivressel/Nénucrique -> Carmin sur Mer et Carmin sur Mer (marin du port) -> Poivressel ;
- Bourg Palette : la maison de RF est à vendre (pancarte), fermée tant qu'elle n'est pas achetée ; plus de maman ;
  point de retour après K.O. devant la maison dès l'arrivée.
Relancer ne fait rien de plus.
Usage : python tools/kanto_travel.py   (depuis la racine du projet)
"""
import json

K = 'data/kanto/data/maps/'


def rd(p):
    return open(p, encoding='utf-8', newline='').read()


def wr(p, t):
    open(p, 'w', encoding='utf-8', newline='').write(t)


def once(p, a, b, cnt=1):
    t = rd(p)
    if '\r\n' in t:
        a, b = a.replace('\n', '\r\n'), b.replace('\n', '\r\n')
    if b in t:
        return
    assert t.count(a) == cnt, (p, a)
    wr(p, t.replace(a, b))


once('include/constants/flags.h', '#define FLAG_UNUSED_0x02C    0x2C // Unused Flag\n#define FLAG_UNUSED_0x02D    0x2D // Unused Flag\n',
     '#define FLAG_PALLET_HOUSE_BOUGHT  0x2C // PokemonNative3G\n#define FLAG_FUSION_KANTO_VISITED 0x2D // PokemonNative3G\n')

exec(open('tools/kanto_travel_pc.py', encoding='utf-8').read())

once('data/specials.inc', '\tdef_special HasAllMons @ PokemonNative3G\n',
     '\tdef_special HasAllMons @ PokemonNative3G\n\tdef_special Fusion_StorePartyInPC @ PokemonNative3G\n\tdef_special CanFlyBetweenRegions @ PokemonNative3G\n')

# --- ports de Poivressel / Nénucrique : destination KANTO du menu du ferry, ajoutée à la main le 2026-10-31
# (Fusion_CanTakeFerryToKanto, Fusion_EventScript_KantoFerryConfirm / KantoFerryWarp)
once(K + 'VermilionCity/scripts.inc', '''VermilionCity_EventScript_FerrySailor::
	lock
	faceplayer
''', '''VermilionCity_EventScript_FerrySailor::
	lock
	faceplayer
	call Fusion_EventScript_VermilionHoenn @ PokemonNative3G : data/scripts/fusion_kanto_travel.inc
''')

# --- Bourg Palette : maison à vendre, plus de maman
once(K + 'PalletTown/scripts.inc', '''PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
''', '''PalletTown_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Fusion_PalletTown_OnLoad @ PokemonNative3G : maison fermée tant qu'elle n'est pas achetée
	map_script MAP_SCRIPT_ON_TRANSITION, PalletTown_OnTransition
''')
once(K + 'PalletTown/scripts.inc', '''PalletTown_EventScript_PlayersHouseSign::
	msgbox PalletTown_Text_PlayersHouse, MSGBOX_SIGN
	end''', '''PalletTown_EventScript_PlayersHouseSign::
	goto_if_unset FLAG_PALLET_HOUSE_BOUGHT, Fusion_EventScript_PalletHouseForSale @ PokemonNative3G
	msgbox PalletTown_Text_PlayersHouse, MSGBOX_SIGN
	end''')
m = json.load(open('data/maps/PalletTown/map.json', encoding='utf-8'))
if not any(b.get('script') == 'Fusion_EventScript_PalletHouseDoor' for b in m['bg_events']):
    m['bg_events'].append({'type': 'sign', 'x': 6, 'y': 7, 'elevation': 0, 'player_facing_dir': 'BG_EVENT_PLAYER_FACING_NORTH',
                           'script': 'Fusion_EventScript_PalletHouseDoor'})
    open('data/maps/PalletTown/map.json', 'w', encoding='utf-8', newline='\n').write(json.dumps(m, indent=2, ensure_ascii=False) + '\n')
p = 'data/maps/PalletTown_PlayersHouse_1F/map.json'
m = json.load(open(p, encoding='utf-8'))
for o in m['object_events']:
    if o['local_id'] == 'LOCALID_KANTO_MOM':
        o['flag'] = 'FLAG_SYS_GAME_CLEAR'  # la maison est celle du joueur de Hoenn (il faut finir la Ligue de Hoenn pour venir)
open(p, 'w', encoding='utf-8', newline='\n').write(json.dumps(m, indent=2, ensure_ascii=False) + '\n')

once('data/event_scripts.s', '\t.include "data/scripts/fusion_charms.inc"\n',
     '\t.include "data/scripts/fusion_charms.inc"\n\t.include "data/scripts/fusion_kanto_travel.inc"\n')
print('ok')
