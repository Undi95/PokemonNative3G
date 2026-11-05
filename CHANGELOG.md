# PokemonNative3G — Changelog

## Version 1.2.1 (5 novembre 2026)

Petite mise à jour de la base, pour la version navigateur.

### Nouveauté
- Version navigateur : les touches se changent dans la page (bouton « Touches » de la barre du bas, une fois le jeu
  lancé). Elles sont gardées dans le navigateur du joueur, avec sa partie.

### Corrections
- Version navigateur : le clavier se lit comme sur PC, par la lettre écrite sur la touche, AZERTY comme QWERTY
  (A = Z, L = A). Avant, c'étaient les positions d'un clavier QWERTY (sur AZERTY, A = W et L = Q).

## Version 1.2 (5 novembre 2026) — la base

Cette version est la **base** de PokemonNative3G : le jeu complet, à reprendre pour construire son propre jeu
par-dessus. Le dépôt est public : https://github.com/Undi95/PokemonNative3G

Contenu du zip : `Windows/` (`PokemonNative3G.exe` + `SDL2.dll`), `Linux/` (`PokemonNative3G`), `Android/`
(`PokemonNative3G.apk`), `Navigateur/` (`index.html` + `pokeemeraude.js`, nouveau), ce CHANGELOG et le guide
`Où trouver les Pokémon.md`.

### Nouveautés
- À Kanto, le joueur a son sprite de style Rouge Feu, quel que soit le personnage : Brice et Flora y gardent leur
  tenue d'Émeraude, dessinés en style Rouge Feu par Poffin_Case (marche, course, vélos, figures du Vélo Cross, surf,
  pêche, Cherche VS…). Ils peuvent aussi lever le Cherche VS à Kanto.
- À Hoenn, Red et Leaf (option PERSO) ont leur sprite de style Émeraude : tête et tenue de leur marche d'Émeraude,
  dessinées à la main sur toutes les poses du joueur (course, vélos et figures du Vélo Cross, surf, Capacité, pêche,
  plongée, arrosoir, décoration). La monture du SURF et l'oiseau du VOL gardent les couleurs d'Émeraude ; pas de
  pose du Cherche VS à Hoenn, comme Brice et Flora.
- À Hoenn, l'image d'aperçu de Rouge Feu s'affiche aussi à l'entrée de 13 lieux, avec leur nom : Bois Clémenti, Parc
  Safari, Tunnel Mérazon, Grotte Granite, Site Météore, Chemin Ardent, Grotte Tréfonds, Grotte Origine, Route
  Victoire, Grotte Zénith, Grotte Métamo, Grotte Atelier et Grotte Terra. Ce sont des images de Rouge Feu qui ne
  montrent qu'une forêt, une savane ou une entrée de grotte. Comme à Kanto, l'aperçu dure plus longtemps à la
  première visite, et B l'abrège dans une grotte.
- Les 10 lieux uniques de Hoenn ont leur propre image d'aperçu, dessinée dans le style de Rouge Feu : Mont Mémoria,
  Pilier Céleste, Planque Aqua, Planque Magma, Épave, New Lavandia, Tour Mirage, Ruines Désert, Grotte Island et
  Tombeau Antique. Le Pilier Céleste et les entrées des trois ruines des Regi sont dessinés d'après Rubis Oméga et
  Saphir Alpha.
- Version navigateur : le jeu se joue dans un navigateur, sans rien installer. Le dossier Navigateur contient deux
  fichiers à ouvrir tels quels ou à déposer sur un site. La partie est gardée dans le navigateur, avec des boutons
  pour exporter et importer la sauvegarde : c'est le même fichier que sur PC et Android. Le son, la manette et
  l'écran tactile fonctionnent.
- Sac sans limite : les poches Objets, Objets rares et Balls ne sont plus jamais pleines (au-delà de 99, un objet
  continue sur une nouvelle ligne). Les CT et les baies gardent une seule ligne chacune (99 CT, 999 baies), pour la
  boîte à CT et le sac à baies de Rouge Feu. Les sauvegardes existantes sont reprises telles quelles.
