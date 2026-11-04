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
| party_menu.c | 145 | 36 | 0 | 0 | 109 | 0 |
| scrcmd.c | 68 | 9 | 0 | 0 | 59 | 0 |
| field_effect_helpers.c | 60 | 7 | 0 | 0 | 53 | 0 |
| trainer_card.c | 52 | 2 | 0 | 0 | 50 | 0 |
| pokemon.c | 62 | 23 | 0 | 0 | 39 | 0 |
| field_player_avatar.c | 64 | 26 | 0 | 0 | 38 | 0 |
| fieldmap.c | 34 | 3 | 0 | 0 | 31 | 0 |
| naming_screen.c | 37 | 8 | 0 | 0 | 29 | 0 |
| daycare.c | 35 | 10 | 0 | 0 | 24 | 1 |
| field_control_avatar.c | 25 | 2 | 0 | 0 | 23 | 0 |
| shop.c | 39 | 18 | 0 | 0 | 21 | 0 |
| metatile_behavior.c | 23 | 3 | 0 | 0 | 20 | 0 |
| field_weather_effects.c | 38 | 19 | 0 | 0 | 19 | 0 |
| field_specials.c | 20 | 2 | 0 | 0 | 18 | 0 |
| battle_controller_oak_old_man.c | 26 | 9 | 0 | 0 | 17 | 0 |
| battle_controllers.c | 16 | 3 | 0 | 0 | 13 | 0 |
| item.c | 20 | 7 | 0 | 0 | 12 | 1 |
| bike.c | 12 | 1 | 0 | 0 | 11 | 0 |
| event_data.c | 16 | 5 | 0 | 0 | 11 | 0 |
| field_door.c | 16 | 5 | 0 | 0 | 11 | 0 |
| field_fadetransition.c | 24 | 13 | 0 | 0 | 11 | 0 |
| wild_encounter.c | 12 | 1 | 0 | 0 | 11 | 0 |
| hall_of_fame.c | 23 | 13 | 0 | 0 | 10 | 0 |
| item_use.c | 14 | 4 | 0 | 0 | 10 | 0 |
| battle_main.c | 56 | 5 | 42 | 0 | 9 | 0 |
| ereader_helpers.c | 9 | 0 | 0 | 0 | 9 | 0 |
| menu_helpers.c | 9 | 0 | 0 | 0 | 9 | 0 |
| pokemon_icon.c | 10 | 1 | 0 | 0 | 9 | 0 |
| script.c | 13 | 4 | 0 | 0 | 9 | 0 |
| battle_script_commands.c | 116 | 39 | 69 | 0 | 8 | 0 |
| berry.c | 8 | 0 | 0 | 0 | 8 | 0 |
| berry_powder.c | 9 | 1 | 0 | 0 | 8 | 0 |
| field_camera.c | 10 | 2 | 0 | 0 | 8 | 0 |
| item_menu.c | 13 | 5 | 0 | 0 | 8 | 0 |
| ereader_screen.c | 7 | 0 | 0 | 0 | 7 | 0 |
| evolution_scene.c | 9 | 2 | 0 | 0 | 7 | 0 |
| field_weather.c | 15 | 8 | 0 | 0 | 7 | 0 |
| script_menu.c | 8 | 1 | 0 | 0 | 7 | 0 |
| string_util.c | 23 | 8 | 8 | 0 | 7 | 0 |
| trainer_see.c | 9 | 2 | 0 | 0 | 7 | 0 |
| evolution_graphics.c | 8 | 2 | 0 | 0 | 6 | 0 |
| field_tasks.c | 6 | 0 | 0 | 0 | 6 | 0 |
| new_game.c | 6 | 0 | 0 | 0 | 6 | 0 |
| start_menu.c | 10 | 4 | 0 | 0 | 6 | 0 |
| battle_controller_opponent.c | 34 | 5 | 24 | 0 | 5 | 0 |
| field_message_box.c | 8 | 3 | 0 | 0 | 5 | 0 |
| field_poison.c | 5 | 0 | 0 | 0 | 5 | 0 |
| minigame_countdown.c | 6 | 1 | 0 | 0 | 5 | 0 |
| mon_markings.c | 5 | 0 | 0 | 0 | 5 | 0 |
| party_menu_specials.c | 5 | 0 | 0 | 0 | 5 | 0 |
| save_location.c | 5 | 0 | 0 | 0 | 5 | 0 |
| script_pokemon_util.c | 5 | 0 | 0 | 0 | 5 | 0 |
| special_field_anim.c | 6 | 1 | 0 | 0 | 5 | 0 |
| trainer_pokemon_sprites.c | 6 | 1 | 0 | 0 | 5 | 0 |
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
| title_screen.c | 3 | 0 | 0 | 0 | 3 | 0 |
| trainer_tower.c | 3 | 0 | 0 | 0 | 3 | 0 |
| battle_ai_script_commands.c | 88 | 3 | 81 | 0 | 2 | 2 |
| battle_bg.c | 10 | 1 | 7 | 0 | 2 | 0 |
| battle_controller_player.c | 69 | 16 | 50 | 0 | 2 | 1 |
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
| wonder_news.c | 2 | 0 | 0 | 0 | 2 | 0 |
| battle_controller_pokedude.c | 30 | 29 | 0 | 0 | 1 | 0 |
| battle_controller_safari.c | 12 | 5 | 6 | 0 | 1 | 0 |
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
| battle_controller_link_opponent.c | 20 | 4 | 16 | 0 | 0 | 0 |
| battle_controller_link_partner.c | 20 | 4 | 16 | 0 | 0 | 0 |
| battle_gfx_sfx_util.c | 29 | 9 | 20 | 0 | 0 | 0 |
| battle_intro.c | 8 | 2 | 6 | 0 | 0 | 0 |
| battle_tower.c | 12 | 0 | 12 | 0 | 0 | 0 |
| battle_transition.c | 77 | 11 | 66 | 0 | 0 | 0 |
| berry_fix_program.c | 3 | 0 | 3 | 0 | 0 | 0 |
| bg.c | 42 | 4 | 38 | 0 | 0 | 0 |
| blend_palette.c | 1 | 0 | 1 | 0 | 0 | 0 |
| blit.c | 1 | 0 | 1 | 0 | 0 | 0 |
| decompress.c | 8 | 1 | 7 | 0 | 0 | 0 |
| diploma.c | 1 | 1 | 0 | 0 | 0 | 0 |
| dma3_manager.c | 4 | 1 | 3 | 0 | 0 | 0 |
| dynamic_placeholder_text_util.c | 3 | 3 | 0 | 0 | 0 | 0 |
| event_object_lock.c | 5 | 5 | 0 | 0 | 0 | 0 |
| event_object_movement.c | 378 | 301 | 0 | 77 | 0 | 0 |
| field_effect.c | 94 | 34 | 0 | 60 | 0 | 0 |
| isagbprn.c | 7 | 0 | 7 | 0 | 0 | 0 |
| item_menu_icons.c | 8 | 8 | 0 | 0 | 0 | 0 |
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
| menu_indicators.c | 15 | 1 | 14 | 0 | 0 | 0 |
| multiboot.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_event_script.c | 21 | 14 | 7 | 0 | 0 | 0 |
| mystery_gift.c | 16 | 3 | 13 | 0 | 0 | 0 |
| mystery_gift_client.c | 3 | 1 | 2 | 0 | 0 | 0 |
| mystery_gift_menu.c | 15 | 7 | 8 | 0 | 0 | 0 |
| mystery_gift_server.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_gift_show_card.c | 6 | 0 | 6 | 0 | 0 | 0 |
| mystery_gift_show_news.c | 7 | 4 | 3 | 0 | 0 | 0 |
| new_menu_helpers.c | 24 | 10 | 14 | 0 | 0 | 0 |
| overworld.c | 92 | 27 | 0 | 65 | 0 | 0 |
| palette.c | 23 | 7 | 14 | 0 | 0 | 2 |
| play_time.c | 1 | 0 | 1 | 0 | 0 | 0 |
| pokemon_jump.c | 26 | 8 | 18 | 0 | 0 | 0 |
| pokemon_special_anim.c | 1 | 1 | 0 | 0 | 0 | 0 |
| pokemon_storage_system.c | 1 | 0 | 0 | 0 | 0 | 1 |
| pokemon_storage_system_data.c | 49 | 24 | 25 | 0 | 0 | 0 |
| pokemon_storage_system_menu.c | 13 | 9 | 4 | 0 | 0 | 0 |
| pokemon_storage_system_misc.c | 39 | 11 | 28 | 0 | 0 | 0 |
| pokemon_storage_system_tasks.c | 71 | 32 | 39 | 0 | 0 | 0 |
| random.c | 2 | 0 | 2 | 0 | 0 | 0 |
| save.c | 26 | 11 | 15 | 0 | 0 | 0 |
| scanline_effect.c | 3 | 0 | 3 | 0 | 0 | 0 |
| slot_machine.c | 2 | 2 | 0 | 0 | 0 | 0 |
| sound.c | 4 | 0 | 4 | 0 | 0 | 0 |
| sprite.c | 20 | 9 | 11 | 0 | 0 | 0 |
| task.c | 4 | 0 | 4 | 0 | 0 | 0 |
| text.c | 17 | 2 | 15 | 0 | 0 | 0 |
| text_printer.c | 8 | 2 | 6 | 0 | 0 | 0 |
| text_window.c | 2 | 2 | 0 | 0 | 0 | 0 |
| tilemap_util.c | 9 | 0 | 9 | 0 | 0 | 0 |
| trade_scene.c | 32 | 7 | 25 | 0 | 0 | 0 |
| union_room_battle.c | 1 | 0 | 1 | 0 | 0 | 0 |
| union_room_chat.c | 15 | 2 | 13 | 0 | 0 | 0 |
| union_room_chat_display.c | 8 | 2 | 6 | 0 | 0 | 0 |
| union_room_chat_objects.c | 1 | 1 | 0 | 0 | 0 | 0 |
| union_room_player_avatar.c | 18 | 8 | 10 | 0 | 0 | 0 |
| util.c | 4 | 2 | 2 | 0 | 0 | 0 |
| vs_seeker.c | 3 | 3 | 0 | 0 | 0 | 0 |
| window.c | 8 | 1 | 7 | 0 | 0 | 0 |
| window_8bpp.c | 3 | 3 | 0 | 0 | 0 | 0 |
| wireless_communication_status_screen.c | 7 | 0 | 7 | 0 | 0 | 0 |
| **total** | 4254 | 1335 | 1707 | 202 | 1001 | 9 |

## À lire

