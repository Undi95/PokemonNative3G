# Objets donnés dans les deux régions

Objets clés et CS que les scripts d'Émeraude ET de Rouge Feu donnent. Comme ce sont les mêmes
objets (même constante, les `ITEM_HM0x` de Kanto valent les `ITEM_HM_*` d'Émeraude), le joueur
peut les recevoir deux fois. Pour chaque ligne : le script à modifier (carte:ligne de la commande
`giveitem` / `giveitem_msg` / `finditem` / `msgreceiveditem`).

Généré par `tools/item_doubles.py` (à refaire si les scripts changent : cherche les commandes de
don dans `data/**/*.inc`, sépare `data/kanto/`, garde les poches Objets rares / CT-CS).

## Doublons exacts

**CS01 à CS07 : réglées (2026-10-24)** : à Kanto, POKé MONTURE au lieu des CS (voir docs/FUSION-OPTIONS.md) ;
les CS ne sont plus données qu'à Hoenn.
**Météorite : réglée (2026-10-24)** : deux objets distincts (ITEM_KANTO_METEORITE pour RF, `tools/kanto_meteorite.py` ;
même nom et même icône, identique dans les deux jeux).
**Passe Bateau, Cherch'Objet, Boîte Jetons, Pot Poudre : réglés (2026-10-24, `tools/kanto_doubles.py`)** : PASS OCEANE
(image de RF) ; AUTO-REPOUSSE à la place du Cherch'Objet de Kanto ; l'homme de la Boîte Jetons a tout perdu
(easter-egg 9999 jetons) ; le Pot Poudre vient de Hoenn (baies à Azuria si on l'a). Météorite de Kanto rougeâtre.
**Cannes : réglées (2026-10-24)** : les pêcheurs de Kanto améliorent la canne (chaîne de pêche chromatique).

| Objet | Hoenn (data/maps/…) | Kanto (data/kanto/data/maps/…) |
|---|---|---|
| CS01 Coupe | RustboroCity_CuttersHouse:9 | SSAnne_CaptainsOffice:18 |
| CS02 Vol | Route119:131 | Route16_House:11 |
| CS03 Surf | PetalburgCity_WallysHouse:22 | SafariZone_SecretHouse:11 |
| CS04 Force | RusturfTunnel:59 | FuchsiaCity_WardensHouse:26 |
| CS05 Flash | GraniteCave_1F:9 | Route2_EastBuilding:21 |
| CS06 Éclate-Roc | MauvilleCity_House1:9 | OneIsland_KindleRoad_EmberSpa:33 |
| CS07 Cascade | SootopolisCity:1287 | scripts/item_ball_scripts.inc:618 (objet au sol, Îles Sevii) |
| Canne | DewfordTown:83 | VermilionCity_House1:22-24 |
| Super Canne | Route118:34 | FuchsiaCity_House2:23 |
| Méga Canne | MossdeepCity_House3:11 | Route12_FishingHouse:17-19 |
| Boîte Jetons | MauvilleCity_House2:28 | CeladonCity_Restaurant:19 |
| Cherch'Objet | Route110:461 | Route11_EastEntrance_2F:71 |
| Pot Poudre | SlateportCity:711 | CeruleanCity_House5:13 |
| Passe Bateau | data/scripts/players_house.inc:434 | Route25_SeaCottage:101 |
| Météorite | MtChimney:443 | OneIsland_PokemonCenter_1F:100-101 (quête différente, garder les deux en tête) |

## Même rôle, objet différent (à décider)

| Rôle | Hoenn | Kanto |
|---|---|---|
| Carte | POKéNAV (carte intégrée) | CARTE (PalletTown_RivalsHouse, OneIsland_PokemonCenter_1F) |
| Vélo | Vélo Course / Vélo Cross (Mauville) | Bicyclette (CeruleanCity_BikeShop) — fait : plus de Bicyclette, le vendeur donne l'autre vélo de Hoenn ; BON COMMANDE remplacé par l'OVO-CHRONO |
| Pokédex | Pokédex de Hoenn | Pokédex de Kanto (déjà géré : option POKéDEX) |

## Piste pour les remplacer

Une macro de script, par ex. `giveitem_or_alt ITEM_X, ITEM_REMPLACANT` : si `checkitem ITEM_X`
réussit déjà, donner le remplaçant (ou un message « tu l'as déjà »), sinon le don normal. Il
suffit alors de remplacer la commande aux lignes ci-dessus, sans toucher au reste du script.
