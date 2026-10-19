# À tester en jeu

Ce que ni l'utilisateur ni Claude n'ont vérifié en jeu. Cocher (`[x]`) une fois vu. Lancer Kanto
directement : `out/winwsl/pokeemeraude64.exe --kanto-start 1` (build KANTO_DEBUG=1 : menu DEBUG du menu Start).

Déjà vérifiés (pour mémoire) : escaliers latéraux de RF, défilement du menu Options, sprite RED sur la
carte et la carte dresseur, intro du camion / `--kanto-start`, palette du dos de RED en combat, nom du
rival dans son texte de victoire, téléporteur de l'arène de Safrania, marche lente sur les escaliers de
roche (Plateau Indigo), dresseurs d'Argenta.

## Option PERSO (RED / LEAF)
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