- `battle_ai_script_commands.c` **BattleAI_HandleItemUseBeforeAISetup** : 14 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_ai_script_commands.c` **BattleAI_SetupAIData** : 36 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_LEGENDARY_FRLG, BATTLE_TYPE_TRAINER_TOWER
- `battle_ai_script_commands.c` **Cmd_if_equal_** : corps introuvable dans la fusion (déplacé ?)
- `battle_ai_script_commands.c` **Cmd_if_not_equal_** : corps introuvable dans la fusion (déplacé ?)
- `battle_ai_switch_items.c` **GetAI_ItemType** : corps introuvable dans la fusion (déplacé ?)
- `battle_bg.c` **LoadBattleMenuWindowGfx** : 15 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_POKEDUDE
- `battle_bg.c` **DrawBattleEntryBackground** ✓ : 11 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER, TRAINER_CLASS_CHAMPION, TRAINER_CLASS_LEADER
- `battle_controller_oak_old_man.c` **HandleInputChooseAction** : 2 différence(s) ; marqueurs de RF absents de la fusion : ITEM_PREMIER_BALL, SE_SELECT
- `battle_controller_oak_old_man.c` **CompleteOnBattlerSpriteCallbackDummy** : 1 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnInactiveTextPrinter** : 1 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnSpecialAnimDone** : 1 différence(s)
- `battle_controller_oak_old_man.c` **OpenPartyMenuToChooseMon** : 4 différence(s)
- `battle_controller_oak_old_man.c` **WaitForMonSelection** : 1 différence(s)
- `battle_controller_oak_old_man.c` **OpenBagAndChooseItem** : 6 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_oak_old_man.c` **CompleteWhenChoseItem** : 2 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, ITEM_POTION
- `battle_controller_oak_old_man.c` **Intro_WaitForShinyAnimAndHealthbox** : 1 différence(s)
- `battle_controller_oak_old_man.c` **FreeMonSpriteAfterFaintAnim** : 3 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnHealthbarDone** : 1 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnInactiveTextPrinter2** : 1 différence(s)
- `battle_controller_oak_old_man.c` **DoHitAnimBlinkSpriteEffect** : 1 différence(s)
- `battle_controller_oak_old_man.c` **DoSwitchOutAnimation** : 1 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnFinishedBattleAnimation** : 1 différence(s)
- `battle_controller_oak_old_man.c` **CompleteOnFinishedStatusAnimation** : 1 différence(s)
- `battle_controller_oak_old_man.c` **HandleChooseActionAfterDma3** : 2 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_opponent.c` **CompleteOnHealthbarDone** : 5 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_opponent.c` **OpponentHandleLoadMonSprite** : 4 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST
- `battle_controller_opponent.c` **OpponentHandleDrawTrainerPic** : 10 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_controller_opponent.c` **OpponentHandleTrainerSlide** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_controller_opponent.c` **OpponentHandlePrintString** : 3 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_player.c` **HandleInputChooseAction** : 2 différence(s) ; marqueurs de RF absents de la fusion : ITEM_PREMIER_BALL, SE_SELECT
- `battle_controller_player.c` **HandleMoveSwitching** : 21 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE
- `battle_controller_player.c` **MoveSelectionDisplayPpNumber** : corps introuvable dans la fusion (déplacé ?)
- `battle_controller_pokedude.c` **OpenBagAndChooseItem** : 2 différence(s)
- `battle_controller_safari.c` **HandleInputChooseAction** : 2 différence(s) ; marqueurs de RF absents de la fusion : SE_SELECT
- `battle_controllers.c` **InitBattleControllers** : 2 différence(s)
- `battle_controllers.c` **InitSinglePlayerBtlControllers** : 33 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_controllers.c` **InitLinkBtlControllers** : 1 différence(s)
- `battle_controllers.c` **SetBattlePartyIds** : 3 différence(s)
- `battle_controllers.c` **PrepareBufferDataTransferLink** : 20 différence(s)
- `battle_controllers.c` **Task_HandleSendLinkBuffersData** : 23 différence(s)
- `battle_controllers.c` **TryReceiveLinkBattleData** : 2 différence(s)
- `battle_controllers.c` **Task_HandleCopyReceivedLinkBuffersData** : 26 différence(s)
- `battle_controllers.c` **BtlController_EmitMoveAnimation** : 1 différence(s)
- `battle_controllers.c` **BtlController_EmitPrintString** : 1 différence(s)
- `battle_controllers.c` **BtlController_EmitPrintSelectionString** : 1 différence(s)
- `battle_controllers.c` **BtlController_EmitLinkStandbyMsg** : 4 différence(s)
- `battle_controllers.c` **BtlController_EmitEndLinkBattle** : 2 différence(s)
- `battle_interface.c` **TryAddPokeballIconToHealthbox** : 5 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_main.c` **CB2_InitBattle** : 4 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_SAFARI
- `battle_main.c` **BattleMainCB2** : 1 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE
- `battle_main.c` **CreateNPCTrainerParty** : 9 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_main.c` **BattleStartClearSetData** : 17 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, SPECIES_NONE
- `battle_main.c` **BattleIntroDrawTrainersOrMonsSprites** : 16 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_GHOST_UNVEILED, BATTLE_TYPE_LEGENDARY, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_main.c` **BattleIntroRecordMonsToDex** : 4 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_LEGENDARY, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_main.c` **HandleEndTurn_BattleWon** : 14 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER, TRAINER_CLASS_COOLTRAINER, TRAINER_CLASS_DOME_ACE, TRAINER_CLASS_GENTLEMAN, TRAINER_CLASS_SALON_MAIDEN
- `battle_main.c` **HandleEndTurn_FinishBattle** : 14 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_TRAINER_TOWER
- `battle_main.c` **HandleAction_UseItem** : 8 différence(s) ; marqueurs de RF absents de la fusion : ITEM_PREMIER_BALL
- `battle_message.c` **BufferStringBattle** : 42 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_GHOST_UNVEILED, BATTLE_TYPE_OLD_MAN_TUTORIAL
- `battle_message.c` **BattleStringExpandPlaceholders** : 73 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER, FLAG_SYS_NOT_SOMEONES_PC, TRAINER_CLASS_CHAMPION, TRAINER_CLASS_FACTORY_HEAD, TRAINER_CLASS_RIVAL_EARLY
- `battle_records.c` **UpdatePlayerLinkBattleRecords** : 8 différence(s) ; marqueurs de RF absents de la fusion : MAP_GROUP, MAP_NUM, MAP_UNION_ROOM
- `battle_script_commands.c` **Cmd_accuracycheck** : 6 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_FIRST_BATTLE, BATTLE_TYPE_POKEDUDE
- `battle_script_commands.c` **Cmd_critcalc** : 3 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_script_commands.c` **SetMoveEffect** : 22 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `battle_script_commands.c` **Cmd_getexp** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `battle_script_commands.c` **Cmd_switchinanim** : 4 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_LEGENDARY, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_script_commands.c` **Cmd_tryswapitems** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_TRAINER_TOWER
- `battle_script_commands.c` **Cmd_handleballthrow** : 15 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_GHOST, BATTLE_TYPE_OLD_MAN_TUTORIAL, BATTLE_TYPE_POKEDUDE
- `battle_script_commands.c` **Cmd_givecaughtmon** : 16 différence(s) ; marqueurs de RF absents de la fusion : FLAG_SYS_NOT_SOMEONES_PC
- `battle_setup.c` **StartGroudonKyogreBattle** : 5 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_TRAINER
- `battle_setup.c` **StartRegiBattle** : 5 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_TRAINER
- `battle_util.c` **IsMonDisobedient** : 16 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, FLAG_BADGE02_GET, FLAG_BADGE04_GET, FLAG_BADGE06_GET, FLAG_BADGE08_GET
- `battle_util2.c` **AllocateBattleResources** : 8 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `battle_util2.c` **FreeBattleResources** : 3 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE, BATTLE_TYPE_TRAINER_TOWER
- `berry.c` **ClearEnigmaBerries** : 1 différence(s)
- `berry.c` **SetEnigmaBerry** : 9 différence(s)
- `berry.c` **GetEnigmaBerryChecksum** : 8 différence(s)
- `berry.c` **IsEnigmaBerryValid** : 4 différence(s)
- `berry.c` **GetBerryInfo** : 5 différence(s)
- `berry.c` **ItemIdToBerryType** : 5 différence(s) ; marqueurs de RF absents de la fusion : ITEM_ENIGMA_BERRY
- `berry.c` **BerryTypeToItemId** : 4 différence(s) ; marqueurs de RF absents de la fusion : ITEM_ENIGMA_BERRY
- `berry.c` **GetBerryNameByBerryType** : 2 différence(s)
- `berry_crush.c` **Cmd_SignalReadyToBegin** : 3 différence(s) ; marqueurs de RF absents de la fusion : MUS_GAME_CORNER
- `berry_powder.c` **ApplyNewEncryptionKeyToBerryPowder** : 2 différence(s)
- `berry_powder.c` **HasEnoughBerryPowder** : 3 différence(s)
- `berry_powder.c` **TakeBerryPowder** : 6 différence(s)
- `berry_powder.c` **GetBerryPowder** : 2 différence(s)
- `berry_powder.c` **PrintBerryPowderAmount** : 1 différence(s)
- `berry_powder.c` **DrawPlayerPowderAmount** : 5 différence(s)
- `berry_powder.c` **PrintPlayerBerryPowderAmount** : 4 différence(s)
- `berry_powder.c` **DisplayBerryPowderVendorMenu** : 8 différence(s)
- `bike.c` **MovePlayerOnBike** : 5 différence(s)
- `bike.c` **GetBikeCollision** : 7 différence(s)
- `bike.c` **GetBikeCollisionAt** : 4 différence(s)
- `bike.c` **RS_IsRunningDisallowed** : 3 différence(s)
- `bike.c` **IsRunningDisallowed** : 4 différence(s)
- `bike.c` **IsBikingDisallowedByPlayer** : 2 différence(s)
- `bike.c` **IsPlayerNotUsingAcroBikeOnBumpySlope** : 2 différence(s)
- `bike.c` **GetOnOffBike** : 5 différence(s)
- `bike.c` **BikeClearState** : 6 différence(s)
- `bike.c` **Bike_UpdateBikeCounterSpeed** : 1 différence(s)
- `bike.c` **GetPlayerSpeed** : 4 différence(s)
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
- `daycare.c` **Daycare_FindEmptySpot** : 1 différence(s)
- `daycare.c` **StorePokemonInDaycare** : 2 différence(s)
- `daycare.c` **GetDaycareCostForSelectedMon** : corps introuvable dans la fusion (déplacé ?)
- `daycare.c` **Debug_AddDaycareSteps** : 1 différence(s)
- `daycare.c` **ClearDaycareMonMail** : 1 différence(s)
- `daycare.c` **_TriggerPendingDaycareEgg** : 4 différence(s)
- `daycare.c` **InheritIVs** : 8 différence(s)
- `daycare.c` **_GiveEggFromDaycare** : 1 différence(s)
- `daycare.c` **CreateEgg** : 3 différence(s)
- `daycare.c` **SetInitialEggData** : 1 différence(s)
- `daycare.c` **TryProduceOrHatchEgg** : 6 différence(s)
- `daycare.c` **ShouldEggHatch** : 2 différence(s)
- `daycare.c` **_GetDaycareMonNicknames** : 4 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `daycare.c` **GetDaycareLevelMenuText** : 2 différence(s)
- `daycare.c` **DaycareAddTextPrinter** : 2 différence(s)
- `daycare.c` **DaycarePrintMonNickname** : 1 différence(s)
- `daycare.c` **DaycarePrintMonLvl** : 3 différence(s)
- `daycare.c` **Task_HandleDaycareLevelMenuInput** : 4 différence(s)
- `daycare.c` **AddHatchedMonToParty** : 4 différence(s)
- `daycare.c` **EggHatchCreateMonSprite** : 5 différence(s)
- `daycare.c` **EggHatch** : 3 différence(s)
- `daycare.c` **EggHatchSetMonNickname** : 1 différence(s)
- `daycare.c` **Task_EggHatchPlayBGM** : 1 différence(s)
- `daycare.c` **CreateRandomEggShardSprite** : 3 différence(s)
- `daycare.c` **EggHatchPrintMessage** : 4 différence(s)
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
- `ereader_helpers.c` **EReader_Send** : 10 différence(s)
- `ereader_helpers.c` **EReader_Recv** : 10 différence(s)
- `ereader_helpers.c` **OpenSerial32** : 2 différence(s)
- `ereader_helpers.c` **EReaderHandleTransfer** : 5 différence(s)
- `ereader_helpers.c` **DetermineSendRecvState** : 2 différence(s)
- `ereader_helpers.c` **SetUpTransferManager** : 4 différence(s)
- `ereader_helpers.c` **EReaderHelper_SerialCallback** : 24 différence(s)
- `ereader_helpers.c` **DisableTm3** : 1 différence(s)
- `ereader_helpers.c` **GetKeyInput** : 1 différence(s)
- `ereader_screen.c` **EReader_Load** : 1 différence(s)
- `ereader_screen.c` **EReader_Reset** : 1 différence(s)
- `ereader_screen.c` **OpenEReaderLink** : 1 différence(s)
- `ereader_screen.c` **ValidateEReaderConnection** : 3 différence(s)
- `ereader_screen.c` **TryReceiveCard** : 7 différence(s)
- `ereader_screen.c` **CreateEReaderTask** : 2 différence(s)
- `ereader_screen.c` **Task_EReader** : 8 différence(s)
- `event_data.c` **ClearTempFieldEventData** : 7 différence(s)
- `event_data.c` **EnableNationalPokedex** : 3 différence(s)
- `event_data.c` **IsNationalPokedexEnabled** : 3 différence(s)
- `event_data.c` **ClearMysteryGiftVars** : 1 différence(s) ; marqueurs de RF absents de la fusion : VAR_ALTERING_CAVE_WILD_SET
- `event_data.c` **CanResetRTC** : 5 différence(s)
- `event_data.c` **GetVarPointer** : 4 différence(s)
- `event_data.c` **VarGet** : 2 différence(s)
- `event_data.c` **VarSet** : 2 différence(s)
- `event_data.c` **FlagSet** : 1 différence(s)
- `event_data.c` **FlagClear** : 1 différence(s)
- `event_data.c` **FlagGet** : 5 différence(s)
- `evolution_graphics.c` **SetEvoSparklesMatrices** : 2 différence(s)
- `evolution_graphics.c` **LoadEvoSparkleSpriteAndPal** : 1 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_ArcDown** : 2 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_CircleInward** : 2 différence(s)
- `evolution_graphics.c` **EvolutionSparkles_SprayAndFlash_Trade** : 1 différence(s)
- `evolution_graphics.c` **CycleEvolutionMonSprite** : 13 différence(s)
- `evolution_scene.c` **EvolutionScene** : 6 différence(s)
- `evolution_scene.c` **CB2_EvolutionSceneLoadGraphics** : 2 différence(s)
- `evolution_scene.c` **CB2_TradeEvolutionSceneLoadGraphics** : 2 différence(s)
- `evolution_scene.c` **TradeEvolutionScene** : 3 différence(s)
- `evolution_scene.c` **Task_EvolutionScene** : 25 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_MEW
- `evolution_scene.c` **Task_TradeEvolutionScene** : 13 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_MEW
- `evolution_scene.c` **StartBgAnimation** : 3 différence(s)
- `field_camera.c` **DrawWholeMapView** : 1 différence(s)
- `field_camera.c` **CurrentMapDrawMetatileAt** : 1 différence(s)
- `field_camera.c` **DrawDoorMetatileAt** : 1 différence(s)
- `field_camera.c` **DrawMetatileAt** : 2 différence(s)
- `field_camera.c` **DrawMetatile** : 3 différence(s)
- `field_camera.c` **CameraUpdateCallback** : 2 différence(s)
- `field_camera.c` **CameraUpdate** : 5 différence(s)
- `field_camera.c` **SetCameraPanningCallback** : 1 différence(s)
- `field_control_avatar.c` **FieldClearPlayerInput** : 1 différence(s)
- `field_control_avatar.c` **FieldGetPlayerInput** : 7 différence(s)
- `field_control_avatar.c` **ProcessPlayerFieldInput** : 15 différence(s) ; marqueurs de RF absents de la fusion : FLAG_OPENED_START_MENU
- `field_control_avatar.c` **GetInFrontOfPlayerPosition** : 2 différence(s)
- `field_control_avatar.c` **TryStartInteractionScript** : 1 différence(s)
- `field_control_avatar.c` **GetInteractedObjectEventScript** : 2 différence(s)
- `field_control_avatar.c` **GetInteractedBackgroundEventScript** : 13 différence(s)
- `field_control_avatar.c` **GetInteractedMetatileScript** : 18 différence(s)
- `field_control_avatar.c` **GetInteractedWaterScript** : 5 différence(s) ; marqueurs de RF absents de la fusion : FLAG_BADGE05_GET, FLAG_BADGE07_GET
- `field_control_avatar.c` **TryStartStepBasedScript** : 1 différence(s)
- `field_control_avatar.c` **TryStartMiscWalkingScripts** : 2 différence(s)
- `field_control_avatar.c` **TryStartStepCountScript** : 8 différence(s)
- `field_control_avatar.c` **UpdatePoisonStepCounter** : 1 différence(s)
- `field_control_avatar.c` **RestartWildEncounterImmunitySteps** : 1 différence(s)
- `field_control_avatar.c` **CheckStandardWildEncounter** : 5 différence(s)
- `field_control_avatar.c` **TryArrowWarp** : 3 différence(s)
- `field_control_avatar.c` **TryStartWarpEventScript** : 4 différence(s)
- `field_control_avatar.c` **IsWarpMetatileBehavior** : 21 différence(s)
- `field_control_avatar.c` **SetupWarp** : 1 différence(s)
- `field_control_avatar.c` **TryDoorWarp** : 2 différence(s)
- `field_control_avatar.c` **GetWarpEventAtPosition** : 2 différence(s)
- `field_control_avatar.c` **GetCoordEventScriptAtPosition** : 1 différence(s)
- `field_control_avatar.c` **GetBackgroundEventAtPosition** : 1 différence(s)
- `field_door.c` **DrawDoor** : 1 différence(s)
- `field_door.c` **DrawClosedDoorTiles** : 1 différence(s)
- `field_door.c` **CopyDoorTilesToVram** : 2 différence(s)
- `field_door.c` **DrawCurrentDoorAnimFrame** : 2 différence(s)
- `field_door.c` **Task_AnimateDoor** : 7 différence(s)
- `field_door.c` **StartDoorAnimationTask** : 4 différence(s)
- `field_door.c` **FieldSetDoorOpened** ✓ : 1 différence(s)
- `field_door.c` **FieldSetDoorClosed** ✓ : 1 différence(s)
- `field_door.c` **FieldAnimateDoorClose** ✓ : 1 différence(s)
- `field_door.c` **FieldAnimateDoorOpen** ✓ : 1 différence(s)
- `field_door.c` **GetDoorSoundEffect** ✓ : 1 différence(s) ; marqueurs de RF absents de la fusion : SE_DOOR
- `field_effect_helpers.c` **LoadObjectReflectionPalette** : 3 différence(s)
- `field_effect_helpers.c` **LoadObjectRegularReflectionPalette** : 1 différence(s)
- `field_effect_helpers.c` **LoadObjectHighBridgeReflectionPalette** : 1 différence(s)
- `field_effect_helpers.c` **UpdateObjectReflectionSprite** : 3 différence(s)
- `field_effect_helpers.c` **CreateWarpArrowSprite** : 3 différence(s)
- `field_effect_helpers.c` **ShowWarpArrowSprite** : 9 différence(s)
- `field_effect_helpers.c` **FldEff_Shadow** : 6 différence(s)
- `field_effect_helpers.c` **UpdateShadowFieldEffect** : 6 différence(s)
- `field_effect_helpers.c` **FldEff_TallGrass** : 5 différence(s)
- `field_effect_helpers.c` **UpdateTallGrassFieldEffect** : 9 différence(s)
- `field_effect_helpers.c` **FldEff_JumpTallGrass** : 2 différence(s)
- `field_effect_helpers.c` **FindTallGrassFieldEffectSpriteId** : 8 différence(s)
- `field_effect_helpers.c` **FldEff_LongGrass** : 5 différence(s)
- `field_effect_helpers.c` **UpdateLongGrassFieldEffect** : 9 différence(s)
- `field_effect_helpers.c` **FldEff_JumpLongGrass** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_ShortGrass** : 7 différence(s)
- `field_effect_helpers.c` **UpdateShortGrassFieldEffect** : 12 différence(s)
- `field_effect_helpers.c` **FldEff_SandFootprints** : 3 différence(s)
- `field_effect_helpers.c` **FldEff_DeepSandFootprints** : 3 différence(s)
- `field_effect_helpers.c` **FldEff_BikeTireTracks** : 3 différence(s)
- `field_effect_helpers.c` **UpdateFootprintsTireTracksFieldEffect** : 1 différence(s)
- `field_effect_helpers.c` **FadeFootprintsTireTracks_Step0** : 2 différence(s)
- `field_effect_helpers.c` **FadeFootprintsTireTracks_Step1** : 3 différence(s)
- `field_effect_helpers.c` **FldEff_Splash** : 8 différence(s)
- `field_effect_helpers.c` **UpdateSplashFieldEffect** : 3 différence(s)
- `field_effect_helpers.c` **FldEff_JumpSmallSplash** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_JumpBigSplash** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_FeetInFlowingWater** : 8 différence(s)
- `field_effect_helpers.c` **UpdateFeetInFlowingWaterFieldEffect** : 6 différence(s)
- `field_effect_helpers.c` **FldEff_Ripple** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_HotSpringsWater** : 7 différence(s)
- `field_effect_helpers.c` **UpdateHotSpringsWaterFieldEffect** : 6 différence(s)
- `field_effect_helpers.c` **FldEff_UnusedGrass** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_UnusedGrass2** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_UnusedSand** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_Ash** : 5 différence(s)
- `field_effect_helpers.c` **UpdateAshFieldEffect** : 1 différence(s)
- `field_effect_helpers.c` **FldEff_SurfBlob** : 5 différence(s)
- `field_effect_helpers.c` **UpdateSurfBlobFieldEffect** : 6 différence(s)
- `field_effect_helpers.c` **StartUnderwaterSurfBlobBobbing** : 2 différence(s)
- `field_effect_helpers.c` **SpriteCB_UnderwaterSurfBlob** : 3 différence(s)
- `field_effect_helpers.c` **FldEff_Dust** : 2 différence(s)
- `field_effect_helpers.c` **FldEff_SandPile** : 8 différence(s)
- `field_effect_helpers.c` **UpdateSandPileFieldEffect** : 10 différence(s)
- `field_effect_helpers.c` **FldEff_Bubbles** : 2 différence(s)
- `field_effect_helpers.c` **UpdateBubblesFieldEffect** : 1 différence(s)
- `field_effect_helpers.c` **FldEff_BerryTreeGrowthSparkle** : 1 différence(s)
- `field_effect_helpers.c` **ShowDisguiseFieldEffect** : 2 différence(s)
- `field_effect_helpers.c` **UpdateDisguiseFieldEffect** : 4 différence(s)
- `field_effect_helpers.c` **StartRevealDisguise** : 1 différence(s)
- `field_effect_helpers.c` **UpdateRevealDisguise** : 1 différence(s)
- `field_effect_helpers.c` **UpdateSparkleFieldEffect** : 3 différence(s)
- `field_effect_helpers.c` **UpdateGrassFieldEffectSubpriority** : 7 différence(s)
- `field_fadetransition.c` **WarpFadeInScreen** : 4 différence(s)
- `field_fadetransition.c` **FadeInFromBlack** : 1 différence(s)
- `field_fadetransition.c` **WarpFadeOutScreen** : 5 différence(s)
- `field_fadetransition.c` **Task_ReturnToFieldRecordMixing** : 4 différence(s)
- `field_fadetransition.c` **FieldCB_ReturnToFieldWirelessLink** : 1 différence(s)
- `field_fadetransition.c` **SetUpWarpExitTask** : 3 différence(s)
- `field_fadetransition.c` **FieldCB_DefaultWarpExit** : 2 différence(s)
- `field_fadetransition.c` **FieldCB_WarpExitFadeFromBlack** : 3 différence(s)
- `field_fadetransition.c` **Task_ExitDoor** : 14 différence(s)
- `field_fadetransition.c` **Task_ExitNonAnimDoor** : 6 différence(s)
- `field_fadetransition.c` **Task_TeleportWarpIn** : 5 différence(s)
- `field_message_box.c` **InitFieldMessageBox** : 1 différence(s)
- `field_message_box.c` **ShowFieldMessage** : 1 différence(s)
- `field_message_box.c` **ShowFieldAutoScrollMessage** : 1 différence(s)
- `field_message_box.c` **ForceShowFieldAutoScrollMessage** : 1 différence(s)
- `field_message_box.c` **IsFieldMessageBoxHidden** : 1 différence(s)
- `field_player_avatar.c` **TryInterruptObjectEventSpecialAnim** : 5 différence(s)
- `field_player_avatar.c` **MovePlayerAvatarUsingKeypadInput** : 3 différence(s)
- `field_player_avatar.c` **TryDoMetatileBehaviorForcedMovement** : 7 différence(s)
- `field_player_avatar.c` **DoForcedMovement** : 2 différence(s)
- `field_player_avatar.c` **DoForcedMovementInCurrentDirection** : 1 différence(s)
- `field_player_avatar.c` **ForcedMovement_Slide** : 1 différence(s)
- `field_player_avatar.c` **CheckMovementInputNotOnBike** : 6 différence(s)
- `field_player_avatar.c` **PlayerNotOnBikeMoving** : 9 différence(s)
- `field_player_avatar.c` **CheckForPlayerAvatarCollision** : 1 différence(s)
- `field_player_avatar.c` **CheckForObjectEventCollision** : 2 différence(s)
- `field_player_avatar.c` **CanStopSurfing** : 3 différence(s)
- `field_player_avatar.c` **TryPushBoulder** : 11 différence(s)
- `field_player_avatar.c` **CheckAcroBikeCollision** : 1 différence(s)
- `field_player_avatar.c` **SetPlayerAvatarTransitionFlags** : 1 différence(s)
- `field_player_avatar.c` **PlayerAvatarTransition_Normal** : 3 différence(s)
- `field_player_avatar.c` **PlayerAvatarTransition_Surfing** : 3 différence(s)
- `field_player_avatar.c` **PlayerAvatarTransition_Underwater** : 1 différence(s)
- `field_player_avatar.c` **PlayerAnimIsMultiFrameStationary** : 9 différence(s)
- `field_player_avatar.c` **PlayerSetAnimId** : 2 différence(s)
- `field_player_avatar.c` **PlayCollisionSoundIfNotFacingWarp** : 4 différence(s)
- `field_player_avatar.c` **GetRivalAvatarGraphicsIdByStateIdAndGender** : 3 différence(s)
- `field_player_avatar.c` **GetPlayerAvatarGenderByGraphicsId** : 1 différence(s)
- `field_player_avatar.c` **IsPlayerFacingSurfableFishableWater** : 3 différence(s)
- `field_player_avatar.c` **ClearPlayerAvatarInfo** : 3 différence(s)
- `field_player_avatar.c` **GetPlayerAvatarStateTransitionByGraphicsId** : 5 différence(s)
- `field_player_avatar.c` **GetPlayerAvatarGraphicsIdByCurrentState** : 4 différence(s)
- `field_player_avatar.c` **InitPlayerAvatar** : 8 différence(s)
- `field_player_avatar.c` **PlayerUseAcroBikeOnBumpySlope** : 1 différence(s)
- `field_player_avatar.c` **SetPlayerAvatarWatering** : 1 différence(s)
- `field_player_avatar.c` **PlayerAvatar_DoSecretBaseMatJump** : 1 différence(s)
- `field_player_avatar.c` **PlayerAvatar_SecretBaseMatSpinStep1** : 1 différence(s)
- `field_player_avatar.c` **PlayerAvatar_SecretBaseMatSpinStep2** : 6 différence(s)
- `field_player_avatar.c` **PlayerAvatar_SecretBaseMatSpinStep3** : 2 différence(s)
- `field_player_avatar.c` **CreateStopSurfingTask** : 1 différence(s)
- `field_player_avatar.c` **Task_StopSurfingInit** : 2 différence(s)
- `field_player_avatar.c` **Task_WaitStopSurfing** : 4 différence(s)
- `field_player_avatar.c` **StartFishing** : 2 différence(s)
- `field_player_avatar.c` **AlignFishingAnimationFrames** : 17 différence(s)
- `field_poison.c` **AllMonsFainted** : 1 différence(s)
- `field_poison.c` **FaintFromFieldPoison** : 4 différence(s)
- `field_poison.c` **MonFaintedFromPoison** : 5 différence(s)
- `field_poison.c` **Task_TryFieldPoisonWhiteOut** : 1 différence(s)
- `field_poison.c` **DoPoisonFieldEffect** : 4 différence(s)
- `field_screen_effect.c` **AnimateFlash** : 2 différence(s)
- `field_screen_effect.c` **WriteFlashScanlineEffectBuffer** : 4 différence(s)
- `field_special_scene.c` **FieldCB_ShowPortholeView** : 1 différence(s)
- `field_special_scene.c` **LookThroughPorthole** : 1 différence(s)
- `field_specials.c` **ResetCyclingRoadChallengeData** : 1 différence(s)
- `field_specials.c` **GetPlayerAvatarBike** : 2 différence(s)
- `field_specials.c` **GetPlayerTrainerIdOnesDigit** : 3 différence(s)
- `field_specials.c` **SpawnCameraObject** : 2 différence(s)
- `field_specials.c` **LeadMonHasEffortRibbon** : 2 différence(s)
- `field_specials.c` **GiveLeadMonEffortRibbon** : 7 différence(s)
- `field_specials.c` **IsPokerusInParty** : 2 différence(s)
- `field_specials.c` **GetLeadMonIndex** : 5 différence(s)
- `field_specials.c` **CountDigits** : 8 différence(s)
- `field_specials.c` **ChangeBoxPokemonNickname** : 8 différence(s)
- `field_specials.c` **ChangePokemonNickname** : 5 différence(s)
- `field_specials.c` **IsMonOTIDNotPlayers** : 1 différence(s)
- `field_specials.c` **GetMysteryGiftCardStat** : 1 différence(s)
- `field_specials.c` **ShouldShowBoxWasFullMessage** : 5 différence(s)
- `field_specials.c` **IsDestinationBoxFull** : 4 différence(s)
- `field_specials.c` **UsedPokemonCenterWarp** : 3 différence(s)
- `field_specials.c` **BufferTMHMMoveName** : 2 différence(s)
- `field_specials.c` **IncrementBirthIslandRockStepCount** : 6 différence(s)
- `field_tasks.c` **Task_RunTimeBasedEvents** : 3 différence(s)
- `field_tasks.c` **SetUpFieldTasks** : 1 différence(s)
- `field_tasks.c` **MarkIcePuzzleCoordVisited** : 8 différence(s)
- `field_tasks.c` **AshGrassPerStepCallback** : 2 différence(s)
- `field_tasks.c` **SetCrackedFloorHoleMetatile** : 3 différence(s)
- `field_tasks.c` **CrackedFloorPerStepCallback** : 1 différence(s)
- `field_weather.c` **StartWeather** : 2 différence(s)
- `field_weather.c` **Task_WeatherMain** : 1 différence(s)
- `field_weather.c` **ApplyFogBlend** : 6 différence(s)
- `field_weather.c` **UpdateSpritePaletteWithWeather** : 1 différence(s)
- `field_weather.c` **LoadDroughtWeatherPalette** : 1 différence(s)
- `field_weather.c` **DroughtStateInit** : 1 différence(s)
- `field_weather.c` **DroughtStateRun** : 2 différence(s)
- `field_weather_effects.c` **Clouds_InitVars** : 2 différence(s)
- `field_weather_effects.c` **Clouds_InitAll** : 2 différence(s)
- `field_weather_effects.c` **CreateCloudSprites** : 20 différence(s)
- `field_weather_effects.c` **Drought_InitAll** : 2 différence(s)
- `field_weather_effects.c` **Drought_Main** : 2 différence(s)
- `field_weather_effects.c` **UpdateDroughtBlend** : 6 différence(s)
- `field_weather_effects.c` **Snow_InitAll** : 2 différence(s)
- `field_weather_effects.c` **Thunderstorm_InitAll** : 2 différence(s)
- `field_weather_effects.c` **Downpour_InitAll** : 2 différence(s)
- `field_weather_effects.c` **FogHorizontal_InitVars** : 2 différence(s)
- `field_weather_effects.c` **FogHorizontal_InitAll** : 2 différence(s)
- `field_weather_effects.c` **FogHorizontalSpriteCallback** : 1 différence(s)
- `field_weather_effects.c` **CreateFogHorizontalSprites** : 1 différence(s)
- `field_weather_effects.c` **Ash_InitAll** : 2 différence(s)
- `field_weather_effects.c` **UpdateAshSprite** : 1 différence(s)
- `field_weather_effects.c` **FogDiagonal_InitAll** : 2 différence(s)
- `field_weather_effects.c` **UpdateFogDiagonalSprite** : 1 différence(s)
- `field_weather_effects.c` **UpdateSandstormSprite** : 1 différence(s)
- `field_weather_effects.c` **DestroyBubbleSprites** : 2 différence(s)
- `field_weather_util.c` **DoCurrentWeather** : 1 différence(s)
- `field_weather_util.c` **ResumePausedWeather** : 1 différence(s)
- `field_weather_util.c` **TranslateWeatherNum** : 1 différence(s)
- `fieldmap.c` **InitMap** : 1 différence(s)
- `fieldmap.c` **InitMapFromSavedGame** : 2 différence(s)
- `fieldmap.c` **InitMapLayoutData** : 11 différence(s)
- `fieldmap.c` **InitBackupMapLayoutData** : 6 différence(s)
- `fieldmap.c` **InitBackupMapLayoutConnections** : 19 différence(s)
- `fieldmap.c` **FillConnection** : 5 différence(s)
- `fieldmap.c` **FillSouthConnection** : 10 différence(s)
- `fieldmap.c` **FillNorthConnection** : 10 différence(s)
- `fieldmap.c` **FillWestConnection** : 10 différence(s)
- `fieldmap.c` **FillEastConnection** : 10 différence(s)
- `fieldmap.c` **MapGridGetElevationAt** : 2 différence(s)
- `fieldmap.c` **MapGridGetCollisionAt** : 3 différence(s)
- `fieldmap.c` **MapGridGetMetatileIdAt** : 5 différence(s)
- `fieldmap.c` **MapGridGetMetatileBehaviorAt** : 2 différence(s)
- `fieldmap.c` **MapGridGetMetatileLayerTypeAt** : 2 différence(s)
- `fieldmap.c` **MapGridSetMetatileIdAt** : 8 différence(s)
- `fieldmap.c` **MapGridSetMetatileEntryAt** : 3 différence(s)
- `fieldmap.c` **MapGridSetMetatileImpassabilityAt** : 6 différence(s)
- `fieldmap.c` **SaveMapView** : 3 différence(s)
- `fieldmap.c` **SavedMapViewIsEmpty** : 4 différence(s)
- `fieldmap.c` **ClearSavedMapView** : 2 différence(s)
- `fieldmap.c` **LoadSavedMapView** : 9 différence(s)
- `fieldmap.c` **MoveMapViewToBackup** : 18 différence(s)
- `fieldmap.c` **GetMapBorderIdAt** : 10 différence(s)
- `fieldmap.c` **CameraMove** : 5 différence(s)
- `fieldmap.c` **GetIncomingConnection** : 2 différence(s)
- `fieldmap.c` **IsCoordInIncomingConnectingMap** : 7 différence(s)
- `fieldmap.c` **GetMapConnectionAtPos** : 7 différence(s)
- `fieldmap.c` **ApplyGlobalTintToPaletteEntries** : 1 différence(s)
- `fieldmap.c` **ApplyGlobalTintToPaletteSlot** : 1 différence(s)
- `fieldmap.c` **LoadTilesetPalette** : 2 différence(s)
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
- `hall_of_fame.c` **InitHallOfFameScreen** : 2 différence(s) ; marqueurs de RF absents de la fusion : MUS_HALL_OF_FAME
- `hall_of_fame.c` **Task_Hof_InitTeamSaveData** : 5 différence(s)
- `hall_of_fame.c` **Task_Hof_TrySaveData** : 2 différence(s)
- `hall_of_fame.c` **Task_Hof_WaitAndPrintPlayerInfo** : 1 différence(s)
- `hall_of_fame.c` **Task_HofPC_CopySaveData** : 7 différence(s)
- `hall_of_fame.c` **Task_HofPC_HandlePaletteOnExit** : 1 différence(s)
- `hall_of_fame.c` **Task_HofPC_PrintDataIsCorrupted** : 1 différence(s)
- `hall_of_fame.c` **HallOfFame_PrintWelcomeText** : 2 différence(s)
- `hall_of_fame.c` **HallOfFame_PrintMonInfo** : 8 différence(s)
- `hall_of_fame.c` **HallOfFame_PrintPlayerInfo** : 7 différence(s)
- `heal_location.c` **GetHealLocation** : 2 différence(s)
- `hof_pc.c` **ReshowPCMenuAfterHallOfFamePC** : 1 différence(s)
- `image_processing_effects.c` **ConvertColorToGrayscale** : 17 différence(s)
- `intro.c` **LoadCopyrightGraphics** : 8 différence(s)
- `intro.c` **SetUpCopyrightScreen** : 34 différence(s)
- `intro.c` **CB2_InitCopyrightScreenAfterBootup** : 2 différence(s)
- `item.c` **ApplyNewEncryptionKeyToBagItems** : 7 différence(s)
- `item.c` **ApplyNewEncryptionKeyToBagItems_** : corps introuvable dans la fusion (déplacé ?)
- `item.c` **CopyItemName** : 1 différence(s)
- `item.c` **CheckBagHasItem** : 3 différence(s)
- `item.c` **HasAtLeastOneBerry** : 5 différence(s) ; marqueurs de RF absents de la fusion : ITEM_BERRY_POUCH
- `item.c` **CheckBagHasSpace** : 13 différence(s)
- `item.c` **AddBagItem** : 30 différence(s) ; marqueurs de RF absents de la fusion : FLAG_SYS_GOT_BERRY_POUCH, ITEM_BERRY_POUCH, ITEM_TM_CASE
- `item.c` **RemoveBagItem** : 24 différence(s)
- `item.c` **CheckPCHasItem** : 5 différence(s)
- `item.c` **AddPCItem** : 19 différence(s)
- `item.c` **RemovePCItem** : 5 différence(s)
- `item.c` **SwapItemSlots** : 5 différence(s)
- `item.c` **SanitizeItemId** : 2 différence(s)
- `item_menu.c` **GoToBagMenu** : 3 différence(s)
- `item_menu.c` **CB2_BagMenuFromStartMenu** : 1 différence(s)
- `item_menu.c` **CB2_BagMenuFromBattle** : 4 différence(s)
- `item_menu.c` **CreateBagInputHandlerTask** : 5 différence(s)
- `item_menu.c` **Task_BagMenu_HandleInput** : 5 différence(s)
- `item_menu.c` **OpenContextMenu** : 15 différence(s)
- `item_menu.c` **Task_ItemContext_Sell** : 2 différence(s)
- `item_menu.c` **UseRegisteredKeyItemOnField** : 6 différence(s)
- `item_use.c` **SetUpItemUseCallback** : 9 différence(s) ; marqueurs de RF absents de la fusion : ITEM_TYPE_FIELD
- `item_use.c` **CheckIfItemIsTMHMOrEvolutionStone** : 6 différence(s)
- `item_use.c` **CB2_CheckMail** : 1 différence(s)
- `item_use.c` **Task_UseRepel** : 6 différence(s)
- `item_use.c` **RemoveUsedItem** : 2 différence(s)
- `item_use.c` **Task_UsedBlackWhiteFlute** : 4 différence(s)
- `item_use.c` **ItemUseOutOfBattle_EscapeRope** : 1 différence(s)
- `item_use.c` **ItemUseOnFieldCB_EscapeRope** : 1 différence(s)
- `item_use.c` **ItemUseOutOfBattle_EnigmaBerry** : 8 différence(s)
- `item_use.c` **ItemUseInBattle_EnigmaBerry** : 4 différence(s)
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
- `menu_helpers.c` **Task_ContinueTaskAfterMessagePrints** : 1 différence(s)
- `menu_helpers.c` **Task_CallYesOrNoCallback** : 4 différence(s)
- `menu_helpers.c` **CreateYesNoMenuWithCallbacks** : 2 différence(s)
- `menu_helpers.c` **GetLRKeysPressedAndHeld** : 2 différence(s)
- `menu_helpers.c` **IsWritingMailAllowed** : 1 différence(s)
- `menu_helpers.c` **MenuHelpers_IsLinkActive** : 1 différence(s)
- `menu_helpers.c` **IsActiveOverworldLinkBusy** : 1 différence(s)
- `menu_helpers.c` **ResetVramOamAndBgCntRegs** : 2 différence(s)
- `menu_helpers.c` **AdjustQuantityAccordingToDPadInput** : 38 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsPokeGrass** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsReflective** : 2 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsEscalator** : 3 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsNonAnimDoor** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsNorthArrowWarp** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsSouthArrowWarp** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsForcedMovementTile** : 4 différence(s)
- `metatile_behavior.c` **MetatileBehavior_HasRipples** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsTallGrass** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsDiveable** : 4 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsUnableToEmerge** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsShallowFlowingWater** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsSurfableAndNotWaterfall** : 2 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsEastBlocked** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsWestBlocked** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsNorthBlocked** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsSouthBlocked** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsUnionRoomWarp** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsSeaweed** : 1 différence(s)
- `metatile_behavior.c` **MetatileBehavior_IsRunningDisallowed** : 1 différence(s)
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
- `naming_screen.c` **NamingScreen_Init** : 1 différence(s)
- `naming_screen.c` **CreateNamingScreenTask** : 1 différence(s)
- `naming_screen.c` **Task_NamingScreen** : 1 différence(s)
- `naming_screen.c` **MainState_FadeIn** : 2 différence(s)
- `naming_screen.c` **MainState_PressedOKButton** : 2 différence(s)
- `naming_screen.c` **MainState_Exit** : 4 différence(s)
- `naming_screen.c` **DisplaySentToPCMessage** : 5 différence(s) ; marqueurs de RF absents de la fusion : FLAG_SYS_NOT_SOMEONES_PC
- `naming_screen.c` **StartPageSwapAnim** : 1 différence(s)
- `naming_screen.c` **Task_HandlePageSwapAnim** : 1 différence(s)
- `naming_screen.c` **PageSwapAnimState_1** : 4 différence(s)
- `naming_screen.c` **PageSwapAnimState_2** : 4 différence(s)
- `naming_screen.c` **CreateButtonFlashTask** : 1 différence(s)
- `naming_screen.c` **SpriteCB_InputArrow** : 3 différence(s)
- `naming_screen.c` **SpriteCB_Underscore** : 4 différence(s)
- `naming_screen.c` **PageSwapSprite_SlideOff** : 2 différence(s)
- `naming_screen.c` **PageSwapSprite_SlideOn** : 2 différence(s)
- `naming_screen.c` **CreateBackOkSprites** : 1 différence(s)
- `naming_screen.c` **NamingScreen_CreatePCIcon** : 2 différence(s)
- `naming_screen.c` **KeyboardKeyHandler_Character** : 1 différence(s)
- `naming_screen.c` **HandleDpadMovement** : 6 différence(s)
- `naming_screen.c` **DrawNormalTextEntryBox** : 3 différence(s)
- `naming_screen.c` **DrawMonTextEntryBox** : 4 différence(s)
- `naming_screen.c` **DrawGenderIcon** : 2 différence(s)
- `naming_screen.c` **LoadPalettes** : 1 différence(s)
- `naming_screen.c` **DrawTextEntry** : 2 différence(s)
- `naming_screen.c` **PrintKeyboardKeys** : 2 différence(s)
- `naming_screen.c` **DrawKeyboardPageOnDeck** : 1 différence(s)
- `naming_screen.c` **PrintControls** : 4 différence(s)
- `naming_screen.c` **IsWideLetter** : 1 différence(s)
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
- `party_menu.c` **InitPartyMenu** : 5 différence(s)
- `party_menu.c` **ShowPartyMenu** : 48 différence(s)
- `party_menu.c` **ExitPartyMenu** : 1 différence(s)
- `party_menu.c` **AllocPartyMenuBg** : 2 différence(s)
- `party_menu.c` **AllocPartyMenuBgGfx** : 17 différence(s)
- `party_menu.c` **PartyPaletteBufferCopy** : 1 différence(s)
- `party_menu.c` **InitPartyMenuBoxes** : 7 différence(s)
- `party_menu.c` **RenderPartyMenuBox** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonDataForMoveTutorOrEvolutionItem** : 3 différence(s)
- `party_menu.c` **DisplayPartyPokemonDataForMultiBattle** : 3 différence(s)
- `party_menu.c` **AnimatePartySlot** : 4 différence(s)
- `party_menu.c` **GetPartyBoxPaletteFlags** : 3 différence(s)
- `party_menu.c` **IsMultiBattle** : 1 différence(s)
- `party_menu.c` **SwapPartyPokemon** : 4 différence(s)
- `party_menu.c` **Task_ClosePartyMenu** : 1 différence(s)
- `party_menu.c` **Task_ClosePartyMenuAndSetCB2** : 1 différence(s)
- `party_menu.c` **HandleChooseMonSelection** : 6 différence(s)
- `party_menu.c` **HandleChooseMonCancel** : 2 différence(s)
- `party_menu.c` **DisplayCancelChooseMonYesNo** : 3 différence(s)
- `party_menu.c` **UpdatePartySelectionSingleLayout** : 4 différence(s)
- `party_menu.c` **UpdatePartySelectionDoubleLayout** : 2 différence(s)
- `party_menu.c` **Task_PrintAndWaitForText** : 1 différence(s)
- `party_menu.c` **DisplayGaveHeldItemMessage** : 1 différence(s)
- `party_menu.c` **DisplayTookHeldItemMessage** : 1 différence(s)
- `party_menu.c` **DisplaySwitchedHeldItemMessage** : 1 différence(s)
- `party_menu.c` **GiveItemToMon** : 1 différence(s)
- `party_menu.c` **BufferBagFullCantTakeItemMessage** : 1 différence(s) ; marqueurs de RF absents de la fusion : ITEM_BERRY_POUCH, ITEM_TM_CASE
- `party_menu.c` **Task_PartyMenuModifyHP** : 2 différence(s)
- `party_menu.c` **SetPartyMonsAllowedInMinigame** : 11 différence(s)
- `party_menu.c` **CanMonLearnTMTutor** : 4 différence(s) ; marqueurs de RF absents de la fusion : ITEM_TM01_FOCUS_PUNCH
- `party_menu.c` **GetTutorMove** : 3 différence(s)
- `party_menu.c` **CanLearnTutorMove** : 3 différence(s)
- `party_menu.c` **InitPartyMenuWindows** : 6 différence(s)
- `party_menu.c` **CreateCancelConfirmWindows** : 16 différence(s)
- `party_menu.c` **BlitBitmapToPartyWindow** : 4 différence(s)
- `party_menu.c` **BlitBitmapToPartyWindow_LeftColumn** : 2 différence(s)
- `party_menu.c` **BlitBitmapToPartyWindow_RightColumn** : 2 différence(s)
- `party_menu.c` **LoadPartyBoxPalette** : 1 différence(s)
- `party_menu.c` **DisplayPartyPokemonNickname** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonLevelCheck** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonLevel** : 1 différence(s)
- `party_menu.c` **DisplayPartyPokemonGenderNidoranCheck** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonHPCheck** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonMaxHPCheck** : 4 différence(s)
- `party_menu.c` **DisplayPartyPokemonDescriptionText** : 6 différence(s)
- `party_menu.c` **DisplayPartyMenuStdMessage** : 10 différence(s)
- `party_menu.c` **ShouldUseChooseMonText** : 4 différence(s)
- `party_menu.c` **DisplaySelectionWindow** : 12 différence(s)
- `party_menu.c` **PartyMenuDisplayYesNoMenu** : 1 différence(s)
- `party_menu.c` **DrawHeldItemIconsForTrade** : 4 différence(s)
- `party_menu.c` **SetPartyMonSelectionActions** : 3 différence(s)
- `party_menu.c` **SetPartyMonFieldSelectionActions** : 12 différence(s)
- `party_menu.c` **GetPartyMenuActionsType** : 12 différence(s)
- `party_menu.c` **CreateSelectionWindow** : 4 différence(s)
- `party_menu.c` **Task_TryCreateSelectionWindow** : 4 différence(s)
- `party_menu.c` **CB2_ShowPokemonSummaryScreen** : 3 différence(s)
- `party_menu.c` **CB2_ReturnToPartyMenuFromSummaryScreen** : 2 différence(s)
- `party_menu.c` **SwitchSelectedMons** : 1 différence(s)
- `party_menu.c` **TryMovePartySlot** : 4 différence(s)
- `party_menu.c` **CB2_SelectBagItemToGive** : 1 différence(s)
- `party_menu.c` **CB2_WriteMailToGiveMon** : 1 différence(s)
- `party_menu.c` **CB2_ReturnToPartyMenuFromWritingMail** : 1 différence(s)
- `party_menu.c` **Task_UpdateHeldItemSprite** : 6 différence(s)
- `party_menu.c` **Task_HandleFieldMoveExitAreaYesNoInput** : 1 différence(s)
- `party_menu.c` **Task_CancelAfterAorBPress** : 4 différence(s)
- `party_menu.c` **SetUpFieldMove_Surf** : 2 différence(s)
- `party_menu.c` **DisplayCantUseSurfMessage** : 2 différence(s) ; marqueurs de RF absents de la fusion : MAP_GROUP, MAP_NUM, MAP_ROUTE17, MAP_ROUTE18
- `party_menu.c` **CB2_ShowPartyMenuForItemUse** : 8 différence(s)
- `party_menu.c` **CB2_ReturnToBagMenu** : 4 différence(s)
- `party_menu.c` **ItemUseCB_Medicine** ✓ : 3 différence(s)
- `party_menu.c` **ShowMoveSelectWindow** : 9 différence(s)
- `party_menu.c` **SetSelectedMoveForPPItem** : 2 différence(s)
- `party_menu.c` **ItemUseCB_PPUp** : 2 différence(s)
- `party_menu.c` **ItemIdToBattleMoveId** : 1 différence(s) ; marqueurs de RF absents de la fusion : ITEM_TM01_FOCUS_PUNCH
- `party_menu.c` **IsMoveHm** : 3 différence(s)
- `party_menu.c` **MonKnowsMove** : 2 différence(s)
- `party_menu.c` **ItemUseCB_TMHM** ✓ : 2 différence(s)
- `party_menu.c` **Task_LearnedMove** : 2 différence(s)
- `party_menu.c` **Task_LearnNextMoveOrClosePartyMenu** : 4 différence(s)
- `party_menu.c` **CB2_ReturnToPartyMenuWhileLearningMove** : 7 différence(s)
- `party_menu.c` **ItemUseCB_RareCandy** ✓ : 1 différence(s)
- `party_menu.c` **Task_DisplayLevelUpStatsPg1** : 4 différence(s)
- `party_menu.c` **Task_DisplayLevelUpStatsPg2** : 4 différence(s)
- `party_menu.c` **Task_TryLearnNewMoves** : 5 différence(s)
- `party_menu.c` **Task_TryLearningNextMove** : 1 différence(s)
- `party_menu.c` **UseSacredAsh** : 1 différence(s)
- `party_menu.c` **Task_SacredAshLoop** : 1 différence(s)
- `party_menu.c` **TryTutorSelectedMon** : 5 différence(s)
- `party_menu.c` **CB2_ChooseMonToGiveItem** : 6 différence(s)
- `party_menu.c` **CB2_WriteMailToGiveMonFromBag** : 1 différence(s)
- `party_menu.c` **TryGiveMailToSelectedMon** : 2 différence(s)
- `party_menu.c` **GetPartySlotEntryStatus** : 2 différence(s)
- `party_menu.c` **GetBattleEntryEligibility** : 13 différence(s)
- `party_menu.c` **CheckBattleEntriesAndGetMessage** : 20 différence(s)
- `party_menu.c` **HasPartySlotAlreadyBeenSelected** : 2 différence(s)
- `party_menu.c` **ChooseMonForMoveTutor** : 2 différence(s)
- `party_menu.c` **GetPartyMenuActionsTypeInBattle** : 8 différence(s)
- `party_menu.c` **TrySwitchInPokemon** : 3 différence(s)
- `party_menu.c` **BufferBattlePartyOrder** : 12 différence(s)
- `party_menu.c` **BufferBattlePartyOrderBySide** : 11 différence(s)
- `party_menu.c` **SwitchPartyOrderLinkMulti** : 10 différence(s)
- `party_menu.c` **GetPartyIdFromBattlePartyId** : 7 différence(s)
- `party_menu.c` **UpdatePartyToBattleOrder** : 2 différence(s)
- `party_menu.c` **UpdatePartyToFieldOrder** : 2 différence(s)
- `party_menu.c` **SwitchAliveMonIntoLeadSlot** : 2 différence(s)
- `party_menu.c` **CB2_SetUpExitToBattleScreen** : 3 différence(s)
- `party_menu.c` **Task_MultiPartnerPartySlideIn** : 3 différence(s)
- `party_menu.c` **SlideMultiPartyMenuBoxSpritesOneStep** : 3 différence(s)
- `party_menu.c` **ChooseMonForDaycare** : 2 différence(s)
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
- `pokemon.c` **CreateBattleTowerMon** : 7 différence(s)
- `pokemon.c` **ConvertPokemonToBattleTowerPokemon** : 1 différence(s)
- `pokemon.c` **GiveMoveToBoxMon** : 2 différence(s)
- `pokemon.c` **GiveMoveToBattleMon** : 2 différence(s)
- `pokemon.c` **CalculateBaseDamage** : 6 différence(s)
- `pokemon.c` **GetDefaultMoveTarget** : 2 différence(s)
- `pokemon.c` **SetMultiuseSpriteTemplateToPokemon** : 9 différence(s)
- `pokemon.c` **GetBoxMonData3** : 1 différence(s)
- `pokemon.c` **SetMonData** : 6 différence(s)
- `pokemon.c` **SetBoxMonData** : 3 différence(s)
- `pokemon.c` **GetMonsStateToDoubles** : 2 différence(s)
- `pokemon.c` **CreateSecretBaseEnemyParty** : 1 différence(s)
- `pokemon.c` **GetSpeciesName** : 2 différence(s)
- `pokemon.c` **CopyPlayerPartyMonToBattleData** : 3 différence(s)
- `pokemon.c` **PokemonUseItemEffects** : 58 différence(s)
- `pokemon.c` **GetEvolutionTargetSpecies** : 4 différence(s)
- `pokemon.c` **HoennPokedexNumToSpecies** : 2 différence(s)
- `pokemon.c` **NationalPokedexNumToSpecies** : 2 différence(s)
- `pokemon.c` **NationalToHoennOrder** : 2 différence(s)
- `pokemon.c` **SpeciesToCryId** : 3 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_OLD_UNOWN_B, SPECIES_OLD_UNOWN_Z
- `pokemon.c` **DrawSpindaSpotsUnused** : 2 différence(s)
- `pokemon.c` **GetTrainerEncounterMusicId** : 1 différence(s)
- `pokemon.c` **AdjustFriendship** : 9 différence(s)
- `pokemon.c` **MonGainEVs** : 12 différence(s)
- `pokemon.c` **RandomlyGivePartyPokerus** : 3 différence(s)
- `pokemon.c` **UpdatePartyPokerusTime** : 4 différence(s)
- `pokemon.c` **PartySpreadPokerus** : 4 différence(s)
- `pokemon.c` **TryIncrementMonLevel** : 8 différence(s)
- `pokemon.c` **CanMonLearnTMHM** : 2 différence(s)
- `pokemon.c` **SpeciesToPokedexNum** ✓ : 2 différence(s)
- `pokemon.c` **GetBattleBGM** : 19 différence(s) ; marqueurs de RF absents de la fusion : MUS_RS_VS_TRAINER, TRAINER_CLASS_COOLTRAINER, TRAINER_CLASS_GENTLEMAN
- `pokemon.c` **GetMonSpritePalFromSpeciesAndPersonality** : 3 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_EGG
- `pokemon.c` **SetWildMonHeldItem** : 17 différence(s) ; marqueurs de RF absents de la fusion : BATTLE_TYPE_POKEDUDE
- `pokemon.c` **GetTrainerPartnerName** : 1 différence(s)
- `pokemon.c` **GetUnionRoomTrainerPic** : 2 différence(s)
- `pokemon.c` **GetUnionRoomTrainerClass** : 2 différence(s)
- `pokemon.c` **CreateMonSpritesGfxManager** : 71 différence(s)
- `pokemon.c` **DestroyMonSpritesGfxManager** : 15 différence(s)
- `pokemon.c` **MonSpritesGfxManager_GetSpritePtr** : 4 différence(s)
- `pokemon_icon.c` **CreateMonIcon** : 2 différence(s)
- `pokemon_icon.c` **GetIconSpecies** : 1 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_icon.c` **GetUnownLetterByPersonality** : 3 différence(s)
- `pokemon_icon.c` **GetMonIconTiles** : 4 différence(s)
- `pokemon_icon.c` **SafeLoadMonIconPalette** : 1 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_icon.c` **LoadMonIconPalette** : 1 différence(s)
- `pokemon_icon.c` **SafeFreeMonIconPalette** : 1 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_icon.c` **GetValidMonIconPalettePtr** : 1 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
- `pokemon_icon.c` **GetValidMonIconPalIndex** : 1 différence(s) ; marqueurs de RF absents de la fusion : SPECIES_NONE
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
- `scrcmd.c` **ScrCmd_gotonative** : 3 différence(s)
- `scrcmd.c` **ScrCmd_special** : 5 différence(s)
- `scrcmd.c` **ScrCmd_specialvar** : 6 différence(s)
- `scrcmd.c` **ScrCmd_callnative** : 5 différence(s)
- `scrcmd.c` **ScrCmd_goto** : 1 différence(s)
- `scrcmd.c` **ScrCmd_call** : 1 différence(s)
- `scrcmd.c` **ScrCmd_goto_if** : 3 différence(s)
- `scrcmd.c` **ScrCmd_call_if** : 3 différence(s)
- `scrcmd.c` **ScrCmd_vgoto** : 4 différence(s)
- `scrcmd.c` **ScrCmd_vcall** : 4 différence(s)
- `scrcmd.c` **ScrCmd_vgoto_if** : 4 différence(s)
- `scrcmd.c` **ScrCmd_vcall_if** : 4 différence(s)
- `scrcmd.c` **ScrCmd_gotostd** : 4 différence(s)
- `scrcmd.c` **ScrCmd_callstd** : 4 différence(s)
- `scrcmd.c` **ScrCmd_gotostd_if** : 7 différence(s)
- `scrcmd.c` **ScrCmd_callstd_if** : 7 différence(s)
- `scrcmd.c` **ScrCmd_setmysteryeventstatus** : 2 différence(s)
- `scrcmd.c` **ScrCmd_trywondercardscript** : 1 différence(s)
- `scrcmd.c` **ScrCmd_copybyte** : 2 différence(s)
- `scrcmd.c` **ScrCmd_copyvar** : 6 différence(s)
- `scrcmd.c` **Compare** : 2 différence(s)
- `scrcmd.c` **ScrCmd_additem** : 1 différence(s)
- `scrcmd.c` **ScrCmd_adddecoration** : 1 différence(s)
- `scrcmd.c` **ScrCmd_removedecoration** : 1 différence(s)
- `scrcmd.c` **ScrCmd_checkdecorspace** : 1 différence(s)
- `scrcmd.c` **ScrCmd_checkdecor** : 1 différence(s)
- `scrcmd.c` **ScrCmd_initclock** : 1 différence(s)
- `scrcmd.c` **ScrCmd_dotimebasedevents** : 1 différence(s)
- `scrcmd.c` **ScrCmd_gettime** : 4 différence(s)
- `scrcmd.c` **ScrCmd_warpteleport** : 1 différence(s)
- `scrcmd.c` **ScrCmd_playbgm** : 1 différence(s)
- `scrcmd.c` **ScrCmd_fadedefaultbgm** : 1 différence(s)
- `scrcmd.c` **ScrCmd_fadenewbgm** : 2 différence(s)
- `scrcmd.c` **ScrCmd_fadeoutbgm** : 1 différence(s)
- `scrcmd.c` **ScrCmd_fadeinbgm** : 1 différence(s)
- `scrcmd.c` **ScrCmd_lockall** : 1 différence(s)
- `scrcmd.c` **ScrCmd_lock** : 1 différence(s)
- `scrcmd.c` **ScrCmd_messageautoscroll** : 2 différence(s)
- `scrcmd.c` **WaitForAorBPress** : 1 différence(s)
- `scrcmd.c` **ScrCmd_waitbuttonpress** : 1 différence(s)
- `scrcmd.c` **ScrCmd_drawboxtext** : 1 différence(s)
- `scrcmd.c` **ScrCmd_showmonpic** : 1 différence(s)
- `scrcmd.c` **ScrCmd_showcontestpainting** : 2 différence(s)
- `scrcmd.c` **ScrCmd_braillemessage** : 11 différence(s)
- `scrcmd.c` **ScrCmd_bufferitemnameplural** : 2 différence(s)
- `scrcmd.c` **ScrCmd_bufferdecorationname** : 1 différence(s)
- `scrcmd.c` **ScrCmd_givemon** : 6 différence(s)
- `scrcmd.c` **ScrCmd_checkpartymove** : 1 différence(s)
- `scrcmd.c` **ScrCmd_showmoneybox** : 4 différence(s)
- `scrcmd.c` **ScrCmd_showcoinsbox** : 4 différence(s)
- `scrcmd.c` **ScrCmd_playslotmachine** : 1 différence(s)
- `scrcmd.c` **ScrCmd_setberrytree** : 1 différence(s)
- `scrcmd.c` **ScrCmd_getpokenewsactive** : 1 différence(s)
- `scrcmd.c` **ScrCmd_choosecontestmon** : 1 différence(s)
- `scrcmd.c` **ScrCmd_startcontest** : 2 différence(s)
- `scrcmd.c` **ScrCmd_showcontestresults** : 2 différence(s)
- `scrcmd.c` **ScrCmd_contestlinktransfer** : 2 différence(s)
- `scrcmd.c` **ScrCmd_setmetatile** : 1 différence(s)
- `scrcmd.c` **ScrCmd_addelevmenuitem** : 1 différence(s)
- `script.c` **RunScriptCommand** : 9 différence(s)
- `script.c` **ScriptContext_SetupScript** : 1 différence(s)
- `script.c` **RunScriptImmediately** : 2 différence(s)
- `script.c` **MapHeaderGetScriptTable** : 5 différence(s)
- `script.c` **MapHeaderRunScriptType** : 1 différence(s)
- `script.c` **MapHeaderCheckScriptTable** : 3 différence(s)
- `script.c` **TryRunOnFrameMapScript** : 1 différence(s)
- `script.c` **GetSavedRamScriptIfValid** : 2 différence(s)
- `script.c` **InitRamScript_NoObjectEvent** : 1 différence(s)
- `script_menu.c` **ScriptMenu_Multichoice** : 2 différence(s)
- `script_menu.c` **ScriptMenu_MultichoiceWithDefault** : 2 différence(s)
- `script_menu.c` **ScriptMenu_YesNo** : 4 différence(s)
- `script_menu.c` **ScriptMenu_MultichoiceGrid** : 20 différence(s)
- `script_menu.c` **ScriptMenu_DisplayPCStartupPrompt** : 1 différence(s)
- `script_menu.c` **ScriptMenu_ShowPokemonPic** : 8 différence(s)
- `script_menu.c` **CreateWindowFromRect** : 2 différence(s)
- `script_movement.c` **ScriptMovement_UnfreezeObjectEvents** : 2 différence(s)
- `script_movement.c` **ScriptMovement_StartMoveObjects** : 3 différence(s)
- `script_movement.c` **GetMovementScriptIdFromObjectEventId** : 2 différence(s)
- `script_movement.c` **ScriptMovement_TakeStep** : 1 différence(s)
- `script_pokemon_util.c` **ScriptGiveMon** : 7 différence(s)
- `script_pokemon_util.c` **ScriptGiveEgg** : 8 différence(s)
- `script_pokemon_util.c` **CreateScriptedWildMon** : 1 différence(s)
- `script_pokemon_util.c` **ScriptSetMonMoveSlot** : 2 différence(s)
- `script_pokemon_util.c` **ChooseHalfPartyForBattle** : 1 différence(s)
- `shop.c` **CreateShopMenu** : 6 différence(s)
- `shop.c` **Task_ShopMenu** : 1 différence(s)
- `shop.c` **Task_HandleShopMenuBuy** : 1 différence(s)
- `shop.c` **Task_HandleShopMenuSell** : 2 différence(s)
- `shop.c` **CB2_GoToSellMenu** : 3 différence(s)
- `shop.c` **Task_HandleShopMenuQuit** : 1 différence(s)
- `shop.c` **Task_ReturnToShopMenu** : 2 différence(s)
- `shop.c` **BuyMenuBuildListMenuTemplate** : 5 différence(s)
- `shop.c` **BuyMenuPrintItemDescriptionAndShowItemIcon** : 6 différence(s)
- `shop.c` **BuyMenuPrintPriceInList** : 2 différence(s)
- `shop.c` **BuyMenuDrawMapBg** : 2 différence(s)
- `shop.c` **BuyMenuDrawMapMetatile** : 3 différence(s)
- `shop.c` **BuyMenuPrintItemQuantityAndPrice** : 1 différence(s)
- `shop.c` **Task_BuyMenu** : 2 différence(s)
- `shop.c` **Task_BuyHowManyDialogueInit** : 2 différence(s)
- `shop.c` **Task_BuyHowManyDialogueHandleInput** : 1 différence(s)
- `shop.c` **BuyMenuTryMakePurchase** : 3 différence(s)
- `shop.c` **BuyMenuSubtractMoney** : 2 différence(s) ; marqueurs de RF absents de la fusion : SE_SHOP
- `shop.c` **CreatePokemartMenu** ✓ : 1 différence(s)
- `shop.c` **CreateDecorationShop1Menu** : 2 différence(s)
- `shop.c` **CreateDecorationShop2Menu** : 2 différence(s)
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
- `string_util.c` **ExpandPlaceholder_Version** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Magma** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Aqua** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Maxie** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Archie** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Groudon** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `string_util.c` **ExpandPlaceholder_Kyogre** : 2 différence(s) ; marqueurs de RF absents de la fusion : FIRERED, LEAFGREEN
- `tileset_anims.c` **QueueAnimTiles_General_Flower** : 3 différence(s)
- `tileset_anims.c` **TilesetAnim_General** : 6 différence(s)
- `tileset_anims.c` **InitTilesetAnim_General** : 1 différence(s)
- `title_screen.c` **CB2_InitTitleScreen** : 52 différence(s)
- `title_screen.c` **ResetGpuRegs** : 8 différence(s)
- `title_screen.c` **VBlankCB** : 1 différence(s)
- `tm_case.c` **PrintTitle** : 2 différence(s)
- `trade.c` **CB2_CreateTradeMenu** : 29 différence(s) ; marqueurs de RF absents de la fusion : MUS_GAME_CORNER
- `trainer_card.c` **CloseTrainerCard** : 4 différence(s)
- `trainer_card.c` **Task_TrainerCard** : 43 différence(s)
- `trainer_card.c` **LoadCardGfx** : 28 différence(s)
- `trainer_card.c` **CB2_InitTrainerCard** : 13 différence(s)
- `trainer_card.c` **SetPlayerCardData** : 27 différence(s)
- `trainer_card.c` **TrainerCard_GenerateCardForLinkPlayer** : 18 différence(s) ; marqueurs de RF absents de la fusion : VAR_EGG_BRAG_STATE, VAR_HOF_BRAG_STATE, VAR_LINK_WIN_BRAG_STATE, VAR_TRAINER_CARD_MON_ICON_1, VAR_TRAINER_CARD_MON_ICON_2, VAR_TRAINER_CARD_MON_ICON_3, VAR_TRAINER_CARD_MON_ICON_4, VAR_TRAINER_CARD_MON_ICON_5, VAR_TRAINER_CARD_MON_ICON_6, VAR_TRAINER_CARD_MON_ICON_TINT_IDX
- `trainer_card.c` **SetDataFromTrainerCard** : 38 différence(s) ; marqueurs de RF absents de la fusion : FLAG_BADGE08_GET
- `trainer_card.c` **UpdateCardFlipRegs** : 4 différence(s)
- `trainer_card.c` **ResetGpuRegs** : 5 différence(s)
- `trainer_card.c` **InitBgsAndWindows** : 2 différence(s)
- `trainer_card.c` **PrintAllOnCardFront** : 3 différence(s)
- `trainer_card.c` **PrintAllOnCardBack** : 6 différence(s)
- `trainer_card.c` **PrintNameOnCardFront** : 16 différence(s)
- `trainer_card.c` **PrintIdOnCard** : 18 différence(s)
- `trainer_card.c` **PrintMoneyOnCard** : 15 différence(s)
- `trainer_card.c` **GetCaughtMonsCount** : 1 différence(s)
- `trainer_card.c` **PrintPokedexOnCard** : 17 différence(s)
- `trainer_card.c` **PrintTimeOnCard** : 28 différence(s)
- `trainer_card.c` **PrintProfilePhraseOnCard** : 30 différence(s)
- `trainer_card.c` **BufferNameForCardBack** : 13 différence(s)
- `trainer_card.c` **PrintNameOnCardBack** : 17 différence(s)
- `trainer_card.c` **BufferHofDebutTime** : 17 différence(s)
- `trainer_card.c` **PrintHofDebutTimeOnCard** : 5 différence(s)
- `trainer_card.c` **BufferLinkBattleResults** : 14 différence(s)
- `trainer_card.c` **PrintLinkBattleResultsOnCard** : 6 différence(s)
- `trainer_card.c` **BufferNumTrades** : 6 différence(s)
- `trainer_card.c` **PrintTradesStringOnCard** : 8 différence(s)
- `trainer_card.c` **BufferBerryCrushPoints** : 3 différence(s)
- `trainer_card.c` **PrintBerryCrushStringOnCard** : 11 différence(s)
- `trainer_card.c` **BufferUnionRoomStats** : 6 différence(s)
- `trainer_card.c` **PrintUnionStringOnCard** : 10 différence(s)
- `trainer_card.c` **PrintPokemonIconsOnCard** : 10 différence(s)
- `trainer_card.c` **LoadMonIconGfx** : 15 différence(s)
- `trainer_card.c` **PrintStickersOnCard** : 7 différence(s)
- `trainer_card.c` **LoadStickerGfx** : 5 différence(s)
- `trainer_card.c` **DrawCardScreenBackground** : 1 différence(s)
- `trainer_card.c` **DrawCardFrontOrBack** : 1 différence(s)
- `trainer_card.c` **DrawStarsAndBadgesOnCard** : 13 différence(s)
- `trainer_card.c` **DrawCardBackStats** : 1 différence(s)
- `trainer_card.c` **BlinkTimeColon** : 4 différence(s)
- `trainer_card.c` **GetTrainerCardStars** : 3 différence(s)
- `trainer_card.c` **IsCardFlipTaskActive** : 1 différence(s)
- `trainer_card.c` **Task_AnimateCardFlipDown** : 17 différence(s)
- `trainer_card.c` **Task_DrawFlippedCardSide** : 13 différence(s)
- `trainer_card.c` **Task_SetCardFlipped** : 6 différence(s)
- `trainer_card.c` **Task_AnimateCardFlipUp** : 14 différence(s)
- `trainer_card.c` **ShowPlayerTrainerCard** : 6 différence(s)
- `trainer_card.c` **ShowTrainerCardInLink** : 6 différence(s)
- `trainer_card.c` **InitTrainerCardData** : 10 différence(s)
- `trainer_card.c` **CreateTrainerCardTrainerPic** : 24 différence(s)
- `trainer_fan_club.c` **BufferFanClubTrainerName** : 2 différence(s)
- `trainer_pokemon_sprites.c` **DecompressPic** : 4 différence(s)
- `trainer_pokemon_sprites.c` **LoadPicPaletteBySlot** : 2 différence(s)
- `trainer_pokemon_sprites.c` **CreatePicSprite** : 8 différence(s)
- `trainer_pokemon_sprites.c` **CreateTrainerCardSprite** : 6 différence(s)
- `trainer_pokemon_sprites.c` **PlayerGenderToFrontTrainerPicId** : 6 différence(s)
- `trainer_see.c` **CheckForTrainersWantingBattle** : 11 différence(s)
- `trainer_see.c` **CheckTrainer** : 11 différence(s)
- `trainer_see.c` **GetTrainerApproachDistance** : 1 différence(s)
- `trainer_see.c` **GetTrainerApproachDistanceSouth** : 1 différence(s)
- `trainer_see.c` **CheckPathBetweenTrainerAndPlayer** : 13 différence(s)
- `trainer_see.c` **Task_RunTrainerSeeFuncList** : 2 différence(s)
- `trainer_see.c` **FldEff_QuestionMarkIcon** : 1 différence(s)
- `trainer_tower.c` **GetOwnerState** : 8 différence(s)
- `trainer_tower.c` **GiveChallengePrize** : 4 différence(s)
- `trainer_tower.c` **CheckFinalTime** : 12 différence(s)
- `union_room.c` **Task_RunUnionRoom** : 30 différence(s) ; marqueurs de RF absents de la fusion : SE_NOTE_C
- `wild_encounter.c` **ChooseWildMonLevel** : 1 différence(s)
- `wild_encounter.c` **GetCurrentMapWildMonHeaderId** : 2 différence(s)
- `wild_encounter.c` **TryGenerateWildMon** : 5 différence(s)
- `wild_encounter.c` **StandardWildEncounter** : 26 différence(s)
- `wild_encounter.c` **RockSmashWildEncounter** : 10 différence(s)
- `wild_encounter.c` **SweetScentWildEncounter** : 14 différence(s)
- `wild_encounter.c` **DoesCurrentMapHaveFishingMons** : 5 différence(s)
- `wild_encounter.c` **FishingWildEncounter** : 3 différence(s)
- `wild_encounter.c` **UpdateRepelCounter** : 2 différence(s)
- `wild_encounter.c` **ApplyFluteEncounterRateMod** : 7 différence(s)
- `wild_encounter.c` **ApplyCleanseTagEncounterRateMod** : 3 différence(s)
- `wonder_news.c` **WonderNews_GetRewardInfo** : 1 différence(s)
- `wonder_news.c` **GetRewardType** : 2 différence(s)
