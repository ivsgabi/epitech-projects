/*
** EPITECH PROJECT, 2023
** header
** File description:
** for myrpg game_menu
*/

#include "intro_struct.h"
#include "struct.h"
#include "display.h"

#pragma once
#ifndef GAME_MEMU_H
    #define GAME_MENU_H
typedef struct game_menu_t {
    int gm_status;
    int back_to_menu;
    buttons_t *buttons;
    sfTexture *game_menu_texture;
    sfSprite *game_menu_sprite;
    sfVector2f game_menu_pos;
    sfVector2f game_menu_scale;

    sfRectangleShape* window_rect;
    sfVector2f window_rect_size;
    sfVector2f window_rect_pos;
    sfColor window_rect_color;

    sfTexture *command_list_texture;
    sfSprite *command_list_sprite;
    sfVector2f command_list_scale;
    int display_command_list;
} game_menu_t;

void init_game_menu(game_menu_t *game_menu);
int main_game(arg_t *arg, intro_t *intro, game_menu_t *game_menu, int start);
int display_window(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music);
int when_display_game_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu);
int handle_game_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music);
int game_menu_options(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music);
int back_to_main_menu(arg_t *arg, intro_t *intro, game_menu_t *game_menu,
sfMusic **music);
void handle_command_list_displaying(arg_t *arg, intro_t *intro,
game_menu_t *game_menu);
int pages_display_conditions(arg_t *arg, intro_t *intro, buttons_t *buttons,
game_menu_t *game_menu);
void save_party(arg_t *arg);
int resume_game(arg_t *arg);

#endif
