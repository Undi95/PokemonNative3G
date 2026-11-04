# Tri des fonctions divergentes (RF / fusion)

> Généré par `tools/carto_divergentes.py` — ne pas éditer à la main. Classement : `tools/carto_divergentes.txt`.

Règles de famille (`FAMILY_RULES`, sauf marqueur propre à Kanto dans le corps de RF) :

- `^(link|link_rfu|librfu|AgbRfu|union_room|cable_club|trade|berry_crush|dodrio_berry_picking|pokemon_jump|mystery_|record_mixing|wireless_communication|battle_controller_link_|berry_fix)` : écartée — link d'Émeraude dans les deux régions (règle des variantes 2026-11-02 ; caché : LINK_ENABLED)
- `^battle_anim` : écartée — animations de combat d'Émeraude dans les deux régions (règle des variantes, docs/VARIANTES-RF.md)
- `^(battle_script_commands|battle_util|battle_main|battle_controller_(player|opponent|player_partner|safari|wally)|battle_ai_|battle_interface|battle_gfx_sfx_util|battle_message|battle_bg|battle_setup|battle_transition|battle_tv|reshow_battle_screen|battle_records|battle_dome|battle_tower|pokeball|battle_intro|recorded_battle)` : écartée — moteur de combat d'Émeraude dans les deux régions (règle des variantes) ; sans marqueur des combats propres à Kanto (vieil homme, Pokédude, fantôme, Safari, Tour des Dresseurs, légendaires)
- `^(bg|sprite|text|palette|menu|list_menu|string_util|menu_indicators|new_menu_helpers|main|gpu_regs|malloc|decompress|window|blit|dma3_manager|task|scanline_effect|random|util|text_printer|text_window|text_window_graphics|window_8bpp|tilemap_util|blend_palette|librfu|m4a|sound|save|load_save|agb_flash|siirtc|rtc|play_time|multiboot|isagbprn|trig|math_util)\.c$` : écartée — moteur commun d'Émeraude (graphismes, texte, menus, sauvegarde, son) dans les deux régions (règle des variantes) ; les écrans de RF qui en ont besoin ont leur copie kanto_*.c
- `^pokemon_storage_system` : écartée — écran du PC d'Émeraude dans les deux régions (fonds de RF ajoutés ; règle des variantes)

