/*
** EPITECH PROJECT, 2023
** init_struct_gm
** File description:
** initalisation game menu for myrpg
*/

#include "game_menu.h"

void init_command_list(game_menu_t *game_menu)
{
    game_menu->command_list_texture =
    sfTexture_createFromFile("intro_assets/command_list.jpg", NULL);
    game_menu->command_list_sprite = sfSprite_create();
    game_menu->command_list_scale = (sfVector2f) {1, 1};
    sfSprite_setTexture(game_menu->command_list_sprite,
    game_menu->command_list_texture, sfTrue);
    sfSprite_setScale(game_menu->command_list_sprite,
    game_menu->command_list_scale);
    game_menu->display_command_list = 0;
    game_menu->back_to_menu = 0;
}

void init_window_rect(game_menu_t *game_menu)
{
    sfColor sfTransBlack = sfColor_fromRGBA(0, 0, 0, 128);
    game_menu-> window_rect_size = (sfVector2f) {1920, 1080};
    game_menu-> window_rect_pos = (sfVector2f) {1, 1};
    game_menu-> window_rect_color = sfTransBlack;
    sfRectangleShape_setSize(game_menu->window_rect,
    game_menu->window_rect_size);
    sfRectangleShape_setPosition(game_menu->window_rect,
    game_menu->window_rect_pos);
    sfRectangleShape_setFillColor(game_menu->window_rect,
    game_menu->window_rect_color);
}

void init_game_menu(game_menu_t *game_menu)
{
    game_menu->game_menu_texture =
    sfTexture_createFromFile("intro_assets/game_menu.png", NULL);
    game_menu->game_menu_sprite = sfSprite_create();
    game_menu->game_menu_scale = (sfVector2f) {1.47, 1.47};
    game_menu->game_menu_pos = (sfVector2f) {-20, 0};
    game_menu->gm_status = 0 ? game_menu->gm_status == 1 : 0;
    sfSprite_setTexture(game_menu->game_menu_sprite,
    game_menu->game_menu_texture, sfTrue);
    sfSprite_setScale(game_menu->game_menu_sprite, game_menu->game_menu_scale);
    sfSprite_setPosition(game_menu->game_menu_sprite, game_menu->game_menu_pos);
    game_menu->window_rect = sfRectangleShape_create();
    init_window_rect(game_menu);
    init_command_list(game_menu);
}
