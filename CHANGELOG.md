# PokemonNative3G — Changelog

## Prochaine version

### Corrections
- Nouvelle partie par-dessus une sauvegarde avec la boîte de dialogue KANTO : l'intro du Prof. Seko avait un cadre
  cassé et un texte bleu, et la partie démarrait avec le personnage de l'ancienne partie (Red à Hoenn). Les options
  d'affichage sont gardées, le personnage est celui choisi dans l'intro.
- Fiche du Pokémon de Rouge Feu (MENUS = KANTO) : le sprite animé ne reste plus figé sur sa dernière image, et un
  Pokémon rencontré à Hoenn n'est plus « rencontré à un échange » (le lieu est affiché).
- Boîte de dialogue de Rouge Feu : la flèche rouge n'est plus coupée ou cachée en bout de ligne.
- Cycle jour/nuit : l'animation qui lance un combat garde la teinte (le terrain repassait en couleurs de jour).
- Le fichier de réglages du PC ne grossit plus d'une ligne à chaque lancement.
- Listes de Rouge Feu (badges de la maison d'Azuria, étages de l'ascenseur de Sylphe SARL, échange de Poudre Baie) :
  la 4ᵉ ligne n'est plus coupée par le bas de la fenêtre.
- Options : avec la police KANTO, le titre de la page (« L R 2/2 : HOENN/KANTO ») ne recouvre plus « OPTIONS ».
- Dôme de Combat : le tableau du tournoi précédent (panneau du hall) ne fait plus planter le jeu en ouvrant la fiche
  d'un dresseur ou d'un match, ni en y revenant.
- Arène de Céladopole : le combat contre la Pique-nique TINA faisait planter le jeu (ou, après un autre combat,
  reprenait l'équipe de ce combat, donnait 0 ¥ et recommençait sans fin). La Pique-nique SOFIA (Grotte, sous-sol)
  avait l'image et le nom de la Tête de la Zone de Combat. Leurs numéros étaient ceux d'adversaires spéciaux
  d'Émeraude (Base Secrète, Tête de la Zone de Combat).
- Crédits de Kanto : le métier et les noms s'écrivent de nouveau sur leurs lignes (depuis la 1.1, ils s'écrivaient
  l'un sur l'autre sur une seule ligne, « DiJunichi Masuda »).
- Dôme de Combat : la fiche du joueur dans le tableau ne fait plus planter le jeu quand ses Pokémon n'ont aucun EV.
- Mont Combat : les étages s'affichent de nouveau (tuiles magenta, dresseurs absents, joueur bloqué) ; ils étaient
  lus au mauvais endroit sur PC et Android.

## Version 1.1 (1er novembre 2026)

### Ajouts
- **Cycle jour/nuit** (Options, page 1, JOUR/NUIT ; désactivé par défaut) : dehors, la lumière suit l'heure de
  l'appareil (matin doré, coucher de soleil orangé de 17 h à 21 h, nuit bleutée de 21 h à 5 h). Purement visuel :
  mêmes Pokémon à toute heure, boîtes de texte et menus intacts.
  - Le soir et la nuit, les fenêtres des maisons et des bâtiments s'allument, vitre par vitre, avec leurs reflets et
    leurs meneaux ; les lampes du Casino de Lavandia et du Bâtiment des Jeux de l'Île 2, les lampadaires de
    Mérouville et l'emblème des Tentes de Combat aussi.
  - La nuit désature un peu les couleurs (les fleurs ne brillent plus comme des lampes).
  - Les portes gardent leur vitre allumée pendant qu'elles s'ouvrent et se ferment.
- **Mentali / Noctali** : la nuit d'évolution suit le cycle, de 20 h à 6 h (avant : minuit à midi).
- **Police** (Options, page 2, POLICE HOENN / KANTO) : la police choisie sert à tous les textes du jeu, dans les deux
  régions (dialogues, combat, menus, sauvegarde, sac, équipe, résumé, écrans de Rouge Feu…). La police de Rouge Feu
  étant un peu plus large, une ligne qui ne tient plus resserre ses espaces ou passe à la ligne. L'option DIALOGUE ne
  change plus que la boîte (cadre, largeur, interligne). Par défaut : HOENN ; avec les réglages par défaut, les
  écrans de Rouge Feu sont donc maintenant écrits avec la police d'Émeraude.

