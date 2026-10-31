# Sources C : Émeraude / Rouge Feu / fusion

> Généré par `tools/cartographie.py` — ne pas éditer à la main.

Légende : « Propres à RF » = noms de fonctions absents de tout `src/` d'Émeraude ; « même code dans Ém. » = corps identique à une fonction d'Émeraude d'un autre nom (rien à porter) ; « portées » = définies dans ce dépôt sous le même nom ou une variante Kanto (stubs compris) ; « Différentes d'Ém. » = même nom, corps différent (comportement ou présentation propre à RF, ou simple écart de constantes).

## Fichiers présents seulement dans Rouge Feu (76)

| Fichier RF | Où | Fonctions | Propres à RF | dont même code dans Ém. | dont portées | % couvert | Identiques à Ém. | Différentes d'Ém. | Fichier(s) de la fusion |
|---|---|---|---|---|---|---|---|---|---|
| quest_log_events.c | RF seul | 118 | 118 | 0 | 1 | 0 | 0 | 0 | kanto_specials.c (1) |
| quest_log_player.c | RF seul | 15 | 15 | 0 | 0 | 0 | 0 | 0 |  |
| mailbox_pc.c | RF seul | 9 | 9 | 0 | 0 | 0 | 0 | 0 |  |
| pokemon_storage_system_graphics.c | RF seul | 65 | 9 | 0 | 0 | 0 | 5 | 51 |  |
| pokemon_storage_system_tasks.c | RF seul | 82 | 5 | 0 | 0 | 0 | 6 | 71 |  |
| quest_log_battle.c | RF seul | 3 | 3 | 0 | 0 | 0 | 0 | 0 |  |
| quest_log_objects.c | RF seul | 3 | 3 | 0 | 0 | 0 | 0 | 0 |  |
| trade_scene.c | RF seul | 53 | 3 | 0 | 0 | 0 | 18 | 32 |  |
| cable_car_util.c | RF seul | 2 | 2 | 0 | 0 | 0 | 0 | 0 |  |
| blend_palette.c | RF seul | 2 | 1 | 0 | 0 | 0 | 0 | 1 |  |
| field_weather_effects.c | RF seul | 93 | 1 | 0 | 0 | 0 | 54 | 38 |  |
| field_weather_util.c | RF seul | 10 | 1 | 0 | 0 | 0 | 3 | 6 |  |
| save_menu_util.c | RF seul | 1 | 1 | 0 | 0 | 0 | 0 | 0 |  |
| text_printer.c | RF seul | 15 | 1 | 0 | 0 | 0 | 6 | 8 |  |
| text_window_graphics.c | RF seul | 1 | 1 | 0 | 0 | 0 | 0 | 0 |  |
| tilemap_util.c | RF seul | 11 | 1 | 0 | 0 | 0 | 1 | 9 |  |
| window_8bpp.c | RF seul | 7 | 1 | 0 | 0 | 0 | 3 | 3 |  |
| easy_chat_3.c | RF seul | 92 | 92 | 1 | 0 | 1 | 0 | 0 |  |
| quest_log.c | RF seul | 88 | 88 | 0 | 2 | 2 | 0 | 0 | kanto_field_specials.c (2) |
| union_room_chat_display.c | RF seul | 58 | 50 | 1 | 0 | 2 | 0 | 8 |  |
| help_system_util.c | RF seul | 41 | 41 | 0 | 1 | 2 | 0 | 0 | kanto_fame_checker.c (1) |
| oak_speech.c | RF seul | 64 | 64 | 2 | 0 | 3 | 0 | 0 |  |
| easy_chat_2.c | RF seul | 73 | 57 | 2 | 0 | 3 | 9 | 7 |  |
| pokemon_storage_system_data.c | RF seul | 83 | 17 | 1 | 0 | 5 | 17 | 49 |  |
| battle_controller_oak_old_man.c | RF seul | 107 | 81 | 4 | 3 | 8 | 0 | 26 | kanto_battle_controller_pokedude.c (3) |
| union_room_chat_objects.c | RF seul | 13 | 12 | 1 | 0 | 8 | 0 | 1 |  |
| help_system.c | RF seul | 41 | 41 | 0 | 6 | 14 | 0 | 0 | kanto_specials.c (6) |
| cereader_tool.c | RF seul | 8 | 7 | 0 | 1 | 14 | 0 | 1 | kanto_trainer_tower.c (1) |
| pokemon_storage_system_misc.c | RF seul | 70 | 15 | 3 | 0 | 20 | 16 | 39 |  |
| battle_anim_special.c | RF seul | 81 | 42 | 4 | 5 | 21 | 15 | 24 | battle_anim_throw.c (3), kanto_battle_controller_pokedude.c (2) |
| new_menu_helpers.c | RF seul | 54 | 19 | 3 | 1 | 21 | 11 | 24 | menu.c (1) |
| pokemon_storage_system_menu.c | RF seul | 29 | 6 | 2 | 0 | 33 | 10 | 13 |  |
| field_fadetransition.c | RF seul | 59 | 30 | 2 | 12 | 46 | 5 | 24 | field_screen_effect.c (12) |
| help_message.c | RF seul | 7 | 7 | 0 | 6 | 85 | 0 | 0 | copie kanto_help_message.c : 6/7 fonctions |
| battle_controller_pokedude.c | RF seul | 108 | 78 | 0 | 78 | 100 | 0 | 30 | copie kanto_battle_controller_pokedude.c : 108/108 fonctions |
| berry_pouch.c | RF seul | 77 | 77 | 0 | 77 | 100 | 0 | 0 | copie kanto_berry_pouch.c : 77/77 fonctions |
| tm_case.c | RF seul | 73 | 71 | 0 | 71 | 100 | 0 | 2 | copie kanto_tm_case.c : 73/73 fonctions |
| pokedex_screen.c | RF seul | 68 | 67 | 0 | 67 | 100 | 1 | 0 | copie kanto_pokedex_screen.c : 68/68 fonctions |
| fame_checker.c | RF seul | 64 | 64 | 0 | 64 | 100 | 0 | 0 | copie kanto_fame_checker.c : 64/64 fonctions |
| pokemon_special_anim_scene.c | RF seul | 67 | 64 | 0 | 64 | 100 | 0 | 3 | copie kanto_pokemon_special_anim_scene.c : 65/67 fonctions |
| item_pc.c | RF seul | 59 | 59 | 0 | 59 | 100 | 0 | 0 | copie kanto_item_pc.c : 59/59 fonctions |
| teachy_tv.c | RF seul | 58 | 58 | 0 | 58 | 100 | 0 | 0 | copie kanto_teachy_tv.c : 58/58 fonctions |
| trainer_tower.c | RF seul | 43 | 40 | 0 | 40 | 100 | 0 | 3 | copie kanto_trainer_tower.c : 43/43 fonctions |
| vs_seeker.c | RF seul | 41 | 38 | 0 | 38 | 100 | 0 | 3 | copie kanto_vs_seeker.c : 41/41 fonctions |
| pokemon_special_anim.c | RF seul | 31 | 30 | 0 | 30 | 100 | 0 | 1 | copie kanto_pokemon_special_anim.c : 30/31 fonctions |
| itemfinder.c | RF seul | 24 | 22 | 0 | 22 | 100 | 0 | 2 | copie kanto_itemfinder.c : 24/24 fonctions |
| seagallop.c | RF seul | 22 | 22 | 0 | 22 | 100 | 0 | 0 | copie kanto_seagallop.c : 20/22 fonctions; kanto_specials.c (2) |
| learn_move.c | RF seul | 23 | 20 | 0 | 20 | 100 | 1 | 2 | copie kanto_learn_move.c : 23/23 fonctions |
| map_preview_screen.c | RF seul | 14 | 14 | 0 | 14 | 100 | 0 | 0 | copie kanto_map_preview_screen.c : 14/14 fonctions |
| bag.c | RF seul | 13 | 13 | 0 | 13 | 100 | 0 | 0 | copie kanto_bag.c : 13/13 fonctions |
| trainer_fan_club.c | RF seul | 23 | 9 | 0 | 9 | 100 | 1 | 13 | copie kanto_trainer_fan_club.c : 23/23 fonctions |
| ss_anne.c | RF seul | 8 | 8 | 0 | 8 | 100 | 0 | 0 | copie kanto_ss_anne.c : 8/8 fonctions |
| pc_screen_effect.c | RF seul | 7 | 7 | 0 | 7 | 100 | 0 | 0 | kanto_hall_of_fame.c (7) |
| wild_pokemon_area.c | RF seul | 7 | 7 | 0 | 7 | 100 | 0 | 0 | kanto_pokedex_area.c (7) |
| menu2.c | RF seul | 10 | 6 | 0 | 6 | 100 | 0 | 4 | kanto_intro.c (3), kanto_pokemon_special_anim_scene.c (2), menu.c (1) |
| pokedex_area_markers.c | RF seul | 5 | 5 | 0 | 5 | 100 | 0 | 0 | kanto_pokedex_area.c (5) |
| renewable_hidden_items.c | RF seul | 4 | 4 | 0 | 4 | 100 | 0 | 0 | copie kanto_renewable_hidden_items.c : 4/4 fonctions |
| special_field_anim.c | RF seul | 10 | 4 | 0 | 4 | 100 | 0 | 6 | kanto_field_anims.c (4) |
| buy_menu_helpers.c | RF seul | 7 | 3 | 0 | 3 | 100 | 0 | 4 | kanto_shop.c (3) |
| prof_pc.c | RF seul | 3 | 3 | 0 | 3 | 100 | 0 | 0 | kanto_field_specials.c (3) |
| party_menu_specials.c | RF seul | 9 | 1 | 0 | 1 | 100 | 3 | 5 | kanto_specials.c (1) |
| bg_regs.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| braille_text.c | RF seul | 3 | 0 | 0 | 0 | 100 | 1 | 2 |  |
| dodrio_berry_picking_comm.c | RF seul | 8 | 0 | 0 | 0 | 100 | 8 | 0 |  |
| fldeff_berrytree.c | RF seul | 1 | 0 | 0 | 0 | 100 | 0 | 1 |  |
| fldeff_poison.c | RF seul | 3 | 0 | 0 | 0 | 100 | 2 | 1 |  |
| isagbprn.c | RF seul | 16 | 0 | 0 | 0 | 100 | 9 | 7 |  |
| keyboard_text.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| menu_indicators.c | RF seul | 20 | 0 | 0 | 0 | 100 | 5 | 15 |  |
| move_descriptions.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 | copie kanto_move_descriptions.c : 0/0 fonctions |
| mystery_gift_show_card.c | RF seul | 8 | 0 | 0 | 0 | 100 | 2 | 6 |  |
| mystery_gift_show_news.c | RF seul | 10 | 0 | 0 | 0 | 100 | 3 | 7 |  |
| reset_save_heap.c | RF seul | 1 | 0 | 0 | 0 | 100 | 0 | 1 |  |
| sloopsvc.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| trainer_tower_sets.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 | copie kanto_trainer_tower_sets.c : 0/0 fonctions |
| union_room_message.c | RF seul | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |

