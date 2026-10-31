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
- [x] Boîte de dialogue : HOENN / KANTO (option DIALOGUE : cadre, fenêtre et police de RF ; panneaux de RF et texte bleu/rouge des PNJ de Kanto depuis le 2026-10-30)

- [x] Interface de combat : boîtes de PV/EXP et boîte de texte de combat HOENN / KANTO (option BOITES COMBAT), barre de l'équipe (Poké Balls) de RF comprise (2026-10-30, `options_partybar`)
- [x] Pokédex HOENN / KANTO (option POKéDEX) : écran complet de RF (pokedex_screen.c porté, textes/descriptions de RF, zones de Kanto)

## À faire — contenu à réunir (listes)
- Décision : musiques, animations et transitions de combat = celles de la région, comme dans les jeux officiels (pas d'option).
- [x] Options : deux pages (L/R) : réglages d'Émeraude, puis choix HOENN / KANTO.

## À faire — choix HOENN / KANTO dans les Options
- [x] Menus (option MENUS) : menu Start, équipe et résumé
- [x] Sac (option SAC, 2026-10-23) : sac de RF (kanto_item_menu.c, kanto_bag.c, kanto_item_menu_icons.c),
  Boîte à CT (kanto_tm_case.c) et Sac à Baies (kanto_berry_pouch.c) pour les poches CT/CS et Baies d'Émeraude.
  Aiguillage : GoToBagMenu d'Émeraude -> KantoBag_TryGoToBagMenu (terrain, combat, équipe, boutique, PC objets,
  PC boîtes ; le reste garde le sac d'Émeraude : arbres à baies, mixeur, dames, apprenti) ; DisplayItemMessage,
  CloseItemMessage, Task_FadeAndCloseBagMenu et SetBagMenuNewScreenCallback (ex-gBagMenu->newScreenCallback)
  suivent le sac ouvert, ou le Sac à Baies pour une baie (comme item_use.c de RF). Boîte à CT et Sac à Baies
  ajoutés en tête des Objets rares à l'ouverture du sac de RF, retirés à celle du sac d'Émeraude.
  SELECT ne déplace pas la Boîte à CT ni le Sac à Baies, et un objet posé au-dessus d'eux va juste après
  (2026-10-31, `kanto_bag_cases.py`).
  Retirés de RF : tutoriel du Vieil Homme (il garde le sac d'Émeraude), journal des quêtes.
- [x] Télé Pokémon / TV ABC (2026-10-31, `kanto_teachy_tv.c`, `kanto_battle_controller_pokedude.c`) : les six émissions
  du Pokédude de RF, depuis le sac (des deux styles) ou SELECT. Combats de démonstration avec l'interface de combat de RF
  quelle que soit l'option (cadre de voix off, fenêtre 24), décor d'herbe ; sac, équipe et Boîte à CT de démonstration
  (le sac du joueur est sauvegardé puis rendu, poches agrandies comprises). RF n'affiche les émissions CT et objet
  qu'avec la Boîte à CT : ici, dès la première CT ou CS (avec le sac de RF, la Boîte à CT de la fusion est toujours là).
  BATTLE_TYPE_POKEDUDE n'a pas de bit libre : `gBattlePokedudeFrlg`.
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
- [x] Braille (2026-10-24) : option DIALOGUE = KANTO -> écrit dans la boîte de dialogue (comme RF) ; HOENN -> fenêtre d'Émeraude ; vérifié en headless (`kanto_dotted_hole.py` / `kanto_dotted_hole_rf.py`)
- [-] Décorations de Kanto (maison de Bourg Palette) : abandonné (choix utilisateur 2026-10-24) ; la chambre de RF n'a pas les tuiles de décoration d'Émeraude
- [x] Cartes de région : icône du joueur selon le perso choisi (PERSO) sur les deux cartes
- [x] Cherche VS à Hoenn : il déclenche les revanches du PokéNav (dresseurs inscrits ; 70 % comme RF, 100 % si un appel l'avait déjà décidé) ; les dresseurs de Hoenn sautent au lieu de lever la main (pas d'image « main levée » dans les sprites d'Émeraude)
- [-] Cherche VS : sprites de Brice/Flora levant le Cherche VS : pas faisable simplement (tout le corps change de pose dans les images de RF, il faudrait redessiner) ; Brice/Flora se tournent vers le bas, comme Red
- [x] Évolution par échange en solo (2026-10-24) : CÂBLE LINK, 2100₽, vendu dans toutes les boutiques (`tools/link_cable.py`) ; utilisé comme une pierre, le Pokémon évolue comme après un échange (avec son objet tenu pour Tarinor, Coquiperl…). Icône : « linking_cord » de pokeemerald-expansion (rh-hideout, github.com/rh-hideout/pokeemerald-expansion)
- [x] Pokémon exclusifs à Rubis, Saphir et Vert Feuille (2026-10-24, ajout permanent, `tools/exclusifs.py`) : à Kanto/Sevii, Chétiflor/Boustiflor, Magmar, Farfuret, Feuforêve, Démanta aux endroits de Vert Feuille ; à Hoenn, Arakdo, Rosélia, Mangriff, Séléroc, Méditikka, Charmina aux endroits de Rubis/Saphir. Un créneau sur deux reçoit la nouvelle espèce (l'espèce d'origine reste). `tools/obtenables.py [--trade]` liste ce qui reste inobtenable
- [x] Starters manquants (2026-10-24) : un assistant du professeur dans chaque pension (Route 117 à Hoenn, Île 4 à Kanto) donne, après la Ligue de sa région, un œuf de chaque starter jamais attrapé (Hoenn : aussi ceux de Johto une fois celui de SEKO reçu) ; `src/fusion_events.c`, `data/scripts/fusion_starter_eggs.inc`, VAR_STARTER_EGGS_GIVEN (ancienne var inutilisée 0x404E)
- [x] Celebi (2026-10-24) : petit autel en bois dessiné pour la fusion (`graphics/fusion/object_events/shrine.png`) au fond de la Forêt Baies (Île 3, en haut à droite) ; après les deux Ligues, CELEBI apparaît quand on l'examine, combat légendaire N.30 (musique des légendaires de RF) ; vaincu = parti (comme Mew), fuite = il revient (`data/scripts/fusion_celebi.inc`, FLAG_CAUGHT_CELEBI / FLAG_DEFEATED_CELEBI)
- [x] Jirachi (2026-10-24) : après les deux Ligues, une TV de Hoenn passe un flash spécial (comète du millénaire, une fois) ; une météorite (dessinée pour la fusion, `graphics/fusion/object_events/meteorite.png`) apparaît au fond des Chutes Météore (B1F, salle de la CT Dracogriffe ; Surf + Cascade), sans limite de temps. JIRACHI dort dedans : le texte explique qu'il faut une mélodie comme la POKé FLÛTE de Kanto ; avec elle, combat légendaire N.30 (musique de Mew). Vaincu = parti, fuite = il se rendort (`data/scripts/fusion_jirachi.inc`)
- [x] Légendaires manquants (2026-10-24) : Celebi et Jirachi (voir plus haut) ; les autres étaient déjà obtenables (`tools/obtenables.py`)
- [x] Événements de distribution (2026-10-24) : option CADEAU MYST. au menu principal une fois le RUBIS et le SAPHIR rendus à CÉLIO, tant qu'un cadeau manque ; chaque cadeau est présenté sur une CARTE MYSTÈRE d'Émeraude (fond, icône Deoxys / Lugia / Mew) puis donné avec les effets des scripts de distribution : TICKET AURORA (ILE AURORE) et TICKET MYSTIK (ROC NOMBRI) au départ de Nénucrique ou de Carmin sur Mer, VIEILLE CARTE (ILE LOINTAINE, Mew) au départ de Nénucrique seulement ; sauvegarde puis retour au titre, l'option disparaît (`CB2_InitFusionMysteryGift`, mystery_gift_menu.c). Îles en un seul exemplaire (cartes d'Émeraude), donc légendaires combattus une seule fois ; venu par le ferry de Carmin, le marin de l'île ramène à Carmin (FLAG_ISLAND_TRIP_FROM_KANTO)
- [x] Aperçus de donjons/lieux de RF à Kanto (2026-10-24, `src/kanto_map_preview_screen.c`)
- [-] « Précédemment dans votre quête » (journal de RF) : abandonné (décision de l'utilisateur, 2026-10-24)
- [x] Courir partout (intérieurs compris ; bike.c, IsRunningDisallowed)
- [x] Cherch'Objet de RF dans tout le jeu (2026-10-31, choix de l'utilisateur ; avant : celui d'Émeraude à Hoenn, retiré) ; objets « sous les pieds » de RF perdus à l'import des cartes (traités comme des objets cachés normaux)
- [x] Objets donnés deux fois : voir docs/OBJETS-EN-DOUBLE.md ; CS réglées (2026-10-24) : POKé MONTURE à Kanto ; plus aucun objet clé ni CS donné dans les deux régions (`tools/item_doubles.py`, 2026-10-31)
- [x] CS (2026-10-24) : les CS restent à Hoenn ; à Kanto, les 7 dons de CS de RF donnent la POKé MONTURE (objet rare, icône dessinée pour la fusion) puis lui ajoutent chaque capacité (flags de RF FLAG_KANTO_GOT_HM01..06 et ramassage de la CS07). Sans POKéMON de l'équipe qui connaît la capacité, un POKéMON des environs vient l'utiliser, partout : Kanto INSECATEUR, ROUCARNAGE, LOKHLASS, MACKOGNEUR, PIKACHU, GROLEM, POISSOROY ; Hoenn ABSOL, ALTARIA, WAILORD, HARIYAMA, ÉLECSPRINT, GALEGON, MILOBELLUS (Coupe, Vol, Surf, Force, Flash, Éclate-Roc, Cascade). Badges toujours exigés ; Vol et Flash depuis le sac. `tools/poke_monture.py`, `data/scripts/fusion_poke_monture.inc`, `src/fusion_events.c`
- [x] Cannes (2026-10-24) : les 3 pêcheurs de Kanto (CANNE à Carmin, SUPER CANNE à Parmanie, MEGA CANNE Route 12) améliorent la canne au lieu d'en donner une 2e (s'il ne l'a pas encore, ils la donnent, déjà améliorée) ; chacun a son texte. Canne améliorée : chaîne de pêche, chaque POKéMON remonté au même endroit donne un tirage chromatique de plus à la prise suivante (max 40) ; la série se brise si rien ne mord / s'échappe, si le joueur fait un pas, change de carte ou de canne (`FishingChain_*`, src/fusion_events.c ; data/scripts/fusion_fishing.inc ; FLAG_OLD/GOOD/SUPER_ROD_UPGRADED)
- [x] Cannes sans canne de Hoenn (2026-10-24) : les pêcheurs de Kanto ne la donnent plus, ils disent où la trouver (Myokara, Route 118, Algatia)
- [x] Vélo (2026-10-24) : un seul vélo, celui de Hoenn ; vendeur d'Azuria = l'autre modèle (changement depuis le SAC, même en roulant ; src/bike.c GetOnOffBike) ; Piste Cyclable : portiques ouverts avec un vélo de Hoenn, pentes de RF rétablies pour les deux vélos (MB_CYCLING_ROAD_PULL_DOWN, tools/cycling_road.py, tools/kanto_bike.py)
- [x] Passage Hoenn <-> Kanto (2026-10-24, tools/kanto_travel.py, kanto_travel_pc.py, data/scripts/fusion_kanto_travel.inc) : Ligue de Hoenn finie, KANTO dans le menu du ferry de Poivressel / Nénucrique (2026-10-31 : avant, une question à part avant le menu ; départ du ferry animé comme les autres destinations ; menu défilant de Nénucrique au-delà de 6 destinations) ; PAPA en parle en donnant le PASSE BATEAU ; 1er voyage = aller simple vers Bourg Palette (le marin explique, en conseil de vieux marin : personne n'y connaît tes exploits, PC non reliés, on repart comme au premier jour avec son SAC, pas de retour, ceux qui en reviennent en sont MAÎTRES, CILEO veut relier les régions), l'équipe part au PC ; les POKéMON possédés au départ (équipe et PC, échanges et starter compris ; marque HOENN_MON_MARK dans un bit de rubans inutilisé) y sont grisés et refusés dans l'équipe (« Aucune connexion avec HOENN… ») tant que la Ligue de Kanto n'est pas finie et le Rubis/Saphir rendu à CILEO (CanFlyBetweenRegions, qui débloque aussi le vol) ; ensuite bateau Poivressel/Nénucrique <-> Carmin sur Mer (marin du port). Bourg Palette : maison de RF à vendre 300 000¥ (pancarte en bois à la place de la boîte aux lettres, argent affiché ; achat = fondu au noir, puis porte ouverte et boîte aux lettres au nom du joueur), plus de maman, point de retour après K.O. devant la maison. Menu START sans POKéMON si l'équipe est vide
- [x] Cartes selon la région (2026-10-24) : carte murale (EventScript_RegionMap -> EventScript_WallTownMap de RF à Kanto), objet CARTE (kanto_region_map.c : Hoenn -> FieldInitRegionMap), POKéNAV onglet CARTE à Kanto = carte de RF plein écran puis retour au POKéNAV (pokenav.c, CB2_OpenKantoMapFromPokenav) ; libellé « CARTE DE KANTO » (graphics/pokenav/options/kanto_map.png, tools/pokenav_kanto_label.py) et aide de Kanto
- [x] Nom du PC (2026-10-24, tools/pc_owner.py) : « PC de ??? » devient PC de LÉO à Kanto (après l'avoir rencontré) et PC d'ANNETTE à Hoenn (menu, connexion, transfert)
- [x] Objets de confort (2026-10-24, tools/fusion_charms.py) : OVO-CHRONO (Fan Club de Carmin, au lieu du BON COMMANDE ; éclosion x2), CHARME CHROMA (concepteur de Nénucrique, POKéDEX NATIONAL ; +2 tirages chromatiques sur les sauvages et les OEUFS de la PENSION), CHARME OVALE (concepteur de Céladopole, POKéDEX NATIONAL ; OEUFS 20/50/70 % -> 40/80/88 %)

## Trouvé par la cartographie — décisions de l'utilisateur (2026-10-23)
Contenu de RF à importer :
- [x] Approche des dresseurs, la même dans tout le jeu (2026-10-31, choix de l'utilisateur ; scénario `trainer_camera`) : caméra de RF quand un dresseur tourné vers le bas repère le joueur de loin (elle monte jusqu'à lui, « ! », puis redescend) ; comme dans Émeraude, le joueur se tourne vers le dresseur (RF ne le faisait pas)
- [x] Description des capacités de terrain dans le menu d'équipe (2026-10-31, RF ; avec MENUS = KANTO ; scénario `options_fieldmove_desc`) : bande de RF au-dessus du message ; Plongée et Force Cachée, absentes de RF, ont deux descriptions dans le même style (« Plonger en eau profonde. », « Ouvrir une base secrète. »)
- [x] K.O. de RF dans tout le jeu (2026-10-31, demandé par l'utilisateur ; scénario `kanto_whiteout`) : perte d'argent de RF (niveau de l'équipe × badges de la région où l'on est ; Émeraude : la moitié de l'argent) annoncée en combat (« panique et perd X¥ », « paye X¥ comme récompense ») et après un K.O. par le poison ; reprise devant l'infirmière du dernier Centre, Kanto comme Hoenn (respawn_* de `heal_locations.json`), message sur fond noir puis soins. Sans infirmière (maisons de Bourg-en-Vol et de Bourg Palette, Île du Sud) : reprise d'Émeraude
- [x] Combat FANTÔME de la Tour Pokémon (SPECTRES sans Scope Sylph, Ossatueur révélé avec le Scope Sylph de Giovanni ; `gBattleGhostType`, plus de bit libre dans gBattleTypeFlags)
- [x] Objets cachés qui réapparaissent (`src/kanto_renewable_hidden_items.c`, 2026-10-23)
- [x] Fame Checker = MEMORYDEX (2026-10-23, `src/kanto_fame_checker.c` ; même écran avec les deux sacs, police de RF)
- [x] Animation quand on utilise un objet sur un Pokémon (2026-10-24, `kanto_pokemon_special_anim*.c` : soins, PP, CT/CS, Super Bonbon, pierres) : jouée avec le sac KANTO (option SAC), sac HOENN comme Émeraude ; hors combat seulement (comme RF). Le refus d'évolution hors Pokédex de Kanto de RF n'est pas repris (règle d'Émeraude)
- [x] Note du Pokédex par Chen (2026-10-23) : GetProfOaksRatingMessage de RF (PC, Chen en personne, ses aides) ; « PC du PROF. CHEN » ajouté au menu PC à Kanto une fois son Pokédex reçu
- [x] TOUTES les cinématiques de RF (2026-10-23) : départ du S.S. Anne, ferry Seagallop, et les autres stubs de `kanto_specials_stubs.c` (éclairage de la Ligue, téléporteurs de Léo, triangle de Deoxys, fossiles du musée, diplôme…)
- [x] IA des légendaires de RF (2026-10-23, `gBattleLegendaryFrlg` : StartLegendaryBattle de Kanto, IA « mauvaises attaques + K.O. + viabilité ») — sans effet en jeu, dans RF aussi : l'IA n'est consultée que pour les dresseurs, le Safari, les errants et le premier combat ; idem pour les sauvages scriptés (`gBattleWildScriptedFrlg`, 2026-10-24)

Choix HOENN / KANTO :
- [x] PC objets (2026-10-24) : interface de RF avec l'option MENUS = KANTO (RETIRER = PC objets plein écran de RF, `kanto_item_pc.c` ; boîte aux lettres aux fenêtres de RF) ; les objets stockés restent communs aux deux régions (même stockage). Les interfaces de RF suivantes (boutique, Maître des capacités) passent aussi par MENUS
- [x] Maître des capacités (2026-10-24) : interface de RF avec MENUS = KANTO (`kanto_learn_move.c`), rendu seulement. Les deux proposent déjà les mêmes attaques (capacités par niveau, mêmes données) : rien à fusionner
- Donneurs de capacités : chacun reste exclusif à sa région (pas de changement)
- [x] Boutique (2026-10-24) : interface de RF avec MENUS = KANTO (`kanto_shop.c` ; boutiques de décorations d'Émeraude inchangées)
- [x] Machine à sous (2026-10-24) : PAS d'option, chacune dans sa région (celle de RF au Casino de Céladopole, `kanto_slot_machine.c` ; celle d'Émeraude à Lavandia)
- [x] Menu Start de RF : déjà par MENUS = KANTO (police, espacement, curseur, descriptions de RF) ; nom du joueur
  en police de RF aussi (`Menu_PrintFormatIntlPlayerName` de RF, 2026-10-31)
- [x] Menu Options en pages (2026-10-23, L/R ; titre « {L}{R} PAGE 1/2 : JEU » / « PAGE 2/2 : HOENN/KANTO » ; page 2 : PERSO, POKéMON, DIALOGUE, BOITES COMBAT, MENUS, SAC, POKéDEX, TITRE, INTRO) : page 1 = réglages d'Émeraude, page 2 (et suivantes) = choix HOENN/KANTO ; indiquer clairement qu'il y a d'autres pages (ex. « PAGE 1/2 » et flèches L/R dans le titre)

## Notes
- Piste (utilisateur) : Émeraude a été construit à partir de Rouge Feu ; il garde des fonctions vidées et des entrées inutilisées de RF (ex. BgTileAllocOp « Dummied out », LoadMonPicInWindow UNUSED). Les rétablir avec le code de RF avant de réinventer.
- Comparaison des cadres : script PIL (pixels RGB identiques) ; refaire de même pour chaque liste.
- Les choix d'option sont dans gSaveBlock2Ptr (bits libres) ; au-delà, gSaveBlockKanto.
