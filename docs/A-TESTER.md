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
- [ ] Cherche VS (Kanto) : recharge de 100 pas (message « Il faut faire X pas » vérifié en headless, scénario `kanto_vs_seeker.py`) ; sur une route avec des dresseurs déjà battus : le joueur lève le Cherche VS, des dresseurs lèvent la main (!!) ou refusent (X), revanche avec les équipes de RF ; les dresseurs se calment au changement de carte. Pose du joueur seulement avec Red/Leaf (Brice/Flora n'ont pas ce sprite). Hoenn : PokéNav inchangé
- [ ] Course (B) dans les intérieurs : maisons, Centres Pokémon, grottes, à Hoenn et à Kanto
- [ ] Cherch'Objet : à Kanto, flèches de RF vers l'objet + messages de RF (vérifié en headless, `kanto_itemfinder.py`) ; à Hoenn, celui d'Émeraude (le joueur se tourne). Couleur des flèches (palette du joueur)
