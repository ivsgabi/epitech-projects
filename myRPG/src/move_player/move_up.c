/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** move_up.c
*/

#include "struct.h"
#include "move_player.h"

void animate_player_up(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp) {
        arg->player->img->rect.top = 192;
    }
}

void move_player_up(arg_t *arg)
{
    animate_player_up(arg);
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp && arg->player->pos.y - 1 >= 0 &&
    arg->map[arg->player->pos.y - 1][arg->player->pos.x] != '#') {
        arg->player->pos.y -= 1;
        if (arg->can_move == 2)
            arg->player->img->pos.y -= 5;
        else {
            arg->map_img->rect.top -= 5;
            move_pnj(arg->pnj, arg->obj_3d, 0, 9);
        }
    }
}
