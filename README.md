# PokemonNative3G

Pokémon Émeraude et Pokémon Rouge Feu (versions françaises) réunis en un seul jeu, compilé **nativement** pour
Windows, Linux, Android et le navigateur, sans émulateur : Hoenn puis Kanto et les îles Sevii, dans le moteur
d'Émeraude. Le détail par version est dans [CHANGELOG.md](CHANGELOG.md).

PokemonNative3G est une **base** : le jeu complet, à reprendre (fork) pour construire son propre jeu par-dessus.

## Origine du code

- Décomp française : [qigast/pokeemeraude](https://github.com/qigast/pokeemeraude) (commit `2f0d29fcc`),
  fork de [pret/pokeemerald](https://github.com/pret/pokeemerald).
- Couche PC (SDL2) : [fuddlesworth/pokeemerald-native](https://github.com/fuddlesworth/pokeemerald-native)
  (branche `vanilla`), elle-même issue de [NTx86/pokeemerald-sdl2pc](https://github.com/NTx86/pokeemerald-sdl2pc).
- Les deux partent du même commit pret (`83df84e40`) : la fusion est un vrai merge git.

## Crédits graphiques

- **Poffin_Case** (PokéCommunity, pack « FRHoenn ») : Brice et Flora dans leur tenue d'Émeraude, dessinés en style
  Rouge Feu (toutes les poses), et les poses d'Émeraude de Red et Leaf en style Rouge Feu (Vélo Cross, arrosoir,
  plongée, décoration). C'est le joueur à Kanto. Importés par `tools/sprites_joueur_rf.py`.

## Compiler (Docker, rien à installer d'autre)

```
docker build -t pn3g-build docker
docker run --rm -v "<chemin du dépôt>:/repo:ro" -v pn3g-work:/work -v "<chemin du dépôt>/out:/out" pn3g-build bash /repo/docker/build.sh linux
docker run --rm -v "<chemin du dépôt>:/repo:ro" -v pn3g-work:/work -v "<chemin du dépôt>/out:/out" pn3g-build bash /repo/docker/build.sh winwsl
```

Sorties : `out/linux/pokeemeraude64` et `out/winwsl/pokeemeraude64.exe` + `SDL2.dll`.
Android : [docs/PLATEFORMES.md](docs/PLATEFORMES.md). Navigateur (deux fichiers à ouvrir ou à déposer sur un site) :
[docs/NAVIGATEUR.md](docs/NAVIGATEUR.md).
Le build compile le **dernier commit** du dépôt (pas les modifications non commitées).
Instructions sans Docker : voir [INSTALL_PC.md](INSTALL_PC.md).

## Jouer

Touches par défaut (positions d'un clavier QWERTY US — sur AZERTY : A = **W**, B = **X**,
L = **Q**, R = **S**) ; Entrée = Start, flèches = croix. Réglages et sauvegarde dans
`%APPDATA%\pokeemerald` (Windows) ou `~/.local/share/pokeemerald` (Linux).
