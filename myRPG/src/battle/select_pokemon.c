/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** select_pokemon.c
*/

#include "struct.h"
#include <stdlib.h>

static int select_down(arg_t *arg, int *pressed, int i)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown &&
    arg->battle->battle_img[12]->pos.y == 300 && i > 1) {
        arg->battle->battle_img[12]->pos.y = 450;
        *pressed = 1;
        return 1;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown &&
    arg->battle->battle_img[12]->pos.y == 450 && i > 2) {
        arg->battle->battle_img[12]->pos.y = 600;
        *pressed = 1;
        return 1;
    }
    return 0;
}

static int select_up(arg_t *arg, int *pressed)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp &&
    arg->battle->battle_img[12]->pos.y == 600) {
        arg->battle->battle_img[12]->pos.y = 450;
        *pressed = 1;
        return 1;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp &&
    arg->battle->battle_img[12]->pos.y == 450) {
        arg->battle->battle_img[12]->pos.y = 300;
        *pressed = 1;
        return 1;
    }
    return 0;
}

void select_pokemon(arg_t *arg, int *pressed, int i)
{
    if (*pressed == 1 && arg->event.type != sfEvtKeyReleased )
        return;
    if (arg->event.type == sfEvtKeyReleased)
        *pressed = 0;
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyRight && i >= 3) {
        arg->battle->battle_img[12]->pos.x = 1000;
        *pressed = 1;
        return;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyLeft) {
        arg->battle->battle_img[12]->pos.x = 300;
        *pressed = 1;
        return;
    }
    if (select_down(arg, pressed, i) == 1)
        return;
    if (select_up(arg, pressed) == 1)
        return;
}

void battle_num_pokemon(arg_t *arg)
{
    arg->battle->num_pokemon = rand() % (arg->battle->nb_pokemons - 3) + 3;
    if (arg->battle->in_battle_master == 1)
        arg->battle->num_pokemon = 0;
}
