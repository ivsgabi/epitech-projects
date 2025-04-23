/*
** EPITECH PROJECT, 2023
** handle_game_menu
** File description:
** for myrpg
*/

#include <stdlib.h>
#include "struct.h"
#include "game_menu.h"
#include "intro_struct.h"
#include "init.h"
#include "display.h"

int when_display_game_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    if (intro->in_game_status != 0
    && arg->event.type == sfEvtKeyPressed
    && arg->event.key.code == sfKeyEscape && arg->can_move != 2) {
        if (game_menu->gm_status == 0) {
            game_menu->gm_status = 1;
            arg->can_move = 0;
        } else {
            game_menu->gm_status = 0;
            arg->can_move = 1;
        }
    } return (0);
}

static void key_event_inventory(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp) {
        arg->battle->battle_img[4]->pos.y = 360.0;
        arg->inventory->text->str = "A device for catching\nwild Pokemon.";
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown) {
        arg->battle->battle_img[4]->pos.y = 430;
        arg->inventory->text->str = "Heal 20 HP of 1\nof your Pokemon.";
    }
}

int select_inventory(arg_t *arg)
{
    sfRenderWindow_pollEvent(arg->window, &arg->event);
    key_event_inventory(arg);
    if (arg->inventory->text->str[0] == 'H') {
        display_img(arg->battle->battle_img[15], arg->window);
    } else {
        arg->battle->battle_img[7]->pos = (sfVector2f) {530.0, 560.0};
        display_img(arg->battle->battle_img[7], arg->window);
    }
    display_text(arg, arg->inventory->text);
    display_img(arg->battle->battle_img[4], arg->window);
    sfVector2i mouse_pos = sfMouse_getPosition((sfWindow *)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && mouse_pos.x >= 440 && mouse_pos.x <= 544
    && mouse_pos.y >= 843 && mouse_pos.y <= 945) {
        arg->inventory->display_inventory = 0;
        arg->battle->battle_img[4]->pos.x = 1000;
        arg->battle->battle_img[4]->pos.y = 850;
        return 1;
    }
    return 0;
}

int handle_game_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music)
{
    if (game_menu->gm_status == 1) {
        sfRenderWindow_drawRectangleShape(arg->window,
        game_menu->window_rect, NULL);
        sfRenderWindow_drawSprite(arg->window,
        game_menu->game_menu_sprite, NULL);
        if (game_menu_options(arg, intro, game_menu, music) == BACK_TO_MENU)
            return (BACK_TO_MENU);
        game_menu_options(arg, intro, game_menu, music);
        if (arg->inventory->display_inventory == 1) {
            display_inventary(arg);
            select_inventory(arg);
        }
    }
    return (0);
}
