#!/usr/bin/env python3
"""Vélo (PokemonNative3G, 2026-10-24) : un seul vélo, celui de Hoenn (VELO COURSE / VELO CROSS). La BICYCLETTE de
Kanto n'est plus donnée : le vendeur d'Azuria envoie à Lavandia si le joueur n'a pas de vélo, sinon il lui donne
l'autre modèle (on passe de l'un à l'autre depuis le SAC, src/bike.c GetOnOffBike). Les portiques de la Piste
Cyclable laissent passer avec n'importe quel vélo de Hoenn (FLAG_RECEIVED_BIKE). Relancer ne fait rien de plus.
Usage : python tools/kanto_bike.py   (depuis la racine du projet)
"""
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


for m in ('Route16_NorthEntrance_1F', 'Route18_EastEntrance_1F'):
    once(K + m + '/scripts.inc', '\tcall_if_set FLAG_KANTO_GOT_BICYCLE,', '\tcall_if_set FLAG_RECEIVED_BIKE,')
once(K + 'CeruleanCity_BikeShop/scripts.inc', '''	goto_if_set FLAG_KANTO_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_KANTO_GOT_BIKE_VOUCHER, CeruleanCity_BikeShop_EventScript_ExchangeBikeVoucher
''', '''	goto_if_set FLAG_KANTO_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_AlreadyGotBicycle
	goto_if_set FLAG_RECEIVED_BIKE, Fusion_EventScript_BikeShopGiveOtherBike @ PokemonNative3G : data/scripts/fusion_bike.inc
	msgbox Fusion_Text_BikeShopGoToMauville
	release
	end
''')
once(K + 'CeruleanCity_BikeShop/scripts.inc',
     '\tgoto_if_set FLAG_KANTO_GOT_BICYCLE, CeruleanCity_BikeShop_EventScript_YoungsterHaveBike\n',
     '\tgoto_if_set FLAG_RECEIVED_BIKE, CeruleanCity_BikeShop_EventScript_YoungsterHaveBike @ PokemonNative3G\n')
once('src/bike.c', '''    if (gPlayerAvatar.flags & (PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
    {
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
''', '''    // PokemonNative3G : déjà sur l'autre vélo (le vendeur d'Azuria donne les deux) : on change de vélo sans descendre
    if ((gPlayerAvatar.flags & (PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
     && !(gPlayerAvatar.flags & transitionFlags))
    {
        SetPlayerAvatarTransitionFlags(transitionFlags);
    }
    else if (gPlayerAvatar.flags & (PLAYER_AVATAR_FLAG_MACH_BIKE | PLAYER_AVATAR_FLAG_ACRO_BIKE))
    {
        SetPlayerAvatarTransitionFlags(PLAYER_AVATAR_FLAG_ON_FOOT);
''')
once('data/event_scripts.s', '\t.include "data/scripts/fusion_fishing.inc"\n',
     '\t.include "data/scripts/fusion_fishing.inc"\n\t.include "data/scripts/fusion_bike.inc"\n')
print('ok')
