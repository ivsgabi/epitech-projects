/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** all_mvt.c
*/

#include "move_player.h"
#include "my.h"
#include <stdlib.h>

void animate_player(arg_t *arg)
{
    sfTime time = sfClock_getElapsedTime(arg->player->animation);
    if (time.microseconds / 100000 >= 1.0 &&
    arg->event.type == sfEvtKeyPressed && (arg->event.key.code == sfKeyDown ||
    arg->event.key.code == sfKeyUp || arg->event.key.code == sfKeyRight ||
    arg->event.key.code == sfKeyLeft)) {
        arg->player->img->rect.left += 64;
        if (arg->player->img->rect.left >= 192) {
            arg->player->img->rect.left = 64;
        }
        sfClock_restart(arg->player->animation);
    }
    if (arg->event.type == sfEvtKeyReleased) {
        arg->player->img->rect.left = 0;
    }
}

int move_player(arg_t *arg)
{
    animate_player(arg);
    move_player_up(arg);
    move_player_down(arg);
    move_player_left(arg);
    move_player_right(arg);
    return random_fight_pokemon(arg);
}
