# PokemonNative3G

Pokémon Émeraude et Pokémon Rouge Feu (versions françaises) réunis en un seul jeu, compilé **nativement** pour
Windows, Linux, Android et le navigateur, sans émulateur : l'aventure d'Émeraude à Hoenn, puis celle de Rouge Feu à
Kanto et aux îles Sevii, dans le moteur d'Émeraude.

PokemonNative3G est une **base** : le jeu complet et testé, que chacun peut reprendre (fork) pour construire son
propre jeu par-dessus.

> Projet de fans non officiel, sans lien avec Nintendo, Creatures, Game Freak ou The Pokémon Company. Pokémon et
> les noms associés sont des marques de leurs propriétaires.

## Jouer

Télécharger le zip de la dernière version sur la page [Releases](https://github.com/Undi95/PokemonNative3G/releases) :

| Dossier | Contenu |
|---|---|
| `Windows/` | `PokemonNative3G.exe` + `SDL2.dll`, à garder ensemble |
| `Linux/` | `PokemonNative3G` (x86_64 ; il faut SDL2 : `sudo apt install libsdl2-2.0-0`) |
| `Android/` | `PokemonNative3G.apk` (Android 7+, 64 bits ; autoriser l'installation d'applis inconnues) |
| `Navigateur/` | `index.html` + `pokeemeraude.js` : ouvrir `index.html`, ou déposer les deux fichiers sur un site ([docs/NAVIGATEUR.md](docs/NAVIGATEUR.md)) |

Le zip contient aussi le [CHANGELOG](CHANGELOG.md) et le guide
[Où trouver les Pokémon](docs/OU-TROUVER-LES-POKEMON.md).

**Touches par défaut** (modifiables dans `pokeemerald.ini`, à côté de la sauvegarde ; dans le navigateur, par le
bouton « Touches ») : A = **Z**, B = **X**,
L = **Q**, R = **S**, START = **Entrée**, SELECT = **Retour arrière**, croix = **flèches**, avance rapide =
**Espace**, reset = **F5**, plein écran = **F11** ou **Alt+Entrée**. Une touche est celle où la lettre est écrite,
quelle que soit la disposition du clavier (AZERTY comme QWERTY), dans le navigateur comme sur PC. Manette et écran
tactile marchent aussi.

**Sauvegarde** : `%APPDATA%\pokeemerald` (Windows), `~/.local/share/pokeemerald` (Linux), dossier de l'appli
(Android), le navigateur (avec export et import du `.sav`). C'est le même fichier partout : une partie passe d'une
plateforme à l'autre telle quelle.

## Ce qu'il y a dans le jeu

- **Les deux aventures complètes** : scénarios, dresseurs, arènes, Ligues, crédits et Panthéons des deux régions,
  post-game compris (Zone de Combat, Tour des Dresseurs de l'Île 7, Cherche VS dans les deux régions).
- **Le passage vers Kanto** après la Ligue de Hoenn : un premier voyage en aller simple, on repart de zéro jusqu'à
  devenir Maître de Kanto, puis ferry et vol entre les régions.
- **Les 386 Pokémon obtenables en solo** : exclusivités de Rubis, Saphir et Vert Feuille dans la nature, starters
  manquants en œufs, Celebi et Jirachi, cadeaux mystère sans connexion, CÂBLE LINK pour les évolutions par échange.
- **Le style des deux jeux au choix** (Options, page 2) : personnage (Brice, Flora, Red, Leaf), boîte de dialogue,
  police, boîtes de combat, menus, sac, Pokédex, sprites des Pokémon, écran titre, intro, cadre des fenêtres.
- **Confort** : courir partout, POKé MONTURE à Kanto à la place des CS, sac sans limite, cycle jour/nuit (option),
  avance rapide.
- Pas encore de multijoueur (échanges, combats en link, Salle Union) : les accès au link sont fermés en jeu
  (`LINK_ENABLED`, `include/config.h`).

Le détail, version par version : [CHANGELOG.md](CHANGELOG.md).

## Construire son jeu à partir de la base

1. **Forker** le dépôt (ou le copier dans un nouveau dépôt), puis compiler avec Docker (ci-dessous).
2. **Build de test** avec le menu DEBUG (téléportation, objets, Pokémon, drapeaux, outils d'inspection) : ajouter
   `-e MAKEFLAGS_EXTRA=KANTO_DEBUG=1` à la commande de build. Les outils sont décrits dans
   [docs/DEVTOOLS.md](docs/DEVTOOLS.md).
3. **Tests automatiques** : le jeu se joue sans fenêtre, à partir de scénarios en Python, et compare ses écrans à des
   images de référence ([test/headless/README.md](test/headless/README.md)).
   `python test/headless/suite.py out/winwsl/pokeemeraude64.exe` joue toute la suite (245 scénarios) ;
   `bash test-release.sh` y ajoute une passe AddressSanitizer + UBSan.
4. **Release** : `bash build-all.sh VERSION` construit Windows, Linux, Android et la version navigateur sans le menu
   DEBUG, dans `out/PokemonNative3G-VERSION.zip`.

Pour s'y retrouver dans le code : [docs/CARTOGRAPHIE.md](docs/CARTOGRAPHIE.md) dit ce qui vient d'Émeraude, ce qui
vient de Rouge Feu et où c'est dans la fusion.

## Compiler (Docker, rien d'autre à installer)

Sous Git Bash (Windows) ou un terminal Linux, à la racine du dépôt :

```bash
docker build -t pn3g-build docker
P="$(pwd -W 2>/dev/null || pwd)"
MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work:/work -v "$P/out:/out" pn3g-build bash /repo/docker/build.sh winwsl
MSYS_NO_PATHCONV=1 docker run --rm -v "$P:/repo:ro" -v pn3g-work:/work -v "$P/out:/out" pn3g-build bash /repo/docker/build.sh linux
```

Sorties : `out/winwsl/pokeemeraude64.exe` + `SDL2.dll`, et `out/linux/pokeemeraude64`. Le build compile le
**dernier commit** du dépôt, pas les modifications non commitées. Android : [docs/PLATEFORMES.md](docs/PLATEFORMES.md) ;
navigateur : [docs/NAVIGATEUR.md](docs/NAVIGATEUR.md) ; sans Docker : [INSTALL_PC.md](INSTALL_PC.md).

## Documentation

| Fichier | Contenu |
|---|---|
| [CHANGELOG.md](CHANGELOG.md) | Ce qui a changé à chaque version |
| [docs/OU-TROUVER-LES-POKEMON.md](docs/OU-TROUVER-LES-POKEMON.md) | Guide des joueurs : où trouver chacun des 386 Pokémon |
| [docs/PLATEFORMES.md](docs/PLATEFORMES.md) | Builds Windows, Linux, Android ; cadence, sauvegardes, clavier, tactile |
| [docs/NAVIGATEUR.md](docs/NAVIGATEUR.md) | Version navigateur : jouer, héberger, compiler, fonctionnement |
| [INSTALL_PC.md](INSTALL_PC.md) | Compiler sans Docker (Windows avec WSL, Linux, macOS) |
| [docs/CARTOGRAPHIE.md](docs/CARTOGRAPHIE.md) | Carte de la fusion : ce qui vient de chaque jeu et où c'est (listes détaillées dans `docs/carto/`) |
| [docs/KANTO-ETAT.md](docs/KANTO-ETAT.md) | Comment Kanto a été importé dans le moteur d'Émeraude (outils, sauvegarde, scripts, warps) |
| [docs/FUSION-OPTIONS.md](docs/FUSION-OPTIONS.md) | Tout ce qui existe dans les deux jeux et comment la fusion le réunit (options HOENN / KANTO) |
| [docs/VARIANTES-RF.md](docs/VARIANTES-RF.md) | Détails de Rouge Feu où la fusion garde la version d'Émeraude |
| [docs/OBJETS-EN-DOUBLE.md](docs/OBJETS-EN-DOUBLE.md) | Objets clés et CS que les deux régions donnent, et comment c'est réglé |
| [docs/CONNAISSANCE-JEU.md](docs/CONNAISSANCE-JEU.md) | Comportement attendu de chaque écran selon les options et la région |
| [docs/DEVTOOLS.md](docs/DEVTOOLS.md) | Menu DEBUG et outils d'inspection (en jeu, tests, console) |
| [docs/A-TESTER.md](docs/A-TESTER.md) | Points vérifiés en jeu, avec les scénarios qui les couvrent |
| [docs/AUDIT-OUBLIS.md](docs/AUDIT-OUBLIS.md) | Audit de ce qui aurait pu être oublié (Pokémon, objets, scripts, scénario) |
| [test/headless/README.md](test/headless/README.md) | Banc de test sans fenêtre (scénarios, journal, images de référence) |

## Origine du code

- Décomp française d'Émeraude : [qigast/pokeemeraude](https://github.com/qigast/pokeemeraude) (commit `2f0d29fcc`),
  fork de [pret/pokeemerald](https://github.com/pret/pokeemerald).
- Couche PC (SDL2) : [fuddlesworth/pokeemerald-native](https://github.com/fuddlesworth/pokeemerald-native)
  (branche `vanilla`), elle-même issue de [NTx86/pokeemerald-sdl2pc](https://github.com/NTx86/pokeemerald-sdl2pc).
  Les deux partent du même commit pret (`83df84e40`) : la fusion est un vrai merge git.
- Kanto : importé d'une décomp française de Rouge Feu (d'après [pret/pokefirered](https://github.com/pret/pokefirered))
  par les outils de `tools/kanto/`.

## Crédits graphiques

- **Poffin_Case** (PokéCommunity, pack « FRHoenn ») : Brice et Flora dans leur tenue d'Émeraude, dessinés en style
  Rouge Feu (toutes les poses), et les poses d'Émeraude de Red et Leaf en style Rouge Feu (Vélo Cross, arrosoir,
  plongée, décoration). C'est le joueur à Kanto. Importés par `tools/sprites_joueur_rf.py`.
- Icône du CÂBLE LINK : « linking_cord » de [rh-hideout/pokeemerald-expansion](https://github.com/rh-hideout/pokeemerald-expansion).
