/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** options_pressed.c
*/

#include "struct.h"
#include "battle.h"
#include "display.h"

static int option1_pressed(arg_t *arg)
{
    if (arg->battle->battle_img[4]->pos.x == 1000 &&
    arg->battle->battle_img[4]->pos.y == 850) {
        arg->battle->battle_img[4]->pos.x = 560;
        arg->battle->battle_img[4]->pos.y = 850;
        return 0;
    }
    return 1;
}

static int option2_pressed(arg_t *arg)
{
    if (arg->battle->battle_img[4]->pos.x == 1000 &&
    arg->battle->battle_img[4]->pos.y == 915) {
        return 0;
    }
    return 1;
}

static int option3_pressed(arg_t *arg, fight_t *fight)
{
    if (arg->battle->battle_img[4]->pos.x == 1230 &&
    arg->battle->battle_img[4]->pos.y == 850) {
        if (display_bag(arg, fight) == 1)
            return 0;
    }
    return 1;
}

static int option4_pressed(arg_t *arg)
{
    if (arg->battle->battle_img[4]->pos.x == 1230 &&
    arg->battle->battle_img[4]->pos.y == 915) {
        return 1;
    }
    return 0;
}

int options_pressed(arg_t *arg, fight_t *fight)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        if (option1_pressed(arg) == 0) {
            display_select_attack(arg, fight);
            return 0;
        }
        if (option2_pressed(arg) == 0) {
            choose_pokemon(arg);
            return 2;
        }
        if (option3_pressed(arg, fight) == 0) {
            return 1;
        }
        if (arg->battle->in_battle_master == 1)
            return 2;
        if (option4_pressed(arg) == 1) {
            return 1;
        }
    }
    return 2;
}
