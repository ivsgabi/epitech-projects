/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** manage_options.c
*/

#include "struct.h"
#include "battle.h"
#include "display.h"
#include "my.h"

static void select_options(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyRight) {
        arg->battle->battle_img[4]->pos.x = 1230;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyLeft) {
        arg->battle->battle_img[4]->pos.x = 1000;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp) {
        arg->battle->battle_img[4]->pos.y = 850;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown) {
        arg->battle->battle_img[4]->pos.y = 915;
    }
}

void select_attack(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyRight) {
        arg->battle->battle_img[4]->pos.x = 800;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyLeft) {
        arg->battle->battle_img[4]->pos.x = 560;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyUp) {
        arg->battle->battle_img[4]->pos.y = 850;
    }
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyDown) {
        arg->battle->battle_img[4]->pos.y = 910;
    }
}

int manage_fight(arg_t *arg, fight_t *fight)
{
    select_options(arg);
    int check = options_pressed(arg, fight);
    if (check == 1)
        return 1;
    if (check == 0) {
        check = end_of_battle(arg, fight);
        if (check != 0)
            return check;
        sfMusic *attack = sfMusic_createFromFile("assets/attack.ogg");
        sfMusic_setVolume(attack, *arg->music_volume);
        sfMusic_play(attack);
        check = wild_pokemon_attack(arg, fight);
        if (check != 0)
            return check;
        sfMusic_stop(attack);
        sfMusic_destroy(attack);
        check = end_of_battle(arg, fight);
        return check;
    }
    return 2;
}

int manage_options(arg_t *arg, fight_t *fight)
{
    int check = 0;
    while (sfRenderWindow_pollEvent(arg->window, &arg->event)) {
        check = manage_fight(arg, fight);
        if (check == 1)
            return 1;
        if (check == 0)
            return 0;
        if (check == 5)
            return 5;
    }
    return 0;
}
