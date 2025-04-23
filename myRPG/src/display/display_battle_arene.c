/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_battle_arene.c
*/

#include "struct.h"
#include "display.h"

static void display_barre_dresseur_enemy(arg_t *arg)
{
    for (int i = 0; i < 4; i++) {
        arg->battle->battle_img[7]->pos.y = 300;
        (i == 0) ? arg->battle->battle_img[7]->pos.x = 580 : 0;
        (i == 1) ? arg->battle->battle_img[7]->pos.x = 610 : 0;
        (i == 2) ? arg->battle->battle_img[7]->pos.x = 640 : 0;
        (i == 3) ? arg->battle->battle_img[7]->pos.x = 670 : 0;
        arg->battle->battle_img[7]->rect.left = 0;
        if (arg->battle->pokemon_maitre[i]->hp <= 0)
            arg->battle->battle_img[7]->rect.left = 10;
        display_img(arg->battle->battle_img[7], arg->window);
    }
}

static void display_barre_dresseur(arg_t *arg)
{
    for (int i = 0; arg->inventory->pokemons[i] != NULL; i++) {
        arg->battle->battle_img[7]->pos.y = 650;
        (i == 0) ? arg->battle->battle_img[7]->pos.x = 1150 : 0;
        (i == 1) ? arg->battle->battle_img[7]->pos.x = 1180 : 0;
        (i == 2) ? arg->battle->battle_img[7]->pos.x = 1210 : 0;
        (i == 3) ? arg->battle->battle_img[7]->pos.x = 1230 : 0;
        (i == 4) ? arg->battle->battle_img[7]->pos.x = 1260 : 0;
        (i == 5) ? arg->battle->battle_img[7]->pos.x = 1290 : 0;
        arg->battle->battle_img[7]->rect.left = 0;
        if (arg->inventory->pokemons[i]->hp <= 0)
            arg->battle->battle_img[7]->rect.left = 10;
        display_img(arg->battle->battle_img[7], arg->window);
    }
}

void display_battle_arene(arg_t *arg)
{
    if (arg->battle->in_battle_master == 1) {
        display_img(arg->battle->battle_img[18], arg->window);
        arg->battle->battle_img[2]->pos.x = 500;
        arg->battle->battle_img[2]->pos.y = 300;
        display_img(arg->battle->battle_img[2], arg->window);
        sfSprite_setScale(arg->battle->battle_img[7]->sprite,
        (sfVector2f){3.0, 3.0});
        display_barre_dresseur_enemy(arg);
        arg->battle->battle_img[2]->pos.x = 1070;
        arg->battle->battle_img[2]->pos.y = 650;
        display_img(arg->battle->battle_img[2], arg->window);
        display_barre_dresseur(arg);
        display_img(arg->battle->battle_img[7], arg->window);
        sfSprite_setScale(arg->battle->battle_img[7]->sprite,
        (sfVector2f){5.0, 5.0});
    }
}

void display_end_of_battle(arg_t *arg, fight_t *fight, text_t *text_end)
{
    sfClock *sleep_clock = sfClock_create();

    while (sfClock_getElapsedTime(sleep_clock).microseconds / 100000 < 30.0) {
        display_background_battle(arg, fight);
        display_battle_options(arg, fight);
        display_elt_battle(arg, fight);
        display_text(arg, fight->life);
        display_img(arg->battle->battle_img[8], arg->window);
        display_text(arg, text_end);
        sfRenderWindow_display(arg->window);
    }
    sfClock_destroy(sleep_clock);
}