- Kanto sans le POKéDEX NATIONAL : comme dans Rouge Feu, un Pokémon n'évolue pas en un Pokémon de Johto absent des
  Pokédex de Kanto et de Hoenn (Leuphorie, Mentali, Noctali, Steelix, Cizayox, Roigada, Tarpaud, Porygon2) ; la pierre,
  le Câble Link et l'objet tenu sont gardés.

### Corrections
- Kanto, sous la météo « ombre » (Forêt de Jade, Bois Baies, Manoir, chambres de Tanoby encore fermées) : le panneau
  du nom de lieu restait gris et l'image d'aperçu du lieu était ternie. Comme dans Rouge Feu, ni l'un ni l'autre ne
  sont plus touchés par la météo. Vérifié sur une carte par lieu des deux régions : à Kanto, le panneau de Rouge Feu ;
  à Hoenn, celui d'Émeraude, au cadre du lieu.
- Red et Leaf sur le Vélo Cross (figures), avec l'arrosoir et sous l'eau : de vrais sprites de style Rouge Feu
  (Poffin_Case) ; ce n'était qu'une tête de Rouge Feu posée sur le corps de Brice/Flora, le sac à dos coupé en deux.
- PC et Android : chaque fois que le jeu attendait la fin d'une copie d'écran, il rejouait toute une interruption
  d'image de plus. Les chronomètres du MONT DRESSEURS, de la TOUR DRESSEURS et de la Piste Cyclable (Route 110)
  prenaient de l'avance pendant les chargements, et les tirages au hasard ne suivaient plus ceux de la cartouche.
- Pêcheur de la Route 12 et maison de l'Île 6 (records de MAGICARPE et de SCARHINO) : « même taille que la dernière
  fois » est de nouveau dit, l'ancien record s'affiche, et le record de départ n'est plus de 90 cm.
- Tutoriel de capture de Timmy : son sac ne montre plus les objets du joueur, qui ne gagne plus une POTION au passage.
- Pokédex de Rouge Feu (option POKéDEX = KANTO) : après une capture, le Pokémon s'affiche de nouveau sous la question
  du surnom (l'écran restait vide).
- Parc Safari : avec le personnage Red / Leaf (option PERSO), c'est bien lui qu'on voit de dos, et plus Brice / Flora.
- Nouvelle partie : les curseurs du sac, de la boîte à CT et du sac à baies de Rouge Feu repartent du haut.
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
- Sauvegardes : celles de Windows se lisent enfin sur Android et sous Linux (et inversement). L'exe Windows rangeait
  une partie des données autrement que les autres versions (et que la cartouche) : un téléphone voyait une sauvegarde
  vide. Les sauvegardes Windows des versions 1.0 et 1.1 sont converties au chargement, rien à faire.
- Sauvegardes : sur Android et Linux, une sauvegarde faite une seule fois (l'autre emplacement encore vide) pouvait
  faire planter le jeu au démarrage, selon la place que le système lui donnait en mémoire.
- Plus de lecture ou d'écriture hors limites (vues par AddressSanitizer) : fiche d'une capacité à apprendre (Maître
  des capacités, MENUS = KANTO), portes et fenêtre d'étage des ascenseurs de Céladopole, Sylphe SARL, Repaire Rocket
  et Tour des Dresseurs, sortie d'une grotte sombre éclairée par FLASH.
- Clavier (PC) : les touches de pokeemerald.ini sont celles dont le nom est écrit sur le clavier, quelle que soit sa
  disposition. Sur un clavier AZERTY, A = la touche Z (et non plus W), L = la touche A (et non plus Q) ; on peut aussi
  choisir une touche propre à son clavier (« key_a = ù »). La rangée des chiffres reste 1 à 0 sur tous les claviers.
- POKéFLUTE en combat : le combat se bloquait après « La FLUTE réveille le POKéMON! ».
- Résumé du Pokémon de Rouge Feu (MENUS = KANTO) et Panthéon de Kanto : le numéro de Pokédex des Pokémon de Kanto
  s'affiche (« N° 150 » pour MEWTWO, au lieu de « ??? »), comme dans Rouge Feu.
- Plus de lecture hors limites (vues par AddressSanitizer) : icône de DEOXYS forme Vitesse (Émeraude la prenait juste
  après l'icône normale dans la cartouche), palettes des aperçus de donjon de la carte de Kanto (RF en lisait une de
  trop).
- Carte de Kanto (objet CARTE) : refermer l'aperçu d'un donjon (A sur une grotte déjà visitée, comme le Mont
  Sélénite) faisait planter le jeu.
- Carte de dresseur de Kanto : les badges sont dans leurs cases (ils étaient une rangée trop haut et cachaient le mot
  « BADGES »).
- Kanto prend les données de la version Rouge Feu là où Rouge Feu et Vert Feuille diffèrent : l'échange du NIDORAN
  (souterrain, entrée nord) était vide, l'EXCELANGUE de la Route 18 demandait un POKéMON vide, et la salle des lots
  du Casino de Céladopole ne proposait aucun POKéMON (« ??????????? »).
- Échanges avec les PNJ (Hoenn et Kanto) : le jeu plantait à la fin de l'animation, au retour sur la carte.
- Plus de lectures hors limites (vues par AddressSanitizer) : écran titre de Kanto qui repart sur l'intro (deux
  endroits), choix d'un fond de boîte au PC, panneau du nom de la carte à Hoenn, ombre des POKéMON et image de la GBA
  pendant un échange.
- PC de Kanto > PANTHEON sans équipe enregistrée : message d'erreur comme dans Rouge Feu (au lieu d'une équipe vide
  lue hors limites).
