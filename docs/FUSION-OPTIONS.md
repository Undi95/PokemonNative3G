# Fusion Émeraude + Rouge Feu : tout ce qui existe dans les deux jeux

Règle (utilisateur, 2026-10-20) : tout ce qui existe dans les deux jeux est fusionné pour avoir tout le
contenu dans un seul jeu.
- Contenu de même nature (cadres, fonds de PC…) : on garde **les deux listes**, sans doublon (comparer
  pixels + palette ; un élément identique n'apparaît qu'une fois).
- Présentation différente d'un même écran (Pokédex, barres de combat…) : **choix HOENN / KANTO dans les
  Options**, chaque version avec ses propres fonctions.
- Le menu Options défile (`MAX_VISIBLE_ITEMS`), on peut y ajouter autant de lignes que nécessaire.

## Fait
- [x] Personnage joué : BRICE/FLORA ou RED/LEAF (option PERSO) — carte, combat, carte dresseur
- [x] Écran titre : Émeraude ou Rouge Feu (option TITRE)
- [x] Carte dresseur : les deux (Hoenn / Kanto), SELECT pour passer de l'une à l'autre
- [x] Cadres de menus : 20 d'Émeraude + 9 de Rouge Feu (type 2 de RF = cadre 2 d'Émeraude) = 29 (option CADRE)
- [x] Sac : poches agrandies pour contenir les objets des deux jeux
- [x] Fonds des boîtes du PC : 16 d'Émeraude + 16 de Rouge Feu (tous différents), catégorie KANTO (non testé en jeu)
- [x] Boîte de dialogue : HOENN / KANTO (option DIALOGUE : cadre, fenêtre et police de RF) — panneaux de RF (signpost) pas encore

- [x] Interface de combat : boîtes de PV/EXP et boîte de texte de combat HOENN / KANTO (option BOITES COMBAT) — barre de l'équipe (balls) encore celle d'Émeraude
- [x] Pokédex HOENN / KANTO (option POKéDEX) : écran complet de RF (pokedex_screen.c porté, textes/descriptions de RF, zones de Kanto)

## À faire — contenu à réunir (listes)
- Décision : musiques, animations et transitions de combat = celles de la région, comme dans les jeux officiels (pas d'option).
- Options : menu ergonomique (sous-menus / pages) si la liste devient trop longue.

## À faire — choix HOENN / KANTO dans les Options
- [x] Menus (option MENUS) : menu Start, équipe et résumé
- [x] Sac (option SAC, 2026-10-23) : sac de RF (kanto_item_menu.c, kanto_bag.c, kanto_item_menu_icons.c),
  Boîte à CT (kanto_tm_case.c) et Sac à Baies (kanto_berry_pouch.c) pour les poches CT/CS et Baies d'Émeraude.
  Aiguillage : GoToBagMenu d'Émeraude -> KantoBag_TryGoToBagMenu (terrain, combat, équipe, boutique, PC objets,
  PC boîtes ; le reste garde le sac d'Émeraude : arbres à baies, mixeur, dames, apprenti) ; DisplayItemMessage,
  CloseItemMessage, Task_FadeAndCloseBagMenu et SetBagMenuNewScreenCallback (ex-gBagMenu->newScreenCallback)
  suivent le sac ouvert, ou le Sac à Baies pour une baie (comme item_use.c de RF). Boîte à CT et Sac à Baies
  ajoutés en tête des Objets rares à l'ouverture du sac de RF, retirés à celle du sac d'Émeraude.
  Retirés de RF : tutoriels (Vieil Homme, Télé Pokémon), journal des quêtes.
- [ ] Interface du PC (stockage)
- [ ] Écran de nom (clavier)
- [ ] Intro (Flygon / Nidorino-Ectoplasma), crédits, Panthéon
- [ ] Sprites des Pokémon (de face/de dos : Émeraude animés, Rouge Feu fixes et parfois différents)
- [ ] Carte de la région / Vol : chaque région garde la sienne (pas une option : Kanto = carte RF)

## Notes
- Piste (utilisateur) : Émeraude a été construit à partir de Rouge Feu ; il garde des fonctions vidées et des entrées inutilisées de RF (ex. BgTileAllocOp « Dummied out », LoadMonPicInWindow UNUSED). Les rétablir avec le code de RF avant de réinventer.
- Comparaison des cadres : script PIL (pixels RGB identiques) ; refaire de même pour chaque liste.
- Les choix d'option sont dans gSaveBlock2Ptr (bits libres) ; au-delà, gSaveBlockKanto.
