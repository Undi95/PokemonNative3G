# Variantes de Rouge Feu gardées d'Émeraude

Règle (décision de l'utilisateur, 2026-11-02) : quand une fonction du code **commun** aux deux jeux (effets de
terrain, menus, animations, sons) a dans Rouge Feu une variante de détail, la fusion garde la version d'Émeraude dans
les deux régions. Rouge Feu est porté pour ce qui est propre à Kanto (contenu, mécaniques, écrans de RF déjà au choix
dans les Options). Chaque variante **visible** est listée ici, pour pouvoir en choisir une plus tard.

Trouvées en lisant les fonctions « à vérifier » de l'inventaire (`tools/carto_diff.py`, classement dans
`tools/carto_classement.txt`, « écartée variante RF »).

| Où | Émeraude (gardé) | Rouge Feu | Fonction RF |
|---|---|---|---|
| Vol, l'oiseau qui emporte le joueur | arc de rayon 140, 4 par image | arc de rayon 180, 2 par image (plus large, 2× plus lent) | `SpriteCB_FlyBirdWithPlayer` (field_effect.c) |
| Reflets dans l'eau et la glace | cases regardées selon la taille du sprite | toujours 1 × 2 cases (pareil pour le joueur et les PNJ ordinaires ; diffère pour les grands sprites) | `ObjectEventCheckForReflectiveSurface` (event_object_movement.c) |
| **Pêche, la touche** | « Oh! Ça mord! », puis A à temps (la SUPER CANNE peut demander plusieurs fois) | pas de réaction : le Pokémon est ferré directement (« Un POKéMON a mordu! ») | `Fishing7` (field_player_avatar.c) |
| Pêche, les points avant la touche | un point toutes les 8 images ; A arrête la pêche | un point toutes les 12 images, A sans effet | `Fishing5` (field_player_avatar.c) |
| Pêche, ferrer | VENTOUSE ou GLUE en tête : touche plus souvent | aucun talent ne compte | `Fishing6` (field_player_avatar.c) |
| Sons (voir CONNAISSANCE-JEU.md, « Sons de Kanto ») | instruments HQ, batterie complète ; jingles d'Émeraude | samples à 13 kHz ; fanfares du Casino +10 %, évolution, carte retournée | banque de sons de RF |
