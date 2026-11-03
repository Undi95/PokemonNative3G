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
- Ligue de Kanto : les combats contre OLGA, ALDO, AGATHA, PETER et le maître commencent de nouveau par leur
  transition à portrait de Rouge Feu (bandeau à leurs couleurs, portraits qui glissent) au lieu d'une transition
  ordinaire ; avec PERSO = Red/Leaf, la moitié du joueur prend les couleurs de RF.
- Ligue et arènes de Kanto : un combat contre un champion d'arène, le Conseil 4 ou le maître augmente de nouveau
  l'amitié des Pokémon, comme à Hoenn.
- Parc Safari de Kanto : c'est celui de Rouge Feu. 600 pas au lieu de 500 (la maison de la CS Surf et la Dent d'Or
  redeviennent atteignables), les pas restants et les SAFARI BALLS dans le menu START, et en combat BALL, APPAT,
  PIERRE, FUITE au lieu de POKéBLOC et SE RAPPROCHER : l'APPAT fait manger le Pokémon (il fuit moins, se capture
  moins bien), la PIERRE le fâche (il se capture mieux, fuit plus), avec les animations et les règles de RF ; la
  fuite dépend de l'espèce. Le Safari de Hoenn ne change pas.
- Combats (partout) : deux touches de Rouge Feu ajoutées. En combat double, la capacité sous le curseur fait
  blanchir les Pokémon qu'elle touchera ; un Pokémon qui monte de niveau est traversé de bandes lumineuses, avec
  leur son.
- Easy Chat (profil, phrases de combat, LETTRE, questionnaire) : avec MENUS = KANTO, c'est l'écran de Rouge Feu. Les
  deux écrans ont tous les mots des deux jeux : ROUGE, VERT, OR, ARGENT, FEUILLE et FLAMME (groupe DRESSEUR) sont
  maintenant disponibles.
- Club Événement Mystère de Kanto : un profil écrit à Kanto ne compte plus toujours comme la phrase secrète.
- Parc Safari de Kanto : à la fin du temps, des SAFARI BALLS ou avec PARTIR, on revient à l'entrée de Parmanie (le jeu
  envoyait à l'entrée du Parc Safari de la Route 121, à Hoenn).
- Vieil homme de Jadielle : avec SAC = KANTO, sa démonstration de capture ouvre le sac de Rouge Feu (il passe à la
  poche des POKé BALLS et choisit la sienne), au lieu de celui d'Émeraude.
- Musiques de Kanto : le Surf, le vélo, la Piste Cyclable et le Panthéon ont leurs musiques de Rouge Feu (ils jouaient
  celles de Hoenn) ; comme dans Rouge Feu, la Route Victoire, la Route 23 et le Plateau Indigo gardent leur musique à
  vélo ou en surfant.
- Parmanie : le RAMOLOSS près de la Zone Safari erre lentement, comme dans Rouge Feu.
- Kanto : RAIKOU, ENTEI et SUICUNE errants ont la musique des légendaires de Rouge Feu (pas celle des Pokémon
  sauvages).
- K.O. : le joueur reparaît tourné vers l'infirmière qui le soigne, comme dans Rouge Feu.
- Carmin-sur-Mer : l'OCEANE qui part ne disparaît plus trop tôt sur la gauche de l'écran.
- Sons de Kanto : les portes, la caisse (boutique, vente, Casino, Musée, photo) et la fanfare des soins hors Centre
  sont ceux de Rouge Feu (c'étaient des sons d'Émeraude de même nom, et pour les soins un morceau que Rouge Feu ne
  joue jamais).
- Îles Écume : en tombant par un trou dans l'eau quand les rochers n'arrêtent pas encore le courant, le joueur est de
  nouveau emporté par le courant jusqu'à l'étage du dessous, comme dans Rouge Feu (il surfait librement et l'énigme
  des rochers était sautée).
- Éclosion d'un œuf, lecture d'une lettre : plus de lecture hors limites (palettes et tiles de la plateforme, fenêtre
  inexistante de la lettre d'Émeraude) ; un OUI / NON n'est plus effacé deux fois. De même pour COUPE ou ÉCLATE-ROC
  depuis l'équipe sans rien en face du joueur.
- Carte Dresseur de Kanto : la photo de l'imprimante du Casino de Céladopole (les Pokémon de l'équipe, au dos) et
  les STICKERS de l'homme de l'Île 4 apparaissent enfin sur la carte. Les étoiles et la couleur suivent les règles de
  Rouge Feu (Panthéon, Pokédex de Kanto, Pokédex national, 200 baies et 200 sauts), et le Pokédex compte ceux de Kanto.
