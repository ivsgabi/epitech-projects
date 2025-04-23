/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** change_pos_btn.c
*/

#include "struct.h"

static int first_i(arg_t *arg, int i)
{
    if (i == 0) {
        arg->battle->battle_img[11]->pos.x = 300.0;
        arg->battle->battle_img[11]->pos.y = 300.0;
        return 1;
    }
    if (i == 1) {
        arg->battle->battle_img[11]->pos.x = 300.0;
        arg->battle->battle_img[11]->pos.y = 450.0;
        return 1;
    }
    if (i == 2) {
        arg->battle->battle_img[11]->pos.x = 300.0;
        arg->battle->battle_img[11]->pos.y = 600.0;
        return 1;
    }
    return 0;
}

void change_pos_btn(arg_t *arg, int i)
{
    if (first_i(arg, i) == 1)
        return;
    if (i == 3) {
        arg->battle->battle_img[11]->pos.x = 1000.0;
        arg->battle->battle_img[11]->pos.y = 300.0;
        return;
    }
    if (i == 4) {
        arg->battle->battle_img[11]->pos.x = 1000.0;
        arg->battle->battle_img[11]->pos.y = 450.0;
        return;
    }
    if (i == 5) {
        arg->battle->battle_img[11]->pos.x = 1000.0;
        arg->battle->battle_img[11]->pos.y = 600.0;
        return;
    }
}