| Fichier RF | Divergentes | Même code une fois normalisé | Par règle de famille | Classées | À lire | Corps introuvable |
|---|---|---|---|---|---|---|
| evolution_graphics.c | 8 | 2 | 0 | 0 | 6 | 0 |
| field_tasks.c | 6 | 0 | 0 | 0 | 6 | 0 |
| new_game.c | 6 | 0 | 0 | 0 | 6 | 0 |
| start_menu.c | 10 | 4 | 0 | 0 | 6 | 0 |
| field_message_box.c | 8 | 3 | 0 | 0 | 5 | 0 |
| field_poison.c | 5 | 0 | 0 | 0 | 5 | 0 |
| minigame_countdown.c | 6 | 1 | 0 | 0 | 5 | 0 |
| mon_markings.c | 5 | 0 | 0 | 0 | 5 | 0 |
| party_menu_specials.c | 5 | 0 | 0 | 0 | 5 | 0 |
| save_location.c | 5 | 0 | 0 | 0 | 5 | 0 |
| script_pokemon_util.c | 5 | 0 | 0 | 0 | 5 | 0 |
| special_field_anim.c | 6 | 1 | 0 | 0 | 5 | 0 |
| trainer_pokemon_sprites.c | 6 | 1 | 0 | 0 | 5 | 0 |
| battle_controller_opponent.c | 34 | 5 | 21 | 4 | 4 | 0 |
| easy_chat.c | 10 | 6 | 0 | 0 | 4 | 0 |
| fldeff_cut.c | 5 | 1 | 0 | 0 | 4 | 0 |
| fldeff_flash.c | 5 | 1 | 0 | 0 | 4 | 0 |
| fldeff_softboiled.c | 4 | 0 | 0 | 0 | 4 | 0 |
| fldeff_sweetscent.c | 4 | 0 | 0 | 0 | 4 | 0 |
| menu2.c | 4 | 0 | 0 | 0 | 4 | 0 |
| pokemon_size_record.c | 4 | 0 | 0 | 0 | 4 | 0 |
| reshow_battle_screen.c | 5 | 0 | 1 | 0 | 4 | 0 |
| safari_zone.c | 4 | 0 | 0 | 0 | 4 | 0 |
| script_movement.c | 5 | 1 | 0 | 0 | 4 | 0 |
| buy_menu_helpers.c | 4 | 1 | 0 | 0 | 3 | 0 |
| dodrio_berry_picking.c | 44 | 11 | 30 | 0 | 3 | 0 |
| field_weather_util.c | 6 | 3 | 0 | 0 | 3 | 0 |
| fldeff_dig.c | 3 | 0 | 0 | 0 | 3 | 0 |
| fldeff_rocksmash.c | 3 | 0 | 0 | 0 | 3 | 0 |
| intro.c | 6 | 3 | 0 | 0 | 3 | 0 |
| mini_printf.c | 3 | 0 | 0 | 0 | 3 | 0 |
| money.c | 5 | 2 | 0 | 0 | 3 | 0 |
| player_pc.c | 4 | 1 | 0 | 0 | 3 | 0 |
| pokemon_special_anim_scene.c | 3 | 0 | 0 | 0 | 3 | 0 |
| roamer.c | 3 | 0 | 0 | 0 | 3 | 0 |
| save_failed_screen.c | 3 | 0 | 0 | 0 | 3 | 0 |
| tileset_anims.c | 3 | 0 | 0 | 0 | 3 | 0 |
| trainer_tower.c | 3 | 0 | 0 | 0 | 3 | 0 |
| battle_ai_script_commands.c | 88 | 3 | 81 | 0 | 2 | 2 |
| battle_bg.c | 10 | 1 | 7 | 0 | 2 | 0 |
| battle_message.c | 7 | 2 | 3 | 0 | 2 | 0 |
| battle_setup.c | 25 | 3 | 20 | 0 | 2 | 0 |
| battle_util2.c | 3 | 0 | 1 | 0 | 2 | 0 |
| braille_text.c | 2 | 0 | 0 | 0 | 2 | 0 |
| cable_club.c | 28 | 4 | 22 | 0 | 2 | 0 |
| coins.c | 5 | 3 | 0 | 0 | 2 | 0 |
| digit_obj_util.c | 2 | 0 | 0 | 0 | 2 | 0 |
| field_screen_effect.c | 4 | 2 | 0 | 0 | 2 | 0 |
| field_special_scene.c | 2 | 0 | 0 | 0 | 2 | 0 |
| fldeff_strength.c | 2 | 0 | 0 | 0 | 2 | 0 |
| itemfinder.c | 2 | 0 | 0 | 0 | 2 | 0 |
| palette_util.c | 4 | 2 | 0 | 0 | 2 | 0 |
| pokeball.c | 11 | 4 | 5 | 0 | 2 | 0 |
| region_map.c | 10 | 8 | 0 | 0 | 2 | 0 |
| title_screen.c | 3 | 0 | 0 | 1 | 2 | 0 |
| wonder_news.c | 2 | 0 | 0 | 0 | 2 | 0 |
| battle_controller_player.c | 69 | 16 | 42 | 9 | 1 | 1 |
| battle_interface.c | 35 | 10 | 24 | 0 | 1 | 0 |
| battle_records.c | 7 | 2 | 4 | 0 | 1 | 0 |
| battle_util.c | 17 | 7 | 9 | 0 | 1 | 0 |
| berry_crush.c | 58 | 10 | 47 | 0 | 1 | 0 |
| cereader_tool.c | 1 | 0 | 0 | 0 | 1 | 0 |
| coord_event_weather.c | 1 | 0 | 0 | 0 | 1 | 0 |
| credits.c | 1 | 0 | 0 | 0 | 1 | 0 |
| easy_chat_2.c | 7 | 6 | 0 | 0 | 1 | 0 |
| fldeff_berrytree.c | 1 | 0 | 0 | 0 | 1 | 0 |
| fldeff_poison.c | 1 | 0 | 0 | 0 | 1 | 0 |
| fldeff_teleport.c | 2 | 1 | 0 | 0 | 1 | 0 |
| heal_location.c | 1 | 0 | 0 | 0 | 1 | 0 |
| hof_pc.c | 1 | 0 | 0 | 0 | 1 | 0 |
| image_processing_effects.c | 1 | 0 | 0 | 0 | 1 | 0 |
| learn_move.c | 2 | 1 | 0 | 0 | 1 | 0 |
| mail_data.c | 5 | 4 | 0 | 0 | 1 | 0 |
| main_menu.c | 2 | 1 | 0 | 0 | 1 | 0 |
| map_name_popup.c | 1 | 0 | 0 | 0 | 1 | 0 |
| option_menu.c | 1 | 0 | 0 | 0 | 1 | 0 |
| pokedex.c | 1 | 0 | 0 | 0 | 1 | 0 |
| pokemon_storage_system_graphics.c | 51 | 34 | 16 | 0 | 1 | 0 |
| pokemon_summary_screen.c | 3 | 2 | 0 | 0 | 1 | 0 |
| reset_save_heap.c | 1 | 0 | 0 | 0 | 1 | 0 |
| tm_case.c | 2 | 1 | 0 | 0 | 1 | 0 |
| trade.c | 47 | 5 | 41 | 0 | 1 | 0 |
| trainer_fan_club.c | 13 | 12 | 0 | 0 | 1 | 0 |
| union_room.c | 65 | 20 | 44 | 0 | 1 | 0 |
| AgbRfu_LinkManager.c | 6 | 1 | 5 | 0 | 0 | 0 |
| agb_flash.c | 1 | 1 | 0 | 0 | 0 | 0 |
| battle_ai_switch_items.c | 13 | 1 | 11 | 0 | 0 | 1 |
| battle_anim.c | 26 | 0 | 26 | 0 | 0 | 0 |
| battle_anim_bug.c | 9 | 0 | 9 | 0 | 0 | 0 |
| battle_anim_dark.c | 18 | 1 | 17 | 0 | 0 | 0 |
| battle_anim_dragon.c | 9 | 0 | 9 | 0 | 0 | 0 |
| battle_anim_effects_1.c | 77 | 9 | 68 | 0 | 0 | 0 |
| battle_anim_effects_2.c | 35 | 19 | 16 | 0 | 0 | 0 |
| battle_anim_effects_3.c | 35 | 18 | 17 | 0 | 0 | 0 |
| battle_anim_electric.c | 19 | 1 | 18 | 0 | 0 | 0 |
| battle_anim_fight.c | 13 | 5 | 8 | 0 | 0 | 0 |
| battle_anim_fire.c | 14 | 3 | 11 | 0 | 0 | 0 |
| battle_anim_flying.c | 16 | 4 | 12 | 0 | 0 | 0 |
| battle_anim_ghost.c | 19 | 2 | 17 | 0 | 0 | 0 |
| battle_anim_ground.c | 11 | 2 | 9 | 0 | 0 | 0 |
| battle_anim_ice.c | 22 | 3 | 19 | 0 | 0 | 0 |
| battle_anim_mon_movement.c | 22 | 1 | 21 | 0 | 0 | 0 |
| battle_anim_mons.c | 69 | 10 | 59 | 0 | 0 | 0 |
| battle_anim_normal.c | 22 | 1 | 21 | 0 | 0 | 0 |
| battle_anim_poison.c | 2 | 2 | 0 | 0 | 0 | 0 |
| battle_anim_psychic.c | 16 | 1 | 15 | 0 | 0 | 0 |
| battle_anim_rock.c | 13 | 3 | 10 | 0 | 0 | 0 |
| battle_anim_sound_tasks.c | 7 | 0 | 7 | 0 | 0 | 0 |
| battle_anim_special.c | 24 | 14 | 10 | 0 | 0 | 0 |
| battle_anim_status_effects.c | 4 | 2 | 2 | 0 | 0 | 0 |
| battle_anim_utility_funcs.c | 29 | 4 | 25 | 0 | 0 | 0 |
| battle_anim_water.c | 14 | 4 | 10 | 0 | 0 | 0 |
| battle_controller_link_opponent.c | 20 | 4 | 15 | 1 | 0 | 0 |
| battle_controller_link_partner.c | 20 | 4 | 15 | 1 | 0 | 0 |
| battle_controller_oak_old_man.c | 26 | 9 | 0 | 17 | 0 | 0 |
| battle_controller_pokedude.c | 30 | 29 | 0 | 1 | 0 | 0 |
| battle_controller_safari.c | 12 | 5 | 5 | 2 | 0 | 0 |
| battle_controllers.c | 16 | 3 | 0 | 13 | 0 | 0 |
| battle_gfx_sfx_util.c | 29 | 9 | 20 | 0 | 0 | 0 |
| battle_intro.c | 8 | 2 | 6 | 0 | 0 | 0 |
| battle_main.c | 56 | 5 | 42 | 9 | 0 | 0 |
| battle_script_commands.c | 116 | 39 | 69 | 8 | 0 | 0 |
| battle_tower.c | 12 | 0 | 12 | 0 | 0 | 0 |
| battle_transition.c | 77 | 11 | 66 | 0 | 0 | 0 |
| berry.c | 8 | 0 | 0 | 8 | 0 | 0 |
| berry_fix_program.c | 3 | 0 | 3 | 0 | 0 | 0 |
| berry_powder.c | 9 | 1 | 0 | 8 | 0 | 0 |
| bg.c | 42 | 4 | 38 | 0 | 0 | 0 |
| bike.c | 12 | 1 | 0 | 11 | 0 | 0 |
| blend_palette.c | 1 | 0 | 1 | 0 | 0 | 0 |
| blit.c | 1 | 0 | 1 | 0 | 0 | 0 |
| daycare.c | 35 | 10 | 0 | 24 | 0 | 1 |
| decompress.c | 8 | 1 | 7 | 0 | 0 | 0 |
| diploma.c | 1 | 1 | 0 | 0 | 0 | 0 |
| dma3_manager.c | 4 | 1 | 3 | 0 | 0 | 0 |
| dynamic_placeholder_text_util.c | 3 | 3 | 0 | 0 | 0 | 0 |
| ereader_helpers.c | 9 | 0 | 0 | 9 | 0 | 0 |
| ereader_screen.c | 7 | 0 | 0 | 7 | 0 | 0 |
| event_data.c | 16 | 5 | 0 | 11 | 0 | 0 |
| event_object_lock.c | 5 | 5 | 0 | 0 | 0 | 0 |
| event_object_movement.c | 378 | 301 | 0 | 77 | 0 | 0 |
| evolution_scene.c | 9 | 2 | 0 | 7 | 0 | 0 |
| field_camera.c | 10 | 2 | 0 | 8 | 0 | 0 |
| field_control_avatar.c | 25 | 2 | 0 | 23 | 0 | 0 |
| field_door.c | 16 | 5 | 0 | 11 | 0 | 0 |
| field_effect.c | 94 | 34 | 0 | 60 | 0 | 0 |
| field_effect_helpers.c | 60 | 7 | 0 | 53 | 0 | 0 |
| field_fadetransition.c | 24 | 13 | 0 | 11 | 0 | 0 |
| field_player_avatar.c | 64 | 26 | 0 | 38 | 0 | 0 |
| field_specials.c | 20 | 2 | 0 | 18 | 0 | 0 |
| field_weather.c | 15 | 8 | 0 | 7 | 0 | 0 |
| field_weather_effects.c | 38 | 19 | 0 | 19 | 0 | 0 |
| fieldmap.c | 34 | 3 | 0 | 31 | 0 | 0 |
| hall_of_fame.c | 23 | 13 | 0 | 10 | 0 | 0 |
| isagbprn.c | 7 | 0 | 7 | 0 | 0 | 0 |
| item.c | 20 | 7 | 0 | 12 | 0 | 1 |
| item_menu.c | 13 | 5 | 0 | 8 | 0 | 0 |
| item_menu_icons.c | 8 | 8 | 0 | 0 | 0 | 0 |
| item_use.c | 14 | 4 | 0 | 10 | 0 | 0 |
| librfu_intr.c | 2 | 0 | 2 | 0 | 0 | 0 |
| librfu_rfu.c | 16 | 4 | 12 | 0 | 0 | 0 |
| librfu_sio32id.c | 1 | 0 | 1 | 0 | 0 | 0 |
| link.c | 56 | 32 | 24 | 0 | 0 | 0 |
| link_rfu_2.c | 66 | 11 | 55 | 0 | 0 | 0 |
| link_rfu_3.c | 20 | 10 | 10 | 0 | 0 | 0 |
| list_menu.c | 25 | 6 | 19 | 0 | 0 | 0 |
| load_save.c | 5 | 0 | 5 | 0 | 0 | 0 |
| m4a.c | 1 | 0 | 1 | 0 | 0 | 0 |
| mail.c | 1 | 1 | 0 | 0 | 0 | 0 |
| main.c | 10 | 1 | 9 | 0 | 0 | 0 |
| malloc.c | 4 | 0 | 4 | 0 | 0 | 0 |
| menu.c | 17 | 2 | 15 | 0 | 0 | 0 |
| menu_helpers.c | 9 | 0 | 0 | 9 | 0 | 0 |
| menu_indicators.c | 15 | 1 | 14 | 0 | 0 | 0 |
| metatile_behavior.c | 23 | 3 | 0 | 20 | 0 | 0 |
| multiboot.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_event_script.c | 21 | 14 | 7 | 0 | 0 | 0 |
| mystery_gift.c | 16 | 3 | 13 | 0 | 0 | 0 |
| mystery_gift_client.c | 3 | 1 | 2 | 0 | 0 | 0 |
| mystery_gift_menu.c | 15 | 7 | 8 | 0 | 0 | 0 |
| mystery_gift_server.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_gift_show_card.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_gift_show_news.c | 7 | 4 | 3 | 0 | 0 | 0 |
| naming_screen.c | 37 | 8 | 0 | 29 | 0 | 0 |
| new_menu_helpers.c | 24 | 10 | 14 | 0 | 0 | 0 |
| overworld.c | 92 | 27 | 0 | 65 | 0 | 0 |
| palette.c | 23 | 7 | 14 | 0 | 0 | 2 |
| party_menu.c | 145 | 38 | 0 | 107 | 0 | 0 |
| play_time.c | 1 | 0 | 1 | 0 | 0 | 0 |
| pokemon.c | 62 | 23 | 0 | 39 | 0 | 0 |
| pokemon_icon.c | 10 | 1 | 0 | 9 | 0 | 0 |
| pokemon_jump.c | 26 | 8 | 18 | 0 | 0 | 0 |
| pokemon_special_anim.c | 1 | 1 | 0 | 0 | 0 | 0 |
| pokemon_storage_system.c | 1 | 0 | 0 | 0 | 0 | 1 |
| pokemon_storage_system_data.c | 49 | 24 | 25 | 0 | 0 | 0 |
| pokemon_storage_system_menu.c | 13 | 9 | 4 | 0 | 0 | 0 |
| pokemon_storage_system_misc.c | 39 | 11 | 28 | 0 | 0 | 0 |
| pokemon_storage_system_tasks.c | 71 | 32 | 38 | 1 | 0 | 0 |
| random.c | 2 | 0 | 2 | 0 | 0 | 0 |
| save.c | 26 | 11 | 15 | 0 | 0 | 0 |
| scanline_effect.c | 3 | 0 | 3 | 0 | 0 | 0 |
| scrcmd.c | 68 | 9 | 0 | 59 | 0 | 0 |
| script.c | 13 | 4 | 0 | 9 | 0 | 0 |
| script_menu.c | 8 | 1 | 0 | 7 | 0 | 0 |
| shop.c | 39 | 18 | 0 | 21 | 0 | 0 |
| slot_machine.c | 2 | 2 | 0 | 0 | 0 | 0 |
| sound.c | 4 | 0 | 4 | 0 | 0 | 0 |
| sprite.c | 20 | 9 | 11 | 0 | 0 | 0 |
| string_util.c | 23 | 8 | 8 | 7 | 0 | 0 |
| task.c | 4 | 0 | 4 | 0 | 0 | 0 |
| text.c | 17 | 2 | 15 | 0 | 0 | 0 |
| text_printer.c | 8 | 2 | 6 | 0 | 0 | 0 |
| text_window.c | 2 | 2 | 0 | 0 | 0 | 0 |
| tilemap_util.c | 9 | 0 | 9 | 0 | 0 | 0 |
| trade_scene.c | 32 | 7 | 25 | 0 | 0 | 0 |
| trainer_card.c | 52 | 31 | 0 | 21 | 0 | 0 |
| trainer_see.c | 9 | 2 | 0 | 7 | 0 | 0 |
| union_room_battle.c | 1 | 0 | 1 | 0 | 0 | 0 |
| union_room_chat.c | 15 | 2 | 13 | 0 | 0 | 0 |
| union_room_chat_display.c | 8 | 2 | 6 | 0 | 0 | 0 |
| union_room_chat_objects.c | 1 | 1 | 0 | 0 | 0 | 0 |
| union_room_player_avatar.c | 18 | 8 | 10 | 0 | 0 | 0 |
| util.c | 4 | 2 | 2 | 0 | 0 | 0 |
| vs_seeker.c | 3 | 3 | 0 | 0 | 0 | 0 |
| wild_encounter.c | 12 | 1 | 0 | 11 | 0 | 0 |
| window.c | 8 | 1 | 7 | 0 | 0 | 0 |
| window_8bpp.c | 3 | 3 | 0 | 0 | 0 | 0 |
| wireless_communication_status_screen.c | 7 | 0 | 7 | 0 | 0 | 0 |
| **total** | 4254 | 1366 | 1692 | 968 | 219 | 9 |

