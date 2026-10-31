# PokemonNative3G — Changelog

## Prochaine version

### Ajouts
- **Cycle jour/nuit** (Options, page 1, JOUR/NUIT ; désactivé par défaut) : dehors, la lumière suit l'heure de
  l'appareil (matin doré, coucher de soleil orangé, nuit bleutée), les fenêtres s'allument le soir. Purement
  visuel : mêmes Pokémon à toute heure.
- **Mentali / Noctali** : la nuit d'évolution suit le cycle, de 20 h à 6 h (avant : minuit à midi).

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
