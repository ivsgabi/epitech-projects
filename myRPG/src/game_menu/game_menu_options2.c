/*
** EPITECH PROJECT, 2023
** back_to_main_menu_button
** File description:
** for myrpg game_menu
*/

#include "struct.h"
#include "game_menu.h"
#include "intro_struct.h"
#include "display.h"

void handle_command_list_displaying(arg_t *arg, intro_t *intro,
game_menu_t *game_menu)
{
    intro->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 1580 && intro->mouse_pos.x <= 1735
    && intro->mouse_pos.y >= 230 && intro->mouse_pos.y <= 265) {
        game_menu->display_command_list = 1;
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 293 && intro->mouse_pos.x <= 400
    && intro->mouse_pos.y >= 160 && intro->mouse_pos.y <= 265) {
        game_menu->display_command_list = 0;
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 667 && intro->mouse_pos.x <= 1106
    && intro->mouse_pos.y >= 248 && intro->mouse_pos.y <= 338) {
        display_all_pokemon(arg);
    }

}

int back_to_main_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music)
{
    arg->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && arg->mouse_pos.x >= 1380 && arg->mouse_pos.x <= 1606
    && arg->mouse_pos.y >= 175 && arg->mouse_pos.y <= 210) {
        intro->status = 0;
        intro->in_menu_status = 1;
        intro->in_game_status = 0;
        intro->in_intro_status = 0;
        intro->dropdown_status = 0;
        intro->is_clicked = 0;
        return (BACK_TO_MENU);
    }
    return (0);
}