## Fichiers présents dans les deux jeux (207)

| Fichier RF | Où | Fonctions | Propres à RF | dont même code dans Ém. | dont portées | % couvert | Identiques à Ém. | Différentes d'Ém. | Fichier(s) de la fusion |
|---|---|---|---|---|---|---|---|---|---|
| event_object_movement.c | commun | 759 | 129 | 3 | 36 | 30 | 252 | 378 | event_object_movement.c (34), kanto_fame_checker.c (1), kanto_vs_seeker.c (1) |
| party_menu.c | commun | 357 | 70 | 10 | 19 | 41 | 142 | 145 | party_menu.c (19) |
| field_effect.c | commun | 239 | 109 | 13 | 8 | 19 | 36 | 94 | field_effect.c (8) |
| overworld.c | commun | 242 | 44 | 4 | 11 | 34 | 106 | 92 | overworld.c (8), kanto_specials.c (3) |
| battle_script_commands.c | commun | 284 | 3 | 0 | 0 | 0 | 165 | 116 |  |
| field_player_avatar.c | commun | 176 | 61 | 4 | 13 | 27 | 51 | 64 | field_player_avatar.c (13) |
| battle_ai_script_commands.c | commun | 105 | 14 | 0 | 0 | 0 | 3 | 88 |  |
| battle_transition.c | commun | 134 | 10 | 0 | 0 | 0 | 47 | 77 |  |
| battle_anim_effects_1.c | commun | 154 | 1 | 1 | 0 | 100 | 76 | 77 |  |
| battle_anim_mons.c | commun | 128 | 12 | 5 | 1 | 50 | 47 | 69 | battle_anim_mons.c (1) |
| battle_controller_player.c | commun | 123 | 15 | 7 | 2 | 60 | 39 | 69 | kanto_battle_controller_pokedude.c (2) |
| pokemon.c | commun | 143 | 13 | 1 | 4 | 38 | 68 | 62 | pokemon.c (3), kanto_specials.c (1) |
| scrcmd.c | commun | 224 | 12 | 2 | 8 | 83 | 144 | 68 | copie kanto_scrcmd.c : 8/224 fonctions |
| battle_main.c | commun | 106 | 18 | 4 | 1 | 27 | 32 | 56 | battle_main.c (1) |
| link_rfu_2.c | commun | 149 | 4 | 1 | 0 | 25 | 79 | 66 |  |
| union_room.c | commun | 110 | 2 | 0 | 0 | 0 | 43 | 65 |  |
| field_effect_helpers.c | commun | 76 | 7 | 1 | 0 | 14 | 9 | 60 |  |
| trainer_card.c | commun | 73 | 15 | 1 | 0 | 6 | 6 | 52 |  |
| start_menu.c | commun | 65 | 55 | 1 | 1 | 3 | 0 | 10 | kanto_specials.c (1) |
| berry_crush.c | commun | 73 | 4 | 0 | 0 | 0 | 11 | 58 |  |
| link.c | commun | 114 | 2 | 1 | 0 | 50 | 56 | 56 |  |
| item_use.c | commun | 73 | 58 | 2 | 14 | 27 | 1 | 14 | item_use.c (3), kanto_berry_pouch.c (3), kanto_tm_case.c (2) |
| trade.c | commun | 66 | 2 | 0 | 0 | 0 | 17 | 47 |  |
| union_room_chat.c | commun | 51 | 35 | 1 | 0 | 2 | 1 | 15 |  |
| battle_interface.c | commun | 52 | 11 | 0 | 0 | 0 | 6 | 35 |  |
| daycare.c | commun | 93 | 18 | 0 | 7 | 38 | 40 | 35 | daycare.c (7) |
| battle_tower.c | commun | 45 | 33 | 0 | 0 | 0 | 0 | 12 |  |
| dodrio_berry_picking.c | commun | 147 | 1 | 0 | 0 | 0 | 102 | 44 |  |
| bg.c | commun | 50 | 1 | 0 | 0 | 0 | 7 | 42 |  |
| player_pc.c | commun | 47 | 43 | 0 | 4 | 9 | 0 | 4 | player_pc.c (3), kanto_fame_checker.c (1) |
| shop.c | commun | 60 | 17 | 0 | 13 | 76 | 4 | 39 | copie kanto_shop.c : 53/60 fonctions |
| metatile_behavior.c | commun | 115 | 58 | 2 | 39 | 70 | 34 | 23 | metatile_behavior.c (39) |
| naming_screen.c | commun | 109 | 3 | 0 | 0 | 0 | 69 | 37 |  |
| battle_controller_opponent.c | commun | 87 | 10 | 4 | 1 | 50 | 43 | 34 | kanto_battle_controller_pokedude.c (1) |
| fieldmap.c | commun | 54 | 3 | 0 | 0 | 0 | 17 | 34 |  |
| battle_anim_effects_2.c | commun | 121 | 3 | 2 | 0 | 66 | 83 | 35 |  |
| battle_anim_effects_3.c | commun | 140 | 1 | 1 | 0 | 100 | 104 | 35 |  |
| easy_chat.c | commun | 40 | 27 | 0 | 2 | 7 | 3 | 10 | kanto_field_specials.c (2) |
| menu.c | commun | 50 | 25 | 0 | 7 | 28 | 8 | 17 | kanto_hall_of_fame.c (6), kanto_item_pc.c (1) |
| evolution_graphics.c | commun | 37 | 29 | 3 | 0 | 10 | 0 | 8 |  |
| battle_gfx_sfx_util.c | commun | 48 | 6 | 1 | 1 | 33 | 13 | 29 | battle_gfx_sfx_util.c (1) |
| cable_club.c | commun | 54 | 7 | 2 | 0 | 28 | 19 | 28 |  |
| battle_setup.c | commun | 66 | 20 | 0 | 13 | 65 | 21 | 25 | battle_setup.c (11), kanto_battle_bg.c (1), kanto_trainer_tower.c (1) |
| text.c | commun | 37 | 15 | 0 | 0 | 0 | 5 | 17 |  |
| item.c | commun | 49 | 29 | 15 | 3 | 62 | 0 | 20 | kanto_item_pc.c (1), kanto_specials.c (1), kanto_tm_case.c (1) |
| battle_anim_utility_funcs.c | commun | 42 | 1 | 0 | 0 | 0 | 12 | 29 |  |
| field_control_avatar.c | commun | 49 | 13 | 1 | 8 | 69 | 11 | 25 | field_control_avatar.c (8) |
| field_specials.c | commun | 118 | 89 | 0 | 81 | 91 | 9 | 20 | copie kanto_field_specials.c+kanto_list_menu.c+kanto_specials.c : 68/118 fonctions; kanto_field_anims.c (4), kanto_itemfinder.c (2), fldeff_cut.c (2) |
| field_weather.c | commun | 50 | 13 | 1 | 0 | 7 | 22 | 15 |  |
| main_menu.c | commun | 29 | 25 | 0 | 0 | 0 | 2 | 2 |  |
| wild_encounter.c | commun | 36 | 18 | 0 | 3 | 16 | 6 | 12 | wild_encounter.c (2), kanto_pokemon_special_anim_scene.c (1) |
| battle_anim.c | commun | 77 | 0 | 0 | 0 | 100 | 51 | 26 |  |
| battle_anim_normal.c | commun | 36 | 5 | 1 | 0 | 20 | 9 | 22 |  |
| pokemon_jump.c | commun | 186 | 0 | 0 | 0 | 100 | 160 | 26 |  |
| save.c | commun | 33 | 0 | 0 | 0 | 100 | 7 | 26 |  |
| list_menu.c | commun | 31 | 2 | 0 | 2 | 100 | 4 | 25 | kanto_pokedex_screen.c (2) |
| trainer_see.c | commun | 37 | 25 | 5 | 4 | 36 | 3 | 9 | trainer_see.c (4) |
| battle_anim_mon_movement.c | commun | 34 | 2 | 0 | 0 | 0 | 10 | 22 |  |
| palette.c | commun | 41 | 1 | 0 | 0 | 0 | 17 | 23 |  |
| battle_controller_link_partner.c | commun | 85 | 3 | 0 | 0 | 0 | 62 | 20 |  |
| bike.c | commun | 24 | 11 | 0 | 0 | 0 | 1 | 12 |  |
| hall_of_fame.c | commun | 42 | 16 | 0 | 16 | 100 | 3 | 23 | copie kanto_hall_of_fame.c : 42/42 fonctions |
| string_util.c | commun | 40 | 0 | 0 | 0 | 100 | 17 | 23 |  |
| battle_anim_ice.c | commun | 32 | 1 | 1 | 0 | 100 | 9 | 22 |  |
| battle_controller_link_opponent.c | commun | 86 | 2 | 0 | 0 | 0 | 64 | 20 |  |
| event_data.c | commun | 26 | 6 | 0 | 0 | 0 | 4 | 16 |  |
| link_rfu_3.c | commun | 30 | 3 | 1 | 0 | 33 | 7 | 20 |  |
| mystery_event_script.c | commun | 25 | 2 | 1 | 0 | 50 | 2 | 21 |  |
| script_menu.c | commun | 29 | 21 | 0 | 7 | 33 | 0 | 8 | script_menu.c (6), kanto_specials.c (1) |
| sprite.c | commun | 103 | 1 | 0 | 0 | 0 | 82 | 20 |  |
| battle_controller_safari.c | commun | 72 | 9 | 1 | 0 | 11 | 51 | 12 |  |
| script.c | commun | 55 | 17 | 0 | 10 | 58 | 25 | 13 | script.c (10) |
| tileset_anims.c | commun | 28 | 17 | 0 | 0 | 0 | 8 | 3 |  |
| battle_anim_electric.c | commun | 37 | 0 | 0 | 0 | 100 | 18 | 19 |  |
| battle_anim_ghost.c | commun | 41 | 5 | 1 | 4 | 100 | 17 | 19 | battle_anim_ghost.c (4) |
| battle_controllers.c | commun | 68 | 3 | 0 | 0 | 0 | 49 | 16 |  |
| mystery_gift_menu.c | commun | 34 | 4 | 0 | 0 | 0 | 15 | 15 |  |
| union_room_player_avatar.c | commun | 38 | 1 | 0 | 0 | 0 | 19 | 18 |  |
| battle_anim_dark.c | commun | 25 | 0 | 0 | 0 | 100 | 7 | 18 |  |
| battle_anim_flying.c | commun | 33 | 2 | 0 | 0 | 0 | 15 | 16 |  |
| battle_util.c | commun | 37 | 1 | 0 | 0 | 0 | 19 | 17 |  |
| fldeff_flash.c | commun | 22 | 15 | 0 | 2 | 13 | 2 | 5 | fldeff_flash.c (2) |
| option_menu.c | commun | 20 | 19 | 2 | 0 | 10 | 0 | 1 |  |
| battle_anim_psychic.c | commun | 26 | 0 | 0 | 0 | 100 | 10 | 16 |  |
| field_door.c | commun | 21 | 2 | 0 | 2 | 100 | 3 | 16 | copie kanto_field_door.c : 21/21 fonctions |
| librfu_rfu.c | commun | 86 | 0 | 0 | 0 | 100 | 70 | 16 |  |
| mystery_gift.c | commun | 45 | 1 | 1 | 0 | 100 | 28 | 16 |  |
| item_menu.c | commun | 116 | 100 | 0 | 98 | 98 | 3 | 13 | copie kanto_item_menu.c : 111/116 fonctions |
| battle_anim_fight.c | commun | 31 | 2 | 1 | 0 | 50 | 16 | 13 |  |
| battle_anim_fire.c | commun | 35 | 0 | 0 | 0 | 100 | 21 | 14 |  |
| battle_anim_water.c | commun | 48 | 0 | 0 | 0 | 100 | 34 | 14 |  |
| field_camera.c | commun | 29 | 6 | 1 | 1 | 33 | 13 | 10 | field_camera.c (1) |
| field_message_box.c | commun | 14 | 6 | 0 | 0 | 0 | 0 | 8 |  |
| pokemon_icon.c | commun | 23 | 5 | 1 | 0 | 20 | 8 | 10 |  |
| save_failed_screen.c | commun | 14 | 11 | 0 | 0 | 0 | 0 | 3 |  |
| text_window.c | commun | 19 | 15 | 0 | 3 | 20 | 2 | 2 | kanto_bag.c (2), text_window.c (1) |
| battle_ai_switch_items.c | commun | 13 | 0 | 0 | 0 | 100 | 0 | 13 |  |
| battle_anim_rock.c | commun | 22 | 0 | 0 | 0 | 100 | 9 | 13 |  |
| battle_bg.c | commun | 17 | 7 | 0 | 4 | 57 | 0 | 10 | copie kanto_battle_bg.c : 7/17 fonctions |
| field_screen_effect.c | commun | 19 | 9 | 0 | 0 | 0 | 6 | 4 |  |
| battle_message.c | commun | 14 | 5 | 0 | 0 | 0 | 2 | 7 |  |
| battle_records.c | commun | 31 | 21 | 0 | 16 | 76 | 3 | 7 | kanto_trainer_tower.c (15), kanto_seagallop.c (1) |
| main.c | commun | 28 | 2 | 0 | 0 | 0 | 16 | 10 |  |
| battle_anim_ground.c | commun | 25 | 2 | 2 | 0 | 100 | 12 | 11 |  |
| fldeff_cut.c | commun | 13 | 7 | 1 | 0 | 14 | 1 | 5 |  |
| pokeball.c | commun | 37 | 0 | 0 | 0 | 100 | 26 | 11 |  |
| menu_helpers.c | commun | 17 | 3 | 1 | 1 | 66 | 5 | 9 | kanto_bag.c (1) |
| region_map.c | commun | 140 | 130 | 0 | 130 | 100 | 0 | 10 | copie kanto_region_map.c : 140/140 fonctions |
| battle_anim_bug.c | commun | 13 | 0 | 0 | 0 | 100 | 4 | 9 |  |
| battle_anim_dragon.c | commun | 11 | 0 | 0 | 0 | 100 | 2 | 9 |  |
| battle_intro.c | commun | 10 | 1 | 0 | 0 | 0 | 1 | 8 |  |
| berry.c | commun | 9 | 1 | 0 | 0 | 0 | 0 | 8 |  |
| berry_powder.c | commun | 14 | 2 | 0 | 2 | 100 | 3 | 9 | kanto_specials.c (2) |
| ereader_helpers.c | commun | 17 | 1 | 1 | 0 | 100 | 7 | 9 |  |
| evolution_scene.c | commun | 23 | 1 | 1 | 0 | 100 | 13 | 9 |  |
| fldeff_rocksmash.c | commun | 10 | 7 | 1 | 0 | 14 | 0 | 3 |  |
| mail.c | commun | 10 | 9 | 1 | 0 | 11 | 0 | 1 |  |
| mail_data.c | commun | 12 | 4 | 0 | 0 | 0 | 3 | 5 |  |
| window.c | commun | 21 | 1 | 0 | 0 | 0 | 12 | 8 |  |
| decompress.c | commun | 18 | 0 | 0 | 0 | 100 | 10 | 8 |  |
| event_object_lock.c | commun | 11 | 4 | 0 | 1 | 25 | 2 | 5 | kanto_itemfinder.c (1) |
| item_menu_icons.c | commun | 17 | 9 | 0 | 9 | 100 | 0 | 8 | copie kanto_item_menu_icons.c : 17/17 fonctions |
| new_game.c | commun | 11 | 3 | 1 | 0 | 33 | 2 | 6 |  |
| script_pokemon_util.c | commun | 13 | 3 | 0 | 0 | 0 | 5 | 5 |  |
| title_screen.c | commun | 39 | 36 | 0 | 31 | 86 | 0 | 3 | copie kanto_title_screen.c : 33/39 fonctions |
| wireless_communication_status_screen.c | commun | 12 | 1 | 0 | 0 | 0 | 4 | 7 |  |
| battle_anim_sound_tasks.c | commun | 15 | 0 | 0 | 0 | 100 | 8 | 7 |  |
| coins.c | commun | 9 | 2 | 0 | 0 | 0 | 2 | 5 |  |
| ereader_screen.c | commun | 11 | 1 | 1 | 0 | 100 | 3 | 7 |  |
| intro.c | commun | 79 | 71 | 1 | 69 | 98 | 2 | 6 | copie kanto_intro.c : 72/79 fonctions |
| load_save.c | commun | 21 | 2 | 0 | 0 | 0 | 14 | 5 |  |
| map_name_popup.c | commun | 7 | 6 | 0 | 0 | 0 | 0 | 1 |  |
| AgbRfu_LinkManager.c | commun | 33 | 0 | 0 | 0 | 100 | 27 | 6 |  |
| clear_save_data_screen.c | commun | 8 | 8 | 2 | 0 | 25 | 0 | 0 |  |
| field_special_scene.c | commun | 6 | 4 | 0 | 0 | 0 | 0 | 2 |  |
| field_tasks.c | commun | 12 | 2 | 0 | 2 | 100 | 4 | 6 | field_tasks.c (2) |
| minigame_countdown.c | commun | 10 | 1 | 1 | 0 | 100 | 3 | 6 |  |
| multiboot.c | commun | 9 | 0 | 0 | 0 | 100 | 3 | 6 |  |
| mystery_gift_server.c | commun | 14 | 0 | 0 | 0 | 100 | 8 | 6 |  |
| reshow_battle_screen.c | commun | 7 | 1 | 0 | 0 | 0 | 1 | 5 |  |
| sound.c | commun | 48 | 2 | 0 | 0 | 0 | 42 | 4 |  |
| trainer_pokemon_sprites.c | commun | 22 | 0 | 0 | 0 | 100 | 16 | 6 |  |
| dma3_manager.c | commun | 5 | 1 | 0 | 0 | 0 | 0 | 4 |  |
| field_poison.c | commun | 7 | 0 | 0 | 0 | 100 | 2 | 5 |  |
| fldeff_sweetscent.c | commun | 7 | 1 | 0 | 0 | 0 | 2 | 4 |  |
| heal_location.c | commun | 5 | 4 | 0 | 0 | 0 | 0 | 1 |  |
| math_util.c | commun | 9 | 9 | 4 | 0 | 44 | 0 | 0 |  |
| mon_markings.c | commun | 15 | 0 | 0 | 0 | 100 | 10 | 5 |  |
| money.c | commun | 13 | 0 | 0 | 0 | 100 | 8 | 5 |  |
| save_location.c | commun | 10 | 1 | 0 | 1 | 100 | 4 | 5 | kanto_specials.c (1) |
| script_movement.c | commun | 19 | 0 | 0 | 0 | 100 | 14 | 5 |  |
| battle_anim_status_effects.c | commun | 12 | 0 | 0 | 0 | 100 | 8 | 4 |  |
| berry_fix_program.c | commun | 7 | 1 | 0 | 0 | 0 | 3 | 3 |  |
| fldeff_softboiled.c | commun | 8 | 0 | 0 | 0 | 100 | 4 | 4 |  |
| malloc.c | commun | 12 | 0 | 0 | 0 | 100 | 8 | 4 |  |
| palette_util.c | commun | 17 | 0 | 0 | 0 | 100 | 13 | 4 |  |
| pokemon_size_record.c | commun | 13 | 6 | 0 | 6 | 100 | 3 | 4 | pokemon_size_record.c (6) |
| safari_zone.c | commun | 8 | 0 | 0 | 0 | 100 | 4 | 4 |  |
| task.c | commun | 14 | 0 | 0 | 0 | 100 | 10 | 4 |  |
| union_room_battle.c | commun | 5 | 3 | 0 | 0 | 0 | 1 | 1 |  |
| util.c | commun | 10 | 0 | 0 | 0 | 100 | 6 | 4 |  |
| battle_util2.c | commun | 3 | 0 | 0 | 0 | 100 | 0 | 3 |  |
| dynamic_placeholder_text_util.c | commun | 5 | 1 | 0 | 1 | 100 | 1 | 3 | kanto_field_specials.c (1) |
| fldeff_dig.c | commun | 4 | 0 | 0 | 0 | 100 | 1 | 3 |  |
| fldeff_strength.c | commun | 4 | 2 | 1 | 0 | 50 | 0 | 2 |  |
| mini_printf.c | commun | 8 | 0 | 0 | 0 | 100 | 5 | 3 |  |
| mystery_gift_client.c | commun | 18 | 0 | 0 | 0 | 100 | 15 | 3 |  |
| pokemon_storage_system.c | commun | 21 | 2 | 0 | 0 | 0 | 18 | 1 |  |
| pokemon_summary_screen.c | commun | 137 | 134 | 0 | 134 | 100 | 0 | 3 | copie kanto_summary_screen.c : 137/137 fonctions |
| roamer.c | commun | 13 | 1 | 0 | 1 | 100 | 9 | 3 | roamer.c (1) |
| scanline_effect.c | commun | 9 | 0 | 0 | 0 | 100 | 6 | 3 |  |
| battle_anim_poison.c | commun | 9 | 0 | 0 | 0 | 100 | 7 | 2 |  |
| digit_obj_util.c | commun | 14 | 0 | 0 | 0 | 100 | 12 | 2 |  |
| fldeff_teleport.c | commun | 4 | 0 | 0 | 0 | 100 | 2 | 2 |  |
| librfu_intr.c | commun | 9 | 0 | 0 | 0 | 100 | 7 | 2 |  |
| random.c | commun | 2 | 0 | 0 | 0 | 100 | 0 | 2 |  |
| slot_machine.c | commun | 77 | 75 | 0 | 75 | 100 | 0 | 2 | copie kanto_slot_machine.c : 77/77 fonctions |
| wonder_news.c | commun | 9 | 0 | 0 | 0 | 100 | 7 | 2 |  |
| agb_flash.c | commun | 15 | 0 | 0 | 0 | 100 | 14 | 1 |  |
| blit.c | commun | 5 | 0 | 0 | 0 | 100 | 4 | 1 |  |
| coord_event_weather.c | commun | 1 | 0 | 0 | 0 | 100 | 0 | 1 |  |
| credits.c | commun | 16 | 14 | 0 | 14 | 100 | 1 | 1 | copie kanto_credits.c : 16/16 fonctions |
| diploma.c | commun | 10 | 9 | 0 | 9 | 100 | 0 | 1 | copie kanto_diploma.c : 10/10 fonctions |
| hof_pc.c | commun | 5 | 2 | 0 | 2 | 100 | 2 | 1 | kanto_specials.c (2) |
| image_processing_effects.c | commun | 38 | 0 | 0 | 0 | 100 | 37 | 1 |  |
| librfu_sio32id.c | commun | 4 | 0 | 0 | 0 | 100 | 3 | 1 |  |
| m4a.c | commun | 72 | 0 | 0 | 0 | 100 | 71 | 1 |  |
| play_time.c | commun | 5 | 0 | 0 | 0 | 100 | 4 | 1 |  |
| pokedex.c | commun | 8 | 0 | 0 | 0 | 100 | 7 | 1 |  |
| agb_flash_1m.c | commun | 2 | 0 | 0 | 0 | 100 | 2 | 0 |  |
| agb_flash_le.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| agb_flash_mx.c | commun | 5 | 0 | 0 | 0 | 100 | 5 | 0 |  |
| battle_anim_smokescreen.c | commun | 3 | 0 | 0 | 0 | 100 | 3 | 0 |  |
| data.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| decoration.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| gpu_regs.c | commun | 11 | 0 | 0 | 0 | 100 | 11 | 0 |  |
| graphics.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| librfu_stwi.c | commun | 48 | 0 | 0 | 0 | 100 | 48 | 0 |  |
| m4a_tables.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| mystery_event_msg.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| mystery_gift_link.c | commun | 10 | 0 | 0 | 0 | 100 | 10 | 0 |  |
| mystery_gift_scripts.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| post_battle_event_funcs.c | commun | 2 | 1 | 0 | 1 | 100 | 1 | 0 | kanto_hall_of_fame.c (1) |
| rom_header_gf.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| strings.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| tilesets.c | commun | 0 | 0 | 0 | 0 | 100 | 0 | 0 |  |
| trig.c | commun | 4 | 0 | 0 | 0 | 100 | 4 | 0 |  |

