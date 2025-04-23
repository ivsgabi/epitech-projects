/*
** EPITECH PROJECT, 2023
** init_struct_save
** File description:
** initialisation of struct to save game in myrpg
*/

#include "struct.h"
#include "game_menu.h"
#include "intro_struct.h"
#include "save.h"

int init_save_struct(arg_t *arg, save_game_t *save)
{
    save->player_pos_to_save = arg->player->pos;
    save->map_pos_to_save = arg->map_img->rect;
    save->player_texture_to_save = arg->player->img->texture;
    save->player_sprite_to_save = arg->player->img->sprite;
}
// for now
