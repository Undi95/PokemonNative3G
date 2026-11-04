# Variantes de Rouge Feu gardées d'Émeraude

Règle (décision de l'utilisateur, 2026-11-02) : quand une fonction du code **commun** aux deux jeux (effets de
terrain, menus, animations, sons) a dans Rouge Feu une variante de détail, la fusion garde la version d'Émeraude dans
les deux régions. Rouge Feu est porté pour ce qui est propre à Kanto (contenu, mécaniques, écrans de RF déjà au choix
dans les Options). Chaque variante **visible** est listée ici, pour pouvoir en choisir une plus tard.

Trouvées en lisant les fonctions « à vérifier » de l'inventaire (`tools/carto_diff.py`, classement dans
`tools/carto_classement.txt`, « écartée variante RF »).

| Où | Émeraude (gardé) | Rouge Feu | Fonction RF |
|---|---|---|---|
| Vol, l'oiseau qui emporte le joueur | arc de rayon 140, 4 par image ; le sprite du joueur est posé sur l'oiseau (va avec tous les personnages) | arc de rayon 180, 2 par image (plus large, 2× plus lent) ; RED ou LEAF sont dessinés dans l'image de l'oiseau, qui grossit et rapetisse | `SpriteCB_FlyBirdWithPlayer`, `FlyOutFieldEffect_FlyOffWithBird`, `TryChangeBirdSprite` (field_effect.c) |
| Dresseur qui repère le joueur | le joueur se tourne vers lui | le joueur ne bouge pas | `TrainerSeeFunc_PrepareToEngage` (trainer_see.c) |
| Reflets dans l'eau et la glace | cases regardées selon la taille du sprite ; cherchés au début d'un pas | toujours 1 × 2 cases (pareil pour le joueur et les PNJ ordinaires ; diffère pour les grands sprites) ; cherchés aussi à la fin d'un pas | `ObjectEventCheckForReflectiveSurface`, `GetAllGroundEffectFlags_OnFinishStep` (event_object_movement.c) |
| Marche lente des scripts (`walk_slow_*`, cinématiques) | 1 image sur 2 : une case en 32 images | 2 images sur 3 : une case en 24 images | `UpdateWalkSlowAnim` (event_object_movement.c) |
| PNJ qui court sur place (`MOVEMENT_TYPE_JOG_IN_PLACE_*`) | vitesse « rapide » | vitesse « plus rapide » | `MovementType_JogInPlace_Step0` (event_object_movement.c) |
| Marche affine vers le bas (`walk_down_affine`) | lente | plus lente | `MovementAction_WalkDownAffine_Step0` (event_object_movement.c) |
| **Sortie d'un bâtiment** | fondu d'Émeraude | l'écran s'ouvre depuis le milieu, en portes de grange | `DoOutwardBarnDoorWipe` (field_screen_effect.c), `Task_ExitDoor` |
| Corde Sortie | le joueur tourne de plus en plus vite, l'écran s'éteint ; à l'arrivée, il tourne en clignotant | il tourne, puis s'envole hors de l'écran ; à l'arrivée, il redescend du haut de l'écran en tournant | `SpinObjectEvent`, `WarpOutObjectEventUpwards`, `WarpInObjectEventDownwards` (field_effect.c) |
| Surf, le Pokémon qui porte le joueur | monte et descend toutes les 4 / 8 images | 2× plus lent | `CreateBobbingEffect` (field_effect_helpers.c) |
| Fin du Surf (le joueur saute à terre) | les PNJ continuent de marcher | les PNJ s'arrêtent pendant le saut | `CreateStopSurfingTask`, `Task_WaitStopSurfing` (field_player_avatar.c) |
| **Pêche, la touche** | « Oh! Ça mord! », puis A à temps (la SUPER CANNE peut demander plusieurs fois) | pas de réaction : le Pokémon est ferré directement (« Un POKéMON a mordu! ») | `Fishing7` (field_player_avatar.c) |
| Pêche, les points avant la touche | un point toutes les 8 images ; A arrête la pêche | un point toutes les 12 images, A sans effet | `Fishing5` (field_player_avatar.c) |
| Pêche, ferrer | VENTOUSE ou GLUE en tête : touche plus souvent | aucun talent ne compte | `Fishing6` (field_player_avatar.c) |
| Écran d'équipe | fenêtres, police et OUI / NON d'Émeraude ; fondu de sortie normal (MENUS = KANTO : palette de RF) | ses fenêtres et sa police ; fondu de sortie plus rapide | `ExitPartyMenu`, `Task_ClosePartyMenu`, `DisplaySelectionWindow`, `ShowMoveSelectWindow` (party_menu.c) |
| Pension : menu de retrait et message de l'éclosion | police d'Émeraude, niveau aligné à droite en 112 | une police espacée de 1, niveau aligné en 132 | `DaycareAddTextPrinter`, `DaycarePrintMonLvl`, `EggHatchPrintMessage` (daycare.c) |
| Écran des noms (MENUS = KANTO) | titre dans la fenêtre d'Émeraude (tuile 8, texte en 8) | titre 1 px plus à droite (fenêtre en tuile 9, texte en 1) | `DrawNormalTextEntryBox` (naming_screen.c) |
| FLASH dans une grotte sombre | un grand cercle de lumière autour du joueur | toute la grotte éclairée | `SetDefaultFlashLevel` (overworld.c) |
| Poison sur le terrain | tous les 4 pas ; mosaïque jusqu'à 10, +2 puis -2 (10 images) | tous les 5 pas ; jusqu'à 6, +2 puis -1 (9 images, REVISION ≥ 0xA) | `UpdatePoisonStepCounter` (field_control_avatar.c), `Task_FieldPoisonEffect` (fldeff_poison.c), `AdjustBgMosaic` |
| Sons (voir CONNAISSANCE-JEU.md, « Sons de Kanto ») | instruments HQ, batterie complète ; jingles d'Émeraude | samples à 13 kHz ; fanfares du Casino +10 %, évolution, carte retournée | banque de sons de RF |
