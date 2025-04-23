/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** move_right.c
*/

#include "struct.h"
#include "move_player.h"

void animate_player_right(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyRight) {
        arg->player->img->rect.top = 128;
    }
}

void move_player_right(arg_t *arg)
{
    animate_player_right(arg);
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyRight &&
    arg->map[arg->player->pos.y][arg->player->pos.x + 1] != '\0' &&
    arg->map[arg->player->pos.y][arg->player->pos.x + 1] != '#') {
        arg->player->pos.x += 1;
        if (arg->can_move == 2)
            arg->player->img->pos.x += 5;
        else {
            arg->map_img->rect.left += 5;
            move_pnj(arg->pnj, arg->obj_3d, -10, 0);
        }
    }
}