- COUPE à Kanto : elle tond l'herbe comme dans Rouge Feu, avec les cimes d'arbre sur l'herbe, l'herbe de la Piste
  Cyclable, du Parc Safari et de la Forêt de Jade (seule l'herbe haute était tondue).
- SURF et cannes à Kanto : l'eau en face du joueur se reconnaît comme dans Rouge Feu. Sur la plage de la Route 18,
  l'étang n'est plus accessible en Surf ni pêchable depuis le rivage.
- Combats contre la TEAM ROCKET : « SBIRE TEAM ROCKET » (et non plus « TEAM ROCKET SBIRE »), comme dans Rouge Feu.
- Boîte aux lettres du PC avec MENUS = KANTO : les flèches de défilement sont au milieu de la liste.
- Avec MENUS = KANTO, les boîtes d'argent et de jetons des PNJ (Casino, distributeurs, Musée, Parc Safari, pension…)
  sont celles de Rouge Feu (« ARGENT » / « JETONS » écrits au-dessus du montant), comme les choix et le OUI/NON.
  Avec MENUS = HOENN, la boîte des jetons du Casino de Céladopole n'est plus à moitié hors de l'écran.
- Télé Pokémon avec SAC = KANTO : allumée depuis le sac, après l'émission « Enregistrer un objet », on ne pouvait
  plus revenir sur la carte (fermer le sac ramenait à la télé, et fermer la télé au sac).
- Jirachi (Chutes Météore) : après la POKé FLÛTE, JIRACHI apparaît tout de suite ; le joueur restait bloqué
  43 secondes.
- Cap Falaise (Île 2) : le tuteur enseigne de nouveau VEGE-ATTAK, RAFALE FEU et HYDROBLAST à FLORIZARRE, DRACAUFEU
  et TORTANK (il proposait DYNAMOPOING, ROULADE ou BOOST, qu'ils ne peuvent pas apprendre).

### Nouveautés
- Kanto : en entrant dans un lieu, le panneau du nom est celui de Rouge Feu (boîte blanche en haut à gauche), avec
  l'étage comme dans Rouge Feu (« SYLPHE SARL 4ᵉ », « REPAIRE ROCKET 2 SS », « CELADOPOLE TOIT »). Hoenn garde
  le panneau d'Émeraude.
- Options > TITRE = R.FEU : l'écran titre de Rouge Feu mène maintenant au menu principal de Rouge Feu (CONTINUER avec
  le joueur, la durée de jeu, le Pokédex et les badges de la région où reprend la partie, NOUVELLE PARTIE, CADEAU
  MYST.). Comme dans Rouge Feu, il n'a pas d'entrée OPTIONS (elles restent dans le menu Start). Haut + SELECT + B
  sur cet écran titre ouvre aussi l'écran d'effacement de la sauvegarde de Rouge Feu.
- Options > MENUS = KANTO : les choix proposés par les personnages (et leur grille), le choix du PC et les OUI / NON
  sont aussi ceux de Rouge Feu (police de RF, lignes plus serrées, OUI / NON plus large), ainsi que la lecture d'une
  lettre (message et signature placés comme dans Rouge Feu) et l'écran Options (celui de Rouge Feu, avec les deux
  pages de la fusion : L/R). En sauvegardant, la fenêtre d'infos est celle de Rouge Feu (lieu en bleu, JOUEUR,
  BADGES, POKéDEX, DUREE JEU en petite police), avec les badges et le Pokédex de la région où l'on sauvegarde.
- Options > POKéMON = KANTO : à l'éclosion d'un œuf, le Pokémon pousse son cri et se place comme dans Rouge Feu.
- Combats : l'IA des dresseurs teste de nouveau les capacités connues exactement comme la cartouche (une lecture
  mal alignée la faisait « mieux » jouer sur PC et Android) ; plus de lecture hors limites à la fin d'un tour de
  combat double, ni dans l'animation de Métronome ; les confettis des résultats de concours ne lisent plus en dehors
  de la table des sinus.

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