## Fichiers présents seulement dans Émeraude (103)

anim_mon_front_pics.c (0), apprentice.c (53), bard_music.c (3), battle_anim_throw.c (78), battle_arena.c (18),
battle_controller_player_partner.c (92), battle_controller_recorded_opponent.c (87),
battle_controller_recorded_player.c (86), battle_controller_wally.c (81), battle_dome.c (71),
battle_factory.c (26), battle_factory_screen.c (118), battle_palace.c (11), battle_pike.c (54),
battle_pyramid.c (51), battle_pyramid_bag.c (81), battle_tent.c (29), battle_transition_frontier.c (34),
battle_tv.c (12), berry_blender.c (81), berry_fix_graphics.c (1), berry_tag_screen.c (27), birch_pc.c (3),
braille.c (3), braille_puzzles.c (18), cable_car.c (22), clock.c (6), confetti_util.c (8), contest.c (205),
contest_ai.c (142), contest_effect.c (51), contest_link.c (17), contest_link_util.c (12),
contest_painting.c (20), contest_util.c (111), decoration_inventory.c (11), dewford_trend.c (13),
egg_hatch.c (25), faraway_island.c (15), field_region_map.c (6), field_weather_effect.c (106),
fldeff_escalator.c (6), fldeff_misc.c (62), fonts.c (0), frontier_pass.c (37), frontier_util.c (92),
give_gift_ribbon_to_party.c (1), gym_leader_rematch.c (3), international_string_util.c (18),
intro_credits_graphics.c (20), io_reg.c (0), item_icon.c (6), landmark.c (2), libisagbprn.c (16),
lilycove_lady.c (72), lottery_corner.c (8), match_call.c (54), mauville_old_man.c (59),
menu_specialized.c (57), mirage_tower.c (27), move_relearner.c (19), mystery_event_menu.c (6),
mystery_gift_view.c (18), pokeblock.c (58), pokeblock_feed.c (28), pokedex_area_region_map.c (4),
pokedex_area_screen.c (19), pokedex_cry_screen.c (14), pokemon_animation.c (240), pokenav.c (28),
pokenav_conditions.c (32), pokenav_conditions_gfx.c (28), pokenav_conditions_search_results.c (36),
pokenav_list.c (47), pokenav_main_menu.c (45), pokenav_match_call_data.c (52), pokenav_match_call_gfx.c (65),
pokenav_match_call_list.c (29), pokenav_menu_handler.c (27), pokenav_menu_handler_gfx.c (56),
pokenav_region_map.c (37), pokenav_ribbons_list.c (37), pokenav_ribbons_summary.c (55), rayquaza_scene.c (72),
record_mixing.c (43), recorded_battle.c (42), reload_save.c (1), reset_rtc_screen.c (19), rotating_gate.c (21),
rotating_tile_puzzle.c (6), roulette.c (104), rtc.c (26), secret_base.c (99), siirtc.c (16),
starter_choose.c (18), text_input_strings.c (0), time_events.c (10), trader.c (13), trainer_hill.c (59),
tv.c (207), use_pokeblock.c (51), walda_phrase.c (14), wallclock.c (25)
