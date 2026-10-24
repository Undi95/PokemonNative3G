# À tester en jeu

Ce que ni l'utilisateur ni Claude n'ont vérifié en jeu. Cocher (`[x]`) une fois vu. Lancer Kanto
directement : `out/winwsl/pokeemeraude64.exe --kanto-start 1` (build KANTO_DEBUG=1 : menu DEBUG du menu Start).

Déjà vérifiés (pour mémoire) : escaliers latéraux de RF, défilement du menu Options, sprite RED sur la
carte et la carte dresseur, intro du camion / `--kanto-start`, palette du dos de RED en combat, nom du
rival dans son texte de victoire, téléporteur de l'arène de Safrania, marche lente sur les escaliers de
roche (Plateau Indigo), dresseurs d'Argenta.

- [ ] F5 = reset du jeu (retour à l'écran titre) ; touche modifiable via `key_reset` dans pokeemerald.ini (ligne ajoutée automatiquement aux .ini existants)



## Option SAC (HOENN / KANTO)
- [ ] Options > SAC = KANTO : sac de Rouge Feu depuis le menu Start (poches Objets / Objets rares / Balls, L/R ou gauche/droite, SELECT pour déplacer un objet, jeter, enregistrer). Vérifiés en headless : poches, menu d'un objet, Vélo depuis le sac, message du Seau Wailmer (`kanto_bag.py`)
- [ ] Boîte à CT et Sac à Baies en tête des Objets rares (disparaissent avec SAC = HOENN) : liste, apprendre une CT (retour à la Boîte à CT), utiliser une baie (retour au Sac à Baies). Vérifiés en headless (`kanto_tm_case.py`, `kanto_berry_pouch.py`)
- [ ] Sac de RF en combat : Balls (vérifié : MASTER BALL, `kanto_bag_battle.py`), POTION sur un Pokémon, Sac à Baies en combat (OUVRIR)
- [ ] Sac de RF pour : donner un objet depuis l'équipe, vendre en boutique (et vendre des CT / baies depuis la Boîte à CT / le Sac à Baies), déposer au PC (objets), donner un objet depuis le PC (boîtes)
- [ ] Boîte à CT / Sac à Baies enregistrés sur SELECT, ouverts depuis la carte
- [ ] SAC = HOENN : le sac d'Émeraude comme avant (arbres à baies, mixeur, dames : toujours le sac d'Émeraude)
- [ ] Sac de RF : scène de RF quand on utilise un objet sur un Pokémon hors combat (2026-10-24, kanto_pokemon_special_anim*.c). Vérifié en headless : SUPER BONBON (scène, puis « monte au N. 71 » et statistiques dans le menu d'équipe ; `kanto_item_use_anim.py`). Non testés : soins (POTION, TOTAL SOIN…), HUILE / ÉLIXIR (choix de la capacité puis scène), CT/CS (scène « appareil prêt »), CT en remplaçant une capacité (« 1, 2 et… Tadaa ! » dans la scène), pierres d'évolution (scène puis évolution), objet sans effet (message sans scène). En combat : pas de scène (comme RF)
- [ ] Option MENUS = KANTO, PC du joueur (2026-10-24) : RETIRER OBJET ouvre le PC objets plein écran de RF (kanto_item_pc.c) ; vérifié en headless (`kanto_item_pc.py` : POTION retirée, retour au sous-menu). Non testés : DONNER un objet du PC à un Pokémon, déplacer (SELECT), plusieurs objets / défilement. Boîte aux lettres avec les fenêtres, la police et les textes de RF : non testée (il faut des lettres au PC)
- [ ] Option MENUS = KANTO, boutiques (2026-10-24) : menu ACHETER/VENDRE/QUITTER et écran d'achat de RF (kanto_shop.c, case « ARGENT » de RF) ; vérifié en headless à Argenta (`kanto_shop.py` : liste, description, quantité, confirmation). Non testés : achat effectif (argent retiré, objet dans le sac), boutique de CT (fenêtres de CT), VENDRE (sac du style choisi puis retour à la boutique), Hoenn avec MENUS = KANTO. Boutiques de décorations : toujours celles d'Émeraude. Police du vendeur (homme/femme de RF) : police de RF normale en attendant
- [ ] Option MENUS = KANTO, Maître des capacités (2026-10-24) : écran de RF (kanto_learn_move.c, descriptions des capacités de RF) ; vérifié en headless à l'Île 2 (`kanto_move_relearner.py` : liste, panneau de la capacité, « MEWTWO tente d'apprendre… »). Non testés : oubli d'une capacité (résumé), apprentissage réel, champignons donnés, celui de Vergazon (Hoenn) avec MENUS = KANTO. Résumé KANTO : descriptions des capacités de RF aussi
- [ ] Casino de Céladopole (2026-10-24) : machine à sous de RF (kanto_slot_machine.c) ; celle d'Émeraude reste à Lavandia. Vérifié en headless (`kanto_slot_machine.py` : icône sourire, mise, rouleaux, « Quitter la partie? », retour au Casino ; DEBUG « Ajout objets » donne l'étui à jetons et 500 jetons). Avant : le Casino se bloquait (FLDEFF_SMILEY_FACE_ICON vide). Non testés : gains (7, Pikachu…), Mélofée qui danse, plus de jetons. Flash photo de la carte dresseur de Kanto (FLDEFF_PHOTO_FLASH, aussi vide avant) : non testé
- [ ] CÂBLE LINK (2026-10-24) : vérifié en headless avec le sac d'Émeraude (`link_cable.py` : KADABRA → ALAKAZAM ; DEBUG « MEWTWO + KADABRA »). Non testés : achat en boutique, évolution avec objet tenu (Onix + Peau Métal…), Pokémon qui ne peut pas évoluer (message), sac de RF, Pierre Stase
- [ ] Exclusivités de version dans les hautes herbes (2026-10-24, non testé en jeu) : Kanto : Chétiflor Routes 5-7, 12-15, 24-25 et îles Sevii (Forêt Baies, Cap Falaise, Pont Lien, Chemin des Eaux), Magmar Mont Braise, Farfuret Grotte de Glace (1F), Feuforêve Caverne Perdue, Démanta (Surf) Tour des Dresseurs ; Hoenn : Arakdo Routes 102/117 (herbe, 1 %) et 102/111/114/117 (Surf), Rosélia Route 117, Mangriff Route 114, Séléroc Chutes Météore, Méditikka Mont Mémoria (extérieur), Charmina Route Victoire
- [ ] Œufs des starters manquants (2026-10-24) : vérifié en headless à Kanto (`starter_eggs.py` : DEBUG « Carte de vol » = Ligue de Kanto finie, pension de l'Île 4 : trois OEUFS un par visite, puis « plus d'OEUF »). Non testés : à Hoenn (pension de la Route 117, après la Ligue ; Johto après le choix chez SEKO), avant la Ligue (« reviens quand tu seras MAÎTRE »), équipe pleine, éclosion (bonne espèce)
- [ ] Celebi (2026-10-24) : vérifié en headless (`celebi.py` : DEBUG « Deux Ligues finies », téléport FORÊT BAIES, autel, CELEBI apparaît, combat N.30, vaincu → « s'est enfui »). Non testés : capture, fuite puis retour, autel avant les Ligues (texte simple), rendu de l'autel (dessin maison) avec Red/Leaf
- [ ] Jirachi (2026-10-24) : vérifié en headless (`jirachi.py` : DEBUG objets + « Deux Ligues finies », téléport CHUTES MÉTÉORE, météorite, POKé FLÛTE de RF, combat N.30, vaincu → la météorite ne brille plus). Non testés : flash spécial sur une TV de Hoenn (en partie debug, la maison du joueur est encore en déménagement), sans POKé FLÛTE (texte d'explication), capture, fuite puis nouvel essai, météorite absente avant les Ligues
- [ ] CADEAU MYSTÈRE (2026-10-24) : vérifié en headless (`fusion_mystery_gift.py` : DEBUG « Carte de vol » = RUBIS/SAPHIR rendus, sauvegarde, reset ; CADEAU MYST. au menu principal, 3 CARTES MYSTÈRE, objets reçus, sauvegarde, l'option a disparu). Non testés : les traversées (Nénucrique : ILE AURORE, ROC NOMBRI, ILE LOINTAINE ; Carmin sur Mer en Seagallop : ROC NOMBRI, ILE AURORE) et le retour à Carmin par le marin de l'île (multichoix de RF), Ho-Oh/Lugia/Deoxys/Mew une seule fois quel que soit le port de départ
## Plateformes (docs/PLATEFORMES.md)
- [ ] Android : installer `out/android/PokemonNative3G.apk` (autoriser les sources inconnues), le jeu démarre en paysage, son OK, icône = celle de Windows
- [ ] Android : touches tactiles (croix 8 directions, A/B, L/R, SELECT / RESET / START ; RESET maintenu 1 s = retour à l'écran titre), plusieurs doigts à la fois
- [ ] Android : sauvegarder, quitter l'appli, relancer → la sauvegarde est là ; mettre en arrière-plan puis revenir
- [ ] Android : manette Bluetooth
- [ ] Linux : `out/linux/pokeemeraude64` sur une vraie machine Linux (SDL2 installé), fenêtre + son + manette
## Option PERSO (RED / LEAF)
- [ ] Sprites faits pour Red/Leaf (tools/redleaf_sprites.py, d'après Brendan/May) : Vélo Cross (roue arrière, sauts, plus de crash ; Red vérifié en headless, scénario `redleaf_acro.py`), arrosoir (baies), plongée (sous l'eau). Dire si une pose cloche
- [ ] LEAF partout : carte, carte dresseur, dos en combat (et ses frames de lancer)
- [ ] RED / LEAF : vélo (Course et Cross), surf, pêche, capacité de terrain (Coupe, Éclate-Roc…)
- [ ] « ! », « ? » et flèches de sortie en blanc avec RED/LEAF, à Hoenn et à Kanto
- [ ] Repasser en BRICE/FLORA : tout redevient Émeraude

## Combat
- [ ] Perdre contre le rival de la Route 22 : texte du rival puis retour au Centre (plus de crash)
- [ ] Légendaires de Kanto (Mewtwo, Électhor, Sulfura, Artikodin, Deoxys, Lugia, Ho-Oh) : musique RF
- [ ] Îles du Sud (Latios/Latias via ticket) : combat lancé

## Warps et terrain de RF
- [ ] Trous (MB_FALL_WARP) : Îles Écume, Caverne Azurée… on tombe à l'étage du dessous
- [ ] Rocher de Force poussé dans un trou (Îles Écume) : il disparaît et réapparaît en dessous
- [ ] Interrupteurs de la Route Victoire : un rocher dessus déclenche l'ouverture
- [ ] Courir (Chaussures de Course) sur les escaliers de roche : course ralentie
- [ ] Vélo Course sur les escaliers de roche : bridé à la 2e vitesse ; Vélo Cross normal
- [ ] Glace de la grotte Gelée (Îles Sevii) : se fissure puis casse ; état gardé en ressortant
- [ ] Courant des Îles Écume B4F : dépose le joueur sur la terre

## Specials de RF (scripts de Kanto)
- [ ] PC qui s'allume / s'éteint (Centres Pokémon, chambre du joueur)
- [ ] Ascenseurs : Centre Commercial de Céladopole, Sylphe SARL, repaire Rocket (fenêtre « Niveau: », secousse, vue)
- [ ] Menus de liste RF (badges, étages de Sylphe SARL, poudre de baies)
- [ ] Vendeurs des Boutiques Pokémon (bon PNJ qui parle)
- [ ] Casino de Céladopole : machines à sous
- [ ] Vérificateur de surnoms (Lavanville)
- [ ] Poubelles de Carmin (arène du Major Bob)
- [ ] Poupées de Lorelei (Île 4), Homme aux stickers, icônes de la carte dresseur (photo)
- [ ] Resort Gorgeous (Île 5) : Pokémon demandé et récompense
- [ ] Massage de Daisy (Bourg Palette) : amitié +3, attente de 500 pas
- [ ] Cap Falaise (Île 2) : Végé-Attaque / Rafale Feu / Hydroblast
- [ ] Pension de la Route 5 : déposer, gagner des niveaux en marchant, reprendre (et après sauvegarde)
- [ ] Pension de l'Île 4 : coût, courrier
- [ ] Records de taille : Scarabrute et Magicarpe
- [ ] Fan Club de Safrania : fans gagnés / perdus, noms
- [ ] Poudre de baies (échange contre objets)
- [ ] Effaceur de capacités, menu du PC, sauvegarde demandée par un script, PC du Panthéon (version Émeraude)
- [ ] Perte d'argent affichée après un K.O. hors combat (poison) à Kanto
- [ ] Battements d'ailes (son), drapeaux d'après-Ligue

## Démarrage
- [ ] Nouvelle partie : ID dresseur différent à chaque partie (avant : partie basse toujours 0 sur PC)
- [ ] Rencontres / shiny : résultats différents d'un lancement à l'autre (graine aléatoire corrigée)

## Vagabonds
- [ ] Île 1 (après le Réseau Sevii) : Raikou, Entei et Suicune lâchés tous les trois à Kanto, N.50
- [ ] Les rencontrer sur les routes de Kanto ; ils changent de route ; PV/statut gardés entre deux combats
- [ ] Un chien qui utilise Hurlement : il reste en liberté (avant : disparu pour toujours)
- [ ] IV des chiens normaux (pas seulement PV/Attaque)
- [ ] Hoenn : Latios ou Latias (choix à la TV) toujours là, indépendant des chiens

## Carte dresseur
- [ ] À Hoenn : carte d'Émeraude + badges de Hoenn ; SELECT → carte de Kanto + badges de Kanto
- [ ] À Kanto : la carte de Kanto s'ouvre d'abord ; le portrait suit l'option PERSO sur les deux cartes (BRICE/FLORA ou RED/LEAF)
- [ ] Verso des deux cartes (A)

## Écran titre
- [ ] Options → TITRE = R.FEU, sauvegarder, relancer : écran titre de Rouge Feu (Dracaufeu, flammes, cri)
- [ ] Depuis cet écran : START → menu principal ; Haut+Select+B → effacer la sauvegarde ; attente → intro
- [ ] Intro de Groudon/Kyogre (fonds 8bpp) toujours correcte après la correction du rendu 8bpp

## Fusion (options et contenus)
- [ ] Options > FENETRE : cadres 21 à 29 = cadres de Rouge Feu (boîtes de dialogue, menus)
- [ ] PC > boîte > FONDS > KANTO > KANTO 1-4 : les 16 fonds de Rouge Feu, titre de boîte lisible, sauvegardés
- [ ] Options > DIALOGUE = KANTO : boîte de dialogue de Rouge Feu partout (PNJ, panneaux, combats ? non concernés) ; texte lisible, pas de reste de cadre à la fermeture
- [ ] DIALOGUE = KANTO : fenêtre de RF (26 colonnes, 4 coins) + police de RF. Les textes d'Émeraude trop larges pour la police de RF (~4 % des lignes) gardent la police d'Émeraude automatiquement ; une soixantaine de lignes d'Émeraude dépassent même 26 colonnes : signaler si un texte est coupé à droite
- [ ] Options > BOITES COMBAT = KANTO : boîtes de PV/EXP, barres, statuts et boîte de texte de combat de Rouge Feu (simple, double, Safari) ; le menu ATTAQUE/SAC/POKéMON/FUITE et le choix des attaques restent lisibles
- [ ] Options > POKéDEX = KANTO : Pokédex de Rouge Feu depuis le menu Start (sommaire, liste numérique/A-Z/type/poids/taille, habitats, fiche, page Taille/Zone avec les zones de Kanto et des Îles Sevii, chiens errants) et après une capture (enregistrement façon RF). Le debug « Recevoir MEWTWO » donne aussi le Pokédex avec les 151 de Kanto vus
- [ ] Option POKéDEX absente des Options tant que le Prof. Chen n'a pas donné son Pokédex (labo de Bourg Palette), présente ensuite. Debug : « Débloquer les 2 POKéDEX » (MEWTWO ne donne plus le Pokédex)
- [ ] Modes du Pokédex de Kanto (habitats Champs…, A à Z, type, poids, taille) : ne plantent plus, vérifiés en headless (scénario `kanto_dex_modes.py`) ; à revoir en jeu (pages d'habitat, tourner les pages)
- [ ] Options > MENUS = KANTO : menu Start de RF (police, espacement, bande de description bleue en bas qui suit le curseur ; 8 entrées avec le POKéNAV : resserrées, la bande reste visible), équipe aux couleurs de RF, résumé du Pokémon de RF (pages INFOS/STATS/CAPACITÉS, changer de Pokémon, depuis l'équipe, le PC, l'échange ; apprendre une capacité au niveau supérieur, Maître des capacités / Effaceur)
- [ ] Animations des tuiles de Kanto (RF) : fleurs, eau et sable des rivages, fontaines de Céladopole et de Sylphe SARL, vapeur du Mont Braise, fleurs de l'arène de Céladopole, porte motorisée de l'arène de Carmin
- [ ] Centre Pokémon de Kanto : moniteur de soin qui clignote (RF), écran du PC qui s'allume/s'éteint (RF), aussi le PC de la chambre

- [ ] Kanto : musique des crédits continue sur tout le défilé ; moniteur RF (pas les écrans d'Émeraude) à l'enregistrement du Panthéon ; fonds de boîtes de Kanto aux bonnes couleurs.
- [ ] Sprites Red/Leaf vélo cross refaits : pédalage = images de vélo de Rouge Feu telles quelles, plus de noir, tête dans la bonne direction sur les figures. Revérifier roue arrière + sauts.
- [ ] CS à Kanto : badges de Kanto (Roche = Flash, Cascade = Coupe, Foudre = Vol, Prisme = Force, Âme = Surf, Marais = Éclate-Roc, Volcan = Cascade) depuis le menu d'équipe et sur l'eau (Surf, Cascade) ; à Hoenn, badges de Hoenn comme avant
- [ ] Options > POKéMON = KANTO : sprites de Rouge Feu (face, dos, couleurs, shiny) sans animation, en combat (sauvage, dresseur, double), résumé, Pokédex, PC, évolution, éclosion ; Deoxys = forme Attaque. HOENN = animés d'Émeraude comme avant
- [ ] Deoxys : menu de l'équipe > FORME > NORMALE / ATTAQUE / DÉFENSE / VITESSE : message, sprite (face et dos, combat, résumé) et stats de la forme ; par défaut VITESSE (comme Émeraude). Forme commune à tous les Deoxys du joueur
- [ ] Obéissance : à Kanto, paliers des badges de Kanto (2 = N.30, 4 = N.50, 6 = N.70, 8 = tous) ; à Hoenn, ceux de Hoenn
- [ ] Carte de Kanto (RF) : Vol depuis Kanto (vérifié en headless, scénario `kanto_fly_map.py`), objet CARTE (sac et SELECT), cartes murales de Kanto ; bascule Kanto / Îles Sevii (bouton en bas à droite) ; aperçu des donjons (A sur une grotte)
- [ ] Vol entre régions : après la Ligue de Kanto + Rubis/Saphir rendus à Célio, SELECT sur la carte de vol = carte de l'autre région (vérifié en headless) ; voler réellement vers l'autre région et y atterrir
- [ ] Cherche VS (Kanto) : recharge de 100 pas (message « Il faut faire X pas » vérifié en headless, scénario `kanto_vs_seeker.py`) ; sur une route avec des dresseurs déjà battus : le joueur lève le Cherche VS, des dresseurs lèvent la main (!!) ou refusent (X), revanche avec les équipes de RF ; les dresseurs se calment au changement de carte. Pose du joueur seulement avec Red/Leaf (Brice/Flora se tournent vers le bas). Les dresseurs de Kanto qui sautent (gamins, campeurs, montagnards…) ne sautaient pas avant (graphicsId tronqué, corrigé)
- [ ] Cherche VS (Hoenn, 2026-10-23) : dresseurs inscrits au PokéNav seulement ; « !! » puis ils sautent, « X » sinon, « ! » s'ils n'ont jamais été battus. Vérifié en headless (`hoenn_vs_seeker.py`, DEBUG > Revanches PokéNav + téléport ROUTE 102) : Rick « ! », Calvin « !! » puis combat de revanche (Grahyena N.27). Non vérifié : Calvin cesse de sauter après une revanche GAGNÉE (le Mewtwo du debug ne peut pas battre Grahyena) ; le PokéNav montre bien Calvin prêt pour une revanche. Avant ce correctif, le Cherche VS bloquait le jeu avec Brice/Flora dès qu'un dresseur était à portée
- [ ] Icônes « !! » et « X » du Cherche VS : maintenant dans le bon ordre (fichiers inversés à l'import) et aux couleurs de RF (bulle bleue et blanche, palette de leur image) avec tous les persos
- [ ] Course (B) dans les intérieurs : maisons, Centres Pokémon, grottes, à Hoenn et à Kanto
- [ ] Cherch'Objet : à Kanto, flèches de RF vers l'objet + messages de RF (vérifié en headless, `kanto_itemfinder.py`) ; à Hoenn, celui d'Émeraude (le joueur se tourne). Couleur des flèches (palette du joueur)
- [ ] Combat FANTÔME (Tour Pokémon, 2026-10-23). Vérifié en headless :
  - `kanto_ghost.py` (DEBUG > TOUR POKéMON 3, sans Scope Sylph) : « Le SPECTRE apparaît ! Mince ! Le SPECTRE ne peut être identifié ! », image du SPECTRE, « MEWTWO a peur de bouger ! », « SPECTRE : Va t'en… Dehors… » (écran assombri), FUITE réussie ;
  - `kanto_giovanni.py` (DEBUG > REPAIRE ROCKET) : combat contre Giovanni, Scope Sylph ramassé, puis TOUR POKéMON 6 : « Le SCOPE SYLPHE révèle l'identité du SPECTRE ! » (mosaïque), « Le SPECTRE était OSSATUEUR ! », victoire, suite du script (l'âme de la mère d'Osselait) ;
  - `kanto_marowak.py` (DEBUG > Ajout objets, donc Scope Sylph) : même combat révélé.
  Non vérifié : Ossatueur SANS Scope Sylph (fuite, le joueur est repoussé dans l'escalier) ; Ball lancée sur un SPECTRE (« Il a évité la BALL ! », la Ball rebondit) ; Pokédex : un SPECTRE non révélé ne doit pas être marqué « vu »
- [ ] Cherche VS avec Red/Leaf : le sprite levant le Cherche VS était faux (numéro de sprite tronqué à 8 bits, corrigé)
- [ ] Menu Options en 2 pages (L/R, vérifié en headless `options_pages.py`) : page 1 = réglages d'Émeraude, page 2 = choix HOENN/KANTO ; RETOUR sur chaque page. En mode boutons L=A, L sert aussi de A (R change toujours de page)
- [ ] Objets cachés qui réapparaissent (Kanto, non testé) : Route 20, 21 Nord, souterrains, etc. (15 cartes de RF). Cachés en début de partie ; après 1 500 pas, en entrant sur une de ces cartes, un tirage en fait réapparaître (rares 10 %, peu communs 30 %, communs 60 %). Avec le Cherch'Objet de Kanto
- [ ] Chen dans la salle du champion de Kanto : rappelle maintenant le starter choisi à Kanto (il lisait celui de Hoenn). Même correctif pour le special IsStarterFirstStageInParty
- [ ] Note du Pokédex par Chen (vérifié en headless `kanto_oak_pc.py`) : à Kanto, menu PC = PC de ???, PC de <joueur>, PC du PROF. CHEN, (PANTHEON), DECONNEXION ; note selon le nombre de Pokémon de Kanto attrapés. Non vérifiés : Chen en personne au labo (Bourg Palette) et ses aides sur les routes, qui utilisent la même fonction (avant, elle ne faisait rien)
- [ ] Légendaires de Kanto (Mewtwo, Électhor, Sulfura, Artikodin…) : IA de RF (évite les attaques inutiles, cherche le K.O.) ; non visible en headless
- [ ] Ferry Seagallop (2026-10-23 ; avant, la traversée ne faisait rien, le voyage ne pouvait pas se faire). Vérifié en headless : `kanto_seagallop.py` (DEBUG > PORT ÎLE 1 : Île 1 -> Île 2 et retour, traversée de RF : mer, ferry, sillage), `kanto_seagallop_menu.py` (DEBUG > Pass îles Sevii : menu des destinations de RF en 2 pages, Île 1 -> Île 7). Nombril du Monde et Île Aurore : arrivée en (8,4) sur les ports d'Émeraude (le marin est en 8,5)
- [ ] Départ du S.S. Anne (ss_anne.c de RF ; AVANT : le jeu se bloquait en sortant du bateau avec la CS Coupe). Vérifié en headless `kanto_ss_anne.py` (DEBUG > Départ S.S. Anne) : corne, fumée, sillage, le bateau quitte l'écran, retour à quai. Sillage et fumée prennent la palette du bateau (RF : palette 10)
- [ ] DEBUG > PORT ÎLE 1 : maintenant au-dessus du marin (en dessous, on était coincé ; signalé par l'utilisateur)
- [ ] Diplôme de Game Freak à Céladopole (diploma.c de RF ; AVANT : le jeu se bloquait). Vérifié en headless `kanto_diploma.py` (DEBUG > POKéDEX Kanto complet, téléport GAME FREAK). « POKéDEX NATIONAL » si tous les Pokémon sont attrapés (non testé)
- [ ] Scènes de RF (2026-10-23), vérifiées en headless `kanto_scenes.py` : image des fossiles du musée d'Argenta (DEBUG > MUSÉE ARGENTA ; palette allouée au lieu de la palette 13 de RF), éclairage de la Ligue (DEBUG > LIGUE : OLGA ; couleurs du sol en boucle). Non testé : téléporteurs de la maison de Léo (Route 25, pendant l'histoire de Léo)
- [ ] Poké Flûte (RF, 2026-10-23) : depuis le sac sur le terrain vérifié en headless (`kanto_poke_flute.py` : « Super!!! Ça c'est du refrain! »). Non testés : réveil d'un Pokémon endormi (fanfare) et usage en combat (réveille tout le monde sauf Anti-Bruit)
- [ ] MEMORYDEX (Fame Checker de RF, 2026-10-23) : vérifié en headless depuis le sac avec DEBUG « MEMORYDEX complet » (`kanto_fame_checker.py` : liste, fiches, lecture, portrait + citation avec START, retour au sac). Non testés : enregistré sur SELECT et ouvert depuis la carte (SELECT ferme alors l'écran), fiches qui se débloquent en parlant aux PNJ / lisant les panneaux, Giovanni qui change de place une fois battu à l'arène de Jadielle
- [ ] Tour des Dresseurs (Île 7, RF, 2026-10-24) : vérifiés en headless avec DEBUG « TOUR DRESSEURS » : accueil, défi SOLO, chrono, 1er étage, combat (image et réplique Easy Chat du dresseur, Pokémon au niveau de l'équipe), défaite → retour au hall (`kanto_trainer_tower.py`) ; tableau des temps (`kanto_trainer_tower_records.py`). Non testés : victoire (réplique de défaite du dresseur, étage franchi), DUO / KO / MIXTE (dispositions d'étage posées par le code), toit (prix, temps final, record), abandon impossible (comme RF), Infirmière et vendeur du hall
- [ ] Aperçus des lieux de RF (2026-10-24) : vérifiés en headless : MONT SÉLÉNITE depuis la Route 4 (grotte : image + nom, puis transition d'entrée ; `kanto_map_preview.py`) et FORÊT DE JADE depuis le poste nord (forêt : fondu sur la carte ; `kanto_map_preview_forest.py`). Non testés : les 26 autres lieux, durée plus courte aux visites suivantes, B pour passer l'aperçu d'une grotte
- [ ] Club Mystery Event de Kanto (2026-10-24) : donner son profil Easy Chat, le PNJ le répète (special ShowEasyChatMessage de RF = ShowEasyChatProfile d'Émeraude). Non testé

