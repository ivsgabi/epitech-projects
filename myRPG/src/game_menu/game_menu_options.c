/*
** EPITECH PROJECT, 2023
** game_menu_options
** File description:
** handle game menu options/settings
*/

#include <stdlib.h>

#include "struct.h"
#include "game_menu.h"
#include "intro_struct.h"

void if_gm_cross_clicked(arg_t *arg, game_menu_t *game_menu)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 16 && mouse_pos.x <= 126
    && mouse_pos.y >= 23 && mouse_pos.y <= 130) {
        game_menu->gm_status = 0;
        arg->can_move = 1;
    }
}

void gm_music_volume_settings(arg_t *arg, intro_t *intro, sfMusic **music)
{
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1267 && mouse_pos.x <= 1398
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        intro->music_volume = intro->music_volume + 15.0;
        sfMusic_setVolume(*music, intro->music_volume);
    } if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1305 && mouse_pos.x <= 1335
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        intro->music_volume = intro->music_volume - 15.0;
        sfMusic_setVolume(*music, intro->music_volume);
    } if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1340 && mouse_pos.x <= 1370
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        intro->music_volume = 0;
        sfMusic_setVolume(*music, intro->music_volume);
    }
}

void gm_window_settings(arg_t *arg)
{
    sfVideoMode desktopMode = sfVideoMode_getDesktopMode();
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1606 && mouse_pos.x <= 1640
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        sfRenderWindow_setSize(arg->window, (sfVector2u){630, 350});
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1644 && mouse_pos.x <= 1673
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        sfRenderWindow_setSize(arg->window, (sfVector2u){1430, 850});
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 1679 && mouse_pos.x <= 1710
    && mouse_pos.y >= 322 && mouse_pos.y <= 356) {
        sfRenderWindow_setSize(arg->window,
        (sfVector2u){desktopMode.width, desktopMode.height});
    }
}

void display_inventory(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 200 && intro->mouse_pos.x <= 645
    && intro->mouse_pos.y >= 248 && intro->mouse_pos.y <= 345) {
        arg->inventory->display_inventory = 1;
        arg->battle->battle_img[4]->pos.x = 920.0;
        arg->battle->battle_img[4]->pos.y = 360.0;
        arg->inventory->text->str = "A device for catching\nwild Pokemon.";
    }
}

int game_menu_options(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music)
{
    if_gm_cross_clicked(arg, game_menu);
    if (back_to_main_menu(arg, intro, game_menu, music) == BACK_TO_MENU)
        return BACK_TO_MENU;
    gm_music_volume_settings(arg, intro, music);
    gm_window_settings(arg);
    handle_command_list_displaying(arg, intro, game_menu);
    display_inventory(arg, intro, game_menu);
    gm_save_game(arg, intro, game_menu);
    if (game_menu->display_command_list != 0) {
        sfRenderWindow_drawSprite(arg->window,
        game_menu->command_list_sprite, NULL);
    }
    return (0);
}

//printf("x = %d, y = %d\n", mouse_pos.x, mouse_pos.y);
//gm_save_game(arg, intro, game_menu);
//handle_save();
//gm_reload();
//equipement;
//characteristics;
