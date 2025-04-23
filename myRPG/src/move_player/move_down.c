/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** move_down.c
*/

#include "struct.h"

void animate_player_down(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown) {
        arg->player->img->rect.top = 0;
    }
}

void move_pnj(player_t **pnj, img_t **obj_3d, int x, int y)
{
    for (int i = 0; pnj[i] != NULL; i++) {
        pnj[i]->img->pos.x += x;
        pnj[i]->img->pos.y += y;
    }
    for (int i = 0; obj_3d[i] != NULL; i++) {
        obj_3d[i]->pos.x += x;
        obj_3d[i]->pos.y += y;
    }
}

void move_player_down(arg_t *arg)
{
    animate_player_down(arg);
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown &&
    arg->map[arg->player->pos.y + 1] != NULL &&
    arg->map[arg->player->pos.y + 1][arg->player->pos.x] != '#') {
        arg->player->pos.y += 1;
        if (arg->can_move == 2)
            arg->player->img->pos.y += 5;
        else {
            arg->map_img->rect.top += 5;
            move_pnj(arg->pnj, arg->obj_3d, 0, -9);
        }
    }
}