- Panthéon de Kanto : l'entrée est comptée comme dans Rouge Feu, dans un compteur à part (celui de Hoenn ne bouge
  plus). Le PC affichait « PANTHEON Nº 0 », la carte de dresseur de Kanto prenait l'étoile et la date du Panthéon de
  Hoenn, et les poupées de la maison d'OLGA (Île 4) ne pouvaient pas apparaître.
- Résumé du Pokémon de Rouge Feu (MENUS = KANTO) sans Pokédex national : les Pokémon du Pokédex de Hoenn ont leur
  numéro (« N° 255 » pour POUSSIFEU) ; seuls les autres (Johto) restent « ??? ».
- Grotte Métamo (Île 6) : ses rencontres et la page ZONE du Pokédex de Rouge Feu suivent de nouveau sa propre table
  (elles lisaient la Caverne Altérée de Hoenn).
- Avec Options > PERSO = Red/Leaf, le reflet du joueur dans l'eau est pâle comme dans Rouge Feu (il gardait les
  couleurs normales).
- Options > INTRO = HOENN : le jeu démarre de nouveau sur l'intro d'Émeraude (au lancement, c'était toujours celle de
  Rouge Feu ; l'option ne comptait qu'après un passage par l'écran titre).
- Évolution : comme sur la cartouche, l'écran attend la fin du son puis du cri avant « Félicitations! » (le portage PC
  sautait ces deux attentes).
- 2ᵉ étage des Centres POKéMON de Kanto : le moniteur sans fil et l'écran des records répondent de nouveau, comme dans
  Rouge Feu (les deux cases étaient muettes).

### Nouveautés
- Link (échanges, combats, Union Room, mini-jeux, concours et combats multi en link) : il reste dans le jeu mais
  fermé jusqu'à l'arrivée du multijoueur ; dans les deux régions, les hôtesses et guichets répondent que le club est
  en préparation ou en réglage (avant, on pouvait lancer une connexion qui échouait).
- Île 7 : la maison du dresseur e-Reader fonctionne (combat contre un dresseur e-Reader enregistré, comme dans Rouge
  Feu). Sans e-Reader, on ne peut pas encore y enregistrer de dresseur.
- POKéDEX NATIONAL donné une seule fois : si le PROF. SEKO l'a déjà donné, le PROF. CHEN se contente de noter le
  POKéDEX (sa scène est considérée comme faite) ; si c'est le PROF. CHEN, le PROF. SEKO le dit, et la suite (starters
  de Johto, appel de SCOTT pour la Zone de Combat) reste la même.
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
  de la table des sinus ; en combat double, « Ce n'est pas très efficace » ne fait plus lire la télé de combat hors
  de la table des combattants.

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
- Fenêtre redimensionnable, plein écran, écran tactile (téléphone : boutons à l'écran ; RESET à maintenir un court
  instant).
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