## À lire

- `battle_ai_script_commands.c` **BattleAI_HandleItemUseBeforeAISetup** : 14 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_ai_script_commands.c` **BattleAI_SetupAIData** : 36 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_LEGENDARY_FRLG, BATTLE_TYPE_TRAINER_TOWER
- `battle_ai_script_commands.c` **Cmd_if_equal_** : corps introuvable dans la fusion (déplacé ?)
- `battle_ai_script_commands.c` **Cmd_if_not_equal_** : corps introuvable dans la fusion (déplacé ?)
- `battle_ai_switch_items.c` **GetAI_ItemType** : corps introuvable dans la fusion (déplacé ?)
- `battle_bg.c` **LoadBattleMenuWindowGfx** : 15 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_POKEDUDE
- `battle_bg.c` **DrawBattleEntryBackground** ✓ : 11 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER, TRAINER_CLASS_CHAMPION, TRAINER_CLASS_LEADER
- `battle_controller_opponent.c` **OpponentHandleLoadMonSprite** : 4 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST
- `battle_controller_opponent.c` **OpponentHandleDrawTrainerPic** : 10 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_controller_opponent.c` **OpponentHandleTrainerSlide** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_controller_opponent.c` **OpponentHandlePrintString** : 3 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_player.c` **HandleMoveSwitching** : 21 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_player.c` **MoveSelectionDisplayPpNumber** : corps introuvable dans la fusion (déplacé ?)
- `battle_interface.c` **TryAddPokeballIconToHealthbox** : 5 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_message.c` **BufferStringBattle** : 42 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_GHOST_UNVEILED, BATTLE_TYPE_OLD_MAN_TUTORIAL
- `battle_message.c` **BattleStringExpandPlaceholders** : 73 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER, FLAG_SYS_NOT_SOMEONES_PC, TRAINER_CLASS_CHAMPION, TRAINER_CLASS_FACTORY_HEAD, TRAINER_CLASS_RIVAL_EARLY
- `battle_records.c` **UpdatePlayerLinkBattleRecords** : 8 différence(s) ; marqueurs de RF absents de la fusion : MAP_GROUP, MAP_NUM, MAP_UNION_ROOM
- `battle_setup.c` **StartGroudonKyogreBattle** : 5 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_TRAINER
- `battle_setup.c` **StartRegiBattle** : 5 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_TRAINER
- `battle_util.c` **IsMonDisobedient** : 16 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, FLAG_BADGE02_GET, FLAG_BADGE04_GET, FLAG_BADGE06_GET, FLAG_BADGE08_GET
- `battle_util2.c` **AllocateBattleResources** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `battle_util2.c` **FreeBattleResources** : 3 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `berry_crush.c` **Cmd_SignalReadyToBegin** : 3 différence(s) ; marqueurs de RF absents de la fusion : MUS_GAME_CORNER
- `braille_text.c` **FontFunc_Braille** : 9 différence(s)
- `braille_text.c` **DecompressGlyph_Braille** : 11 différence(s)
- `buy_menu_helpers.c` **BuyMenuInitWindows** : 2 différence(s)
- `buy_menu_helpers.c` **BuyMenuDisplayMessage** : 1 différence(s)
- `buy_menu_helpers.c` **BuyMenuConfirmPurchase** : 1 différence(s)
- `cable_club.c` **Task_StartWiredCableClubBattle** : 6 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_GYM_LEADER, MUS_RS_VS_TRAINER
- `cable_club.c` **Task_StartWirelessCableClubBattle** : 13 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_GYM_LEADER, MUS_RS_VS_TRAINER
- `cereader_tool.c` **GetTrainerHillUnkVal** : 2 différence(s)
- `coins.c` **AddCoins** : 5 différence(s)
- `coins.c` **ShowCoinsWindow** ✓ : 7 différence(s)
- `coord_event_weather.c` **DoCoordEventWeather** : 1 différence(s)
- `credits.c` **CB2_Credits** : 1 différence(s) ; marqueurs de RF absents de la fusion : FLAG_DONT_SHOW_MAP_NAME_POPUP
- `digit_obj_util.c` **DigitObjUtil_CreatePrinter** : 8 différence(s)
- `digit_obj_util.c` **DrawNumObjsMinusInBack** : 2 différence(s)
- `dodrio_berry_picking.c` **InitResults_Leader** : 8 différence(s) ; marqueurs de RF absents de la fusion : MUS_VICTORY_WILD
- `dodrio_berry_picking.c` **InitResults_Member** : 10 différence(s) ; marqueurs de RF absents de la fusion : MUS_VICTORY_WILD
- `dodrio_berry_picking.c` **ShowResults** : 40 différence(s) ; marqueurs de RF absents de la fusion : MUS_VICTORY_WILD
- `easy_chat.c` **EasyChat_GetNumWordsInGroup** : 1 différence(s)
- `easy_chat.c` **GetEasyChatWord** : 2 différence(s)
- `easy_chat.c` **InitEasyChatPhrases** : 4 différence(s)
- `easy_chat.c` **InitQuestionnaireWords** : 1 différence(s)
- `easy_chat_2.c` **ShowEasyChatScreen** : 1 différence(s)
- `evolution_graphics.c` **SetEvoSparklesMatrices** : 2 différence(s)
- `evolution_graphics.c` **LoadEvoSparkleSpriteAndPal** : 1 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_ArcDown** : 2 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_CircleInward** : 2 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_SprayAndFlash_Trade** : 1 différence(s)
- `evolution_graphics.c` **CycleEvolutionMonSprite** : 13 différence(s)
- `field_message_box.c` **InitFieldMessageBox** : 1 différence(s)
- `field_message_box.c` **ShowFieldMessage** : 1 différence(s)
- `field_message_box.c` **ShowFieldAutoScrollMessage** : 1 différence(s)
- `field_message_box.c` **ForceShowFieldAutoScrollMessage** : 1 différence(s)
- `field_message_box.c` **IsFieldMessageBoxHidden** : 1 différence(s)
- `field_poison.c` **AllMonsFainted** : 1 différence(s)
- `field_poison.c` **FaintFromFieldPoison** : 4 différence(s)
- `field_poison.c` **MonFaintedFromPoison** : 5 différence(s)
- `field_poison.c` **Task_TryFieldPoisonWhiteOut** : 1 différence(s)
- `field_poison.c` **DoPoisonFieldEffect** : 4 différence(s)
- `field_screen_effect.c` **AnimateFlash** : 2 différence(s)
- `field_screen_effect.c` **WriteFlashScanlineEffectBuffer** : 4 différence(s)
- `field_special_scene.c` **FieldCB_ShowPortholeView** : 1 différence(s)
- `field_special_scene.c` **LookThroughPorthole** : 1 différence(s)
- `field_tasks.c` **Task_RunTimeBasedEvents** : 3 différence(s)
- `field_tasks.c` **SetUpFieldTasks** : 1 différence(s)
- `field_tasks.c` **MarkIcePuzzleCoordVisited** : 8 différence(s)
- `field_tasks.c` **AshGrassPerStepCallback** : 2 différence(s)
- `field_tasks.c` **SetCrackedFloorHoleMetatile** : 3 différence(s)
- `field_tasks.c` **CrackedFloorPerStepCallback** : 1 différence(s)
- `field_weather_util.c` **DoCurrentWeather** : 1 différence(s)
- `field_weather_util.c` **ResumePausedWeather** : 1 différence(s)
- `field_weather_util.c` **TranslateWeatherNum** : 1 différence(s)
- `fldeff_berrytree.c` **DoWateringBerryTreeAnim** : 1 différence(s)
- `fldeff_cut.c` **SetUpFieldMove_Cut** : 3 différence(s)
- `fldeff_cut.c` **FldEff_UseCutOnGrass** : 1 différence(s)
- `fldeff_cut.c` **FldEff_UseCutOnTree** : 1 différence(s)
- `fldeff_cut.c` **FldEff_CutGrass** : 13 différence(s)
- `fldeff_dig.c` **SetUpFieldMove_Dig** : 1 différence(s)
- `fldeff_dig.c` **FldEff_UseDig** : 3 différence(s)
- `fldeff_dig.c` **StartDigFieldEffect** : 1 différence(s)
- `fldeff_flash.c` **SetUpFieldMove_Flash** : 5 différence(s)
- `fldeff_flash.c` **FieldCallback_Flash** : 4 différence(s)
- `fldeff_flash.c` **CB2_DoChangeMap** : 2 différence(s)
- `fldeff_flash.c` **TryDoMapTransition** : 5 différence(s)
- `fldeff_poison.c` **Task_FieldPoisonEffect** : 9 différence(s)
- `fldeff_rocksmash.c` **CheckObjectGraphicsInFrontOfPlayer** : 2 différence(s)
- `fldeff_rocksmash.c` **SetUpFieldMove_RockSmash** : 2 différence(s)
- `fldeff_rocksmash.c` **FldEff_UseRockSmash** : 1 différence(s)
- `fldeff_softboiled.c` **SetUpFieldMove_SoftBoiled** : 5 différence(s)
- `fldeff_softboiled.c` **Task_TryUseSoftboiledOnPartyMon** : 4 différence(s)
- `fldeff_softboiled.c` **Task_FinishSoftboiled** : 2 différence(s)
- `fldeff_softboiled.c` **Task_ChooseNewMonForSoftboiled** : 2 différence(s)
- `fldeff_strength.c` **SetUpFieldMove_Strength** : 6 différence(s)
- `fldeff_strength.c` **FldEff_UseStrength** : 3 différence(s)
- `fldeff_sweetscent.c` **FldEff_SweetScent** : 2 différence(s)
- `fldeff_sweetscent.c` **StartSweetScentFieldEffect** : 2 différence(s)
- `fldeff_sweetscent.c` **TrySweetScentEncounter** : 11 différence(s)
- `fldeff_sweetscent.c` **FailSweetScentEncounter** : 1 différence(s)
- `fldeff_teleport.c` **FldEff_UseTeleport** : 2 différence(s)
- `heal_location.c` **GetHealLocation** : 2 différence(s)
- `hof_pc.c` **ReshowPCMenuAfterHallOfFamePC** : 1 différence(s)
- `image_processing_effects.c` **ConvertColorToGrayscale** : 17 différence(s)
- `intro.c` **LoadCopyrightGraphics** : 8 différence(s)
- `intro.c` **SetUpCopyrightScreen** : 34 différence(s)
- `intro.c` **CB2_InitCopyrightScreenAfterBootup** : 2 différence(s)
- `itemfinder.c` **ItemUseOnFieldCB_Itemfinder** : 1 différence(s)
- `itemfinder.c` **CreateStarSprite** : 1 différence(s)
- `learn_move.c` **PrintTextOnWindow** : 1 différence(s)
- `mail_data.c` **GiveMailToMon** : 8 différence(s)
- `main_menu.c` **CB2_InitMainMenu** : 2 différence(s)
- `map_name_popup.c` **ShowMapNamePopup** ✓ : 2 différence(s) ; marqueurs de RF absents de la fusion : FLAG_DONT_SHOW_MAP_NAME_POPUP
- `menu2.c` **AddTextPrinterParameterized3** : 4 différence(s)
- `menu2.c` **AddTextPrinterParameterized4** : 4 différence(s)
- `menu2.c` **AddTextPrinterParameterized5** : 4 différence(s)
- `menu2.c` **UnusedBlitBitmapRect** : 15 différence(s)
- `mini_printf.c` **mini_pchar_decode** : 1 différence(s)
- `mini_printf.c` **_putsEncoded** : 1 différence(s)
- `mini_printf.c` **mini_vpprintf** : 2 différence(s)
- `minigame_countdown.c` **RunMinigameCountdownDigitsAnim** : 9 différence(s)
- `minigame_countdown.c` **SpriteCB_Start** : 3 différence(s)
- `minigame_countdown.c` **Load321StartGfx** : 3 différence(s)
- `minigame_countdown.c` **CreateNumberSprite** : 2 différence(s)
- `minigame_countdown.c` **CreateStartSprite** : 2 différence(s)
- `mon_markings.c` **BufferMenuWindowTiles** : 2 différence(s)
- `mon_markings.c` **FreeMonMarkingsMenu** : 13 différence(s)
- `mon_markings.c` **CreateMonMarkingAllCombosSprite** : 2 différence(s)
- `mon_markings.c` **CreateMonMarkingComboSprite** : 2 différence(s)
- `mon_markings.c` **UpdateMonMarkingTiles** : 3 différence(s)
- `money.c` **PrintMoneyAmount** : 4 différence(s)
- `money.c` **PrintMoneyAmountInMoneyBoxWithBorder** ✓ : 2 différence(s)
- `money.c` **DrawMoneyBox** ✓ : 5 différence(s)
- `new_game.c` **CopyTrainerId** : 3 différence(s)
- `new_game.c` **InitPlayerTrainerId** : 2 différence(s)
- `new_game.c` **SetDefaultOptions** : 1 différence(s)
- `new_game.c` **ClearPokedexFlags** : 1 différence(s)
- `new_game.c` **ResetMenuAndMonGlobals** : 4 différence(s)
- `new_game.c` **NewGameInitData** : 19 différence(s)
- `option_menu.c` **CB2_InitOptionMenu** : 5 différence(s)
- `palette.c` **IsBlendPalettesGraduallyTaskActive** : corps introuvable dans la fusion (déplacé ?)
- `palette.c` **DestroyBlendPalettesGraduallyTask** : corps introuvable dans la fusion (déplacé ?)
- `palette_util.c` **RouletteFlash_FlashPalette** : 2 différence(s)
- `palette_util.c` **UpdatePulseBlend** : 2 différence(s)
- `party_menu_specials.c` **ChoosePartyMon** : 3 différence(s)
- `party_menu_specials.c` **ChooseMonForMoveRelearner** : 4 différence(s)
- `party_menu_specials.c` **Task_ChoosePartyMon** : 4 différence(s)
- `party_menu_specials.c` **GetNumMovesSelectedMonHas** : 4 différence(s)
- `party_menu_specials.c` **MoveDeleterForgetMove** : 2 différence(s)
- `player_pc.c` **NewGameInitPCItems** : 12 différence(s)
- `player_pc.c` **BedroomPC** : 8 différence(s)
- `player_pc.c` **PlayerPC** : 8 différence(s)
- `pokeball.c` **Task_DoPokeballSendOutAnim** : 9 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE
- `pokeball.c` **SpriteCB_BallThrow_CaptureMon** : 1 différence(s) ; marqueurs de RF absents de la fusion : MUS_CAUGHT_INTRO
- `pokedex.c` **GetSetPokedexFlag** : 6 différence(s)
- `pokemon_size_record.c` **FormatMonSizeRecord** : 1 différence(s)
- `pokemon_size_record.c` **CompareMonSize** : 3 différence(s)
- `pokemon_size_record.c` **GetMonSizeRecordInfo** : 1 différence(s)
- `pokemon_size_record.c` **GiveGiftRibbonToParty** : 5 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_special_anim_scene.c` **SpriteCB_Star** : 17 différence(s)
- `pokemon_special_anim_scene.c` **DrawLevelUpWindowPg1** : 18 différence(s)
- `pokemon_special_anim_scene.c` **DrawLevelUpWindowPg2** : 17 différence(s)
- `pokemon_storage_system.c` **BackupPokemonStorage** : corps introuvable dans la fusion (déplacé ?)
- `pokemon_storage_system_graphics.c` **TryLoadMonIconTiles** : 6 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_summary_screen.c` **ShowSelectMovePokemonSummaryScreen** : 1 différence(s)
- `region_map.c` **HandleRegionMapInput** : 1 différence(s)
- `region_map.c` **GetMapNameGeneric** ✓ : 1 différence(s)
- `reset_save_heap.c` **ReloadSave** : 1 différence(s)
- `reshow_battle_screen.c` **ReshowBattleScreenAfterMenu** : 2 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_SAFARI
- `reshow_battle_screen.c` **LoadBattlerSpriteGfx** : 2 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_OLD_MAN_TUTORIAL
- `reshow_battle_screen.c` **CreateBattlerSprite** : 6 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_OLD_MAN_TUTORIAL
- `reshow_battle_screen.c` **CreateHealthboxSprite** : 2 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_OLD_MAN_TUTORIAL
- `roamer.c` **ClearRoamerData** : 10 différence(s) ; marqueurs de RF absents de la fusion : MAP_GRP, MAP_NUM
- `roamer.c` **CreateInitialRoamerMon** : 32 différence(s)
- `roamer.c` **InitRoamer** : 2 différence(s)
- `safari_zone.c` **EnterSafariMode** : 4 différence(s)
- `safari_zone.c` **ExitSafariMode** : 2 différence(s)
- `safari_zone.c` **SafariZoneTakeStep** : 2 différence(s)
- `safari_zone.c` **CB2_EndSafariBattle** : 3 différence(s)
- `save_failed_screen.c` **DoSaveFailedScreen** : 5 différence(s)
- `save_failed_screen.c` **VerifySectorWipe** : 8 différence(s)
- `save_failed_screen.c` **WipeSector** : 6 différence(s)
- `save_location.c` **IsCurMapInLocationList** : 3 différence(s) ; marqueurs de RF absents de la fusion : MAP_UNDEFINED
- `save_location.c` **TrySetPokeCenterWarpStatus** : 4 différence(s)
- `save_location.c` **TrySetReloadWarpStatus** : 2 différence(s)
- `save_location.c` **TrySetUnknownWarpStatus** : 2 différence(s)
- `save_location.c` **SetUnlockedPokedexFlags** : 3 différence(s)
- `script_movement.c` **ScriptMovement_UnfreezeObjectEvents** : 2 différence(s)
- `script_movement.c` **ScriptMovement_StartMoveObjects** : 3 différence(s)
- `script_movement.c` **GetMovementScriptIdFromObjectEventId** : 2 différence(s)
- `script_movement.c` **ScriptMovement_TakeStep** : 1 différence(s)
- `script_pokemon_util.c` **ScriptGiveMon** : 7 différence(s)
- `script_pokemon_util.c` **ScriptGiveEgg** : 8 différence(s)
- `script_pokemon_util.c` **CreateScriptedWildMon** : 1 différence(s)
- `script_pokemon_util.c` **ScriptSetMonMoveSlot** : 2 différence(s)
- `script_pokemon_util.c` **ChooseHalfPartyForBattle** : 1 différence(s)
- `special_field_anim.c` **SetEscalatorMetatile** : 32 différence(s)
- `special_field_anim.c` **Task_DrawEscalator** : 9 différence(s)
- `special_field_anim.c` **CreateEscalatorTask** : 3 différence(s)
- `special_field_anim.c` **StartEscalator** : 2 différence(s)
- `special_field_anim.c` **IsEscalatorMoving** : 3 différence(s)
- `start_menu.c` **ShowStartMenu** : 2 différence(s)
- `start_menu.c` **StartMenuPokedexCallback** : 2 différence(s)
- `start_menu.c` **StartMenuSaveCallback** : 2 différence(s)
- `start_menu.c` **StartMenuOptionCallback** : 1 différence(s)
- `start_menu.c` **StartMenuExitCallback** : 1 différence(s)
- `start_menu.c` **StartMenuSafariZoneRetireCallback** : 1 différence(s)
- `tileset_anims.c` **QueueAnimTiles_General_Flower** : 3 différence(s)
- `tileset_anims.c` **TilesetAnim_General** : 6 différence(s)
- `tileset_anims.c` **InitTilesetAnim_General** : 1 différence(s)
- `title_screen.c` **CB2_InitTitleScreen** : 52 différence(s)
- `title_screen.c` **VBlankCB** : 1 différence(s)
- `tm_case.c` **PrintTitle** : 2 différence(s)
- `trade.c` **CB2_CreateTradeMenu** : 29 différence(s) ; marqueurs de RF absents de la fusion : MUS_GAME_CORNER
- `trainer_fan_club.c` **BufferFanClubTrainerName** : 2 différence(s)
- `trainer_pokemon_sprites.c` **DecompressPic** : 4 différence(s)
- `trainer_pokemon_sprites.c` **LoadPicPaletteBySlot** : 2 différence(s)
- `trainer_pokemon_sprites.c` **CreatePicSprite** : 8 différence(s)
- `trainer_pokemon_sprites.c` **CreateTrainerCardSprite** : 6 différence(s)
- `trainer_pokemon_sprites.c` **PlayerGenderToFrontTrainerPicId** : 2 différence(s)
- `trainer_tower.c` **GetOwnerState** : 8 différence(s)
- `trainer_tower.c` **GiveChallengePrize** : 4 différence(s)
- `trainer_tower.c` **CheckFinalTime** : 12 différence(s)
- `union_room.c` **Task_RunUnionRoom** : 30 différence(s) ; marqueurs de RF absents de la fusion : SE_NOTE_C
- `wonder_news.c` **WonderNews_GetRewardInfo** : 1 différence(s)
- `wonder_news.c` **GetRewardType** : 2 différence(s)
