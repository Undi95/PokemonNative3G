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
- [-] Interface du PC (stockage) : abandonné (choix utilisateur 2026-10-23) — on garde celle d'Émeraude, qui a déjà les fonds des deux versions
- [x] Écran de nom (MENUS : police + icône PC de RF ; sprite selon PERSO ; Easy Chat gardé d'Émeraude) (option, décision 2026-10-23) : clavier de RF, avec le sprite du perso choisi (Brice/Flora ou Red/Leaf) ;
  aussi l'écran de sélection de mots (Easy Chat)
- [x] Intro (KANTO par défaut) : option INTRO HOENN/KANTO près de ÉCRAN TITRE (Flygon / Nidorino-Ectoplasma)
- [x] Crédits (kanto_credits.c, testés en headless, musique continue) : ceux de la Ligue finie (Hoenn après Hoenn, Kanto après Kanto), pas d'option
- [x] Panthéon (kanto_hall_of_fame.c, sauvegarde annexe @8192, PC par région, testé en headless) : deux Panthéons séparés ; le PC de Kanto montre celui de Kanto, le PC de Hoenn celui de Hoenn
- [x] Sprites des Pokémon (option POKéMON) : Émeraude animés / Rouge Feu fixes ; Deoxys : forme au choix (menu de l'équipe)
- [x] Carte de la région / Vol (pas d'option ; kanto_region_map.c, SELECT entre régions) : carte RF à Kanto (avec Sevii), carte d'Émeraude à Hoenn ; une touche
  bascule vers l'autre région et permet d'y voler (villes visitées). Bascule débloquée seulement quand la Ligue de
  Kanto est finie ET le Rubis/Saphir rendu à Céladon (quête post-game RF qui relie le PC de Kanto à Hoenn :
  sert de contexte, le joueur ne récupère pas ses Pokémon de Hoenn avant). POKéDEX Kanto : débloqué par le
  Pokédex de Chen (déjà fait).
## À faire (liste de l'utilisateur, 2026-10-23)
- [x] Cartes de région : icône du joueur selon le perso choisi (PERSO) sur les deux cartes
- [x] Cherche VS à Hoenn : il déclenche les revanches du PokéNav (dresseurs inscrits ; 70 % comme RF, 100 % si un appel l'avait déjà décidé) ; les dresseurs de Hoenn sautent au lieu de lever la main (pas d'image « main levée » dans les sprites d'Émeraude)
- [-] Cherche VS : sprites de Brice/Flora levant le Cherche VS : pas faisable simplement (tout le corps change de pose dans les images de RF, il faudrait redessiner) ; Brice/Flora se tournent vers le bas, comme Red
- [ ] Évolution par échange en solo (objet du genre « câble link »)
- [ ] Pokémon exclusifs à Rubis, Saphir et Vert Feuille : les rendre obtenables
- [ ] Légendaires manquants (vers la fin)
- [ ] Événements en jeu à Hoenn (ceux de RF + Mew) et objets requis (Ticket Aurora, Ticket Mystique, etc.)
- [ ] Aperçus de donjons/lieux de RF à Kanto (map_preview_screen.c ; données déjà dans kanto_region_map.c)
- [ ] « Précédemment dans votre quête » (journal de RF) : partout si possible, avec une option (désactivé par défaut)
- [x] Courir partout (intérieurs compris ; bike.c, IsRunningDisallowed)
- [x] Cherch'Objet selon la région (kanto_itemfinder.c = RF à Kanto, Émeraude à Hoenn) ; objets « sous les pieds » de RF perdus à l'import des cartes (traités comme des objets cachés normaux)
- [ ] Objets donnés deux fois (CS, cannes, Passe Bateau…) : voir docs/OBJETS-EN-DOUBLE.md

## Trouvé par la cartographie — décisions de l'utilisateur (2026-10-23)
Contenu de RF à importer :
- [x] Combat FANTÔME de la Tour Pokémon (SPECTRES sans Scope Sylph, Ossatueur révélé avec le Scope Sylph de Giovanni ; `gBattleGhostType`, plus de bit libre dans gBattleTypeFlags)
- [x] Objets cachés qui réapparaissent (`src/kanto_renewable_hidden_items.c`, 2026-10-23)
- [x] Fame Checker = MEMORYDEX (2026-10-23, `src/kanto_fame_checker.c` ; même écran avec les deux sacs, police de RF)
- [ ] Animation quand on utilise un objet sur un Pokémon (pokemon_special_anim*.c : CT, Super Bonbon…) : jouée avec le sac KANTO (option SAC), sac HOENN comme Émeraude
- [x] Note du Pokédex par Chen (2026-10-23) : GetProfOaksRatingMessage de RF (PC, Chen en personne, ses aides) ; « PC du PROF. CHEN » ajouté au menu PC à Kanto une fois son Pokédex reçu
- [x] TOUTES les cinématiques de RF (2026-10-23) : départ du S.S. Anne, ferry Seagallop, et les autres stubs de `kanto_specials_stubs.c` (éclairage de la Ligue, téléporteurs de Léo, triangle de Deoxys, fossiles du musée, diplôme…)
- [x] IA des légendaires de RF (2026-10-23, `gBattleLegendaryFrlg` : StartLegendaryBattle de Kanto, IA « mauvaises attaques + K.O. + viabilité »)

Choix HOENN / KANTO :
- [ ] PC objets : interface de RF en option ; les objets stockés restent communs aux deux régions (même stockage)
- [ ] Maître des capacités (réapprentissage) : interface de RF en option (learn_move.c), rendu seulement. Les deux proposent déjà les mêmes attaques (capacités par niveau, mêmes données) : rien à fusionner
- Donneurs de capacités : chacun reste exclusif à sa région (pas de changement)
- [ ] Boutique : interface de RF en option
- [ ] Machine à sous : PAS d'option, chacune dans sa région (celle de RF au Casino de Céladopole, celle d'Émeraude à Lavandia)
- [ ] Menu Start de RF : en option
- [x] Menu Options en pages (2026-10-23, L/R ; titre « {L}{R} PAGE 1/2 : JEU » / « PAGE 2/2 : HOENN/KANTO » ; page 2 : PERSO, POKéMON, DIALOGUE, BOITES COMBAT, MENUS, SAC, POKéDEX, TITRE, INTRO) : page 1 = réglages d'Émeraude, page 2 (et suivantes) = choix HOENN/KANTO ; indiquer clairement qu'il y a d'autres pages (ex. « PAGE 1/2 » et flèches L/R dans le titre)

## Notes
- Piste (utilisateur) : Émeraude a été construit à partir de Rouge Feu ; il garde des fonctions vidées et des entrées inutilisées de RF (ex. BgTileAllocOp « Dummied out », LoadMonPicInWindow UNUSED). Les rétablir avec le code de RF avant de réinventer.
- Comparaison des cadres : script PIL (pixels RGB identiques) ; refaire de même pour chaque liste.
- Les choix d'option sont dans gSaveBlock2Ptr (bits libres) ; au-delà, gSaveBlockKanto.
