/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** fight.c
*/

#include <stdlib.h>

#include "struct.h"
#include "battle.h"
#include "display.h"
#include "my.h"

void check_time(fight_t *fight, sfTime time)
{
    if (time.microseconds / 100000 >= 3.0 && fight->f1 == 1) {
        sfClock_restart(fight->clock);
        fight->f1 = 0;
    }
}

void display_intro(arg_t *arg)
{
    sfMusic_setVolume(arg->music, 0);
    sfClock *clock = sfClock_create();
    sfClock *animation = sfClock_create();
    arg->battle->battle_img[9]->rect.left = 0;
    sfMusic *start = sfMusic_createFromFile("assets/start.ogg");
    sfMusic_setVolume(start, *arg->music_volume);
    sfMusic_play(start);
    while (sfClock_getElapsedTime(clock).microseconds / 100000 < 30.0) {
        display_img(arg->battle->battle_img[9], arg->window);
        if (sfClock_getElapsedTime(animation).microseconds >= 1.0) {
            arg->battle->battle_img[9]->rect.left += 10;
            sfClock_restart(animation);
        }
        sfRenderWindow_display(arg->window);
    }
    sfMusic_stop(start);
    sfMusic_destroy(start);
}

int start_random_fight(arg_t *arg, sfTime time)
{
    if ((time.microseconds / 1000000) >= arg->battle->random_nb) {
        display_intro(arg);
        if (start_fight(arg) == 5) {
            arg->battle->pokemon_found = 0;
            return 5;
        }
        arg->battle->pokemon_found = 0;
    }
    return 0;
}

int random_fight_pokemon(arg_t *arg)
{
    sfTime time = sfClock_getElapsedTime(arg->battle->pop_pokemon);
    if (arg->map[arg->player->pos.y][arg->player->pos.x] == 'h') {
        if (arg->battle->pokemon_found == 0) {
            arg->battle->random_nb = rand() % (5 - 1) + 1;
            sfClock_restart(arg->battle->pop_pokemon);
            arg->battle->pokemon_found = 1; return 0;
        }
        if (start_random_fight(arg, time) == 5)
            return 5;
        if (arg->event.type == sfEvtClosed ||
        (arg->event.type == sfEvtKeyPressed &&
        arg->event.key.code == sfKeyQ)) {
            sfRenderWindow_close(arg->window);
            return 1;
        }
    }
    return 0;
}