### Corrections
- Tour des Dresseurs (Île 7) : la troisième ligne de la phrase des dresseurs était coupée ; elle défile comme dans
  Rouge Feu.
- Sac à Baies (sac de Kanto) : la troisième ligne de la description des baies était coupée.
- Argent : un montant à 6 chiffres dépassait de sa case avec la police de Rouge Feu.
- Description de la POKé MONTURE : elle dépassait de la fenêtre du sac.
- Dôme de Combat : une lecture hors limites du code d'origine d'Émeraude en calculant les résultats d'un tournoi.

## Version 1.0 (31 octobre 2026) — première version complète

Pokémon Émeraude et Pokémon Rouge Feu réunis en un seul jeu, en natif sur PC et sur téléphone (pas un
émulateur). Hoenn puis Kanto et les îles Sevii, de la première ville aux deux Ligues et à tout le post-game, en
solo. Le multijoueur (échanges, combats en link, Salle Union) n'est pas encore là.

### Contenu
- **L'aventure d'Émeraude à Hoenn, puis celle de Rouge Feu à Kanto et aux îles Sevii**, avec leurs scénarios,
  dresseurs, arènes, Ligues, crédits et Panthéons (un par région).
- **Le passage vers Kanto** : après la Ligue de Hoenn, le ferry de Poivressel ou de Nénucrique propose KANTO. Le
  premier voyage est un aller simple : on repart comme au premier jour, sans son équipe (elle reste au PC de
  Hoenn), jusqu'à devenir Maître de Kanto et aider Célio à relier les deux régions. Ensuite, ferry et vol entre les
  régions.
- **Les 386 Pokémon obtenables en solo** : exclusivités de Rubis, Saphir et Vert Feuille ajoutées dans la nature,
  les trois chiens légendaires errent à Kanto, starters manquants en œufs à la pension après chaque Ligue, Celebi et
  Jirachi après les deux Ligues, CADEAU MYSTÈRE sans connexion (TICKET AURORA, TICKET MYSTIK, VIEILLE CARTE,
  PASSE EON) une fois les régions reliées. Évolutions par échange avec le CÂBLE LINK, vendu dans toutes les
  boutiques. Guide complet : `Où trouver les Pokémon.md`, dans ce dossier.
- **POKé MONTURE à Kanto** à la place des CS (un Pokémon des environs vient couper, surfer, voler…).
- **Post-game** : Zone de Combat, Tour des Dresseurs (Île 7), Cherche VS dans les deux régions, maison à acheter
  à Bourg Palette, cannes améliorées (chaîne de pêche chromatique), OVO-CHRONO, CHARME CHROMA, CHARME OVALE.

### Options HOENN / KANTO
Le style des deux jeux au choix (Options, page 2 avec L/R) : personnage (Brendan, Flora, Red, Leaf), boîte de
dialogue, boîtes de combat, menus, sac, Pokédex, sprites des Pokémon, écran titre, intro, cadre des fenêtres.

### Confort
- Courir partout, vitesse du texte, CHERCH'OBJET et K.O. de Rouge Feu partout (perte d'argent, retour devant
  l'infirmière).
- Fenêtre redimensionnable, plein écran, écran tactile (téléphone : boutons à l'écran ; RESET à maintenir 1 s).
- Avance rapide (touche dédiée).

### Technique
- 60 images par seconde régulières (écrans 60 et 120 Hz), peu de processeur, sauvegarde écrite immédiatement.
- Sauvegarde : `%APPDATA%\pokeemerald\pokeemerald.sav` (Windows), dossier de l'appli (Android),
  `~/.local/share/pokeemerald/` (Linux).

### Contenu du dossier
- `Windows/` : `PokemonNative3G.exe` + `SDL2.dll` (à garder ensemble).
- `Linux/` : `PokemonNative3G` (x86_64 ; il faut SDL2 : `sudo apt install libsdl2-2.0-0`).
- `Android/` : `PokemonNative3G.apk` (Android 7+, 64 bits ; autoriser l'installation d'applis inconnues).

### Prochaines versions
Corrections de bugs et contenu en plus. Le multijoueur viendra en dernier.
