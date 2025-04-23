/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** begin_game.c
*/

#include "struct.h"
#include "display.h"
#include "game_menu.h"
#include "intro_struct.h"
#include "my.h"
#include "init.h"
#include <stdlib.h>

static void animate_pnj_start(arg_t *arg, int *droite)
{
    if (*droite != 0) {
        arg->pnj[0]->img->rect.left += 64;
        if (arg->pnj[0]->img->rect.left >= 192) {
            arg->pnj[0]->img->rect.left = 64;
        }
    }
}

int event_begin_game(arg_t *arg)
{
    while (sfRenderWindow_pollEvent(arg->window, &arg->event)) {
        if (arg->event.type == sfEvtClosed ||
        (arg->event.type == sfEvtKeyPressed &&
        arg->event.key.code == sfKeyQ)) {
            sfRenderWindow_close(arg->window);
            return 1;
        }
    }
    return 0;
}

static int give_first_pokemon(arg_t *arg)
{
    sfVector2i mouse;
    choose_t *choose = malloc(sizeof(choose_t));
    init_choose(choose);
    while (sfRenderWindow_isOpen(arg->window)) {
        mouse = sfMouse_getPosition((sfWindow*) arg->window);
        if (event_begin_game(arg) == 1)
            break;
        sfRenderWindow_clear(arg->window, sfBlack);
        display_img(arg->map_img, arg->window);
        if (display_btn_bulbizarre(arg, choose, mouse) == 1)
            break;
        if (display_btn_salameche(arg, choose, mouse) == 1)
            break;
        if (display_btn_carapuce(arg, choose, mouse) == 1)
            break;
        sfRenderWindow_display(arg->window);
    }
    destroy_choose(choose);
    return 0;
}

static void end_of_walk(arg_t *arg, int *droite, int *start)
{
    if (*droite == 0) {
        give_first_pokemon(arg);
        arg->player->img->rect.top = 64;
        arg->pnj[0]->img->pos = (sfVector2f) {825.0f, 200.0f};
        arg->pnj[0]->img->rect.top = 0;
        sfClock_destroy(arg->pnj[0]->animation);
        arg->can_move = 1;
        *start = 1;
    }
}

void walk_png(arg_t *arg, int *bas, int *droite, int *start)
{
    sfTime time = sfClock_getElapsedTime(arg->pnj[0]->animation);
    if (time.microseconds / 100000 >= 1.0) {
        animate_pnj_start(arg, droite);
        if (*bas > 0) {
            arg->pnj[0]->img->pos.y += 5;
            arg->pnj[0]->img->rect.top = 0;
            *bas -= 1;
        }
        if (*droite > 0 && *bas == 0) {
            arg->pnj[0]->img->rect.top = 128;
            arg->pnj[0]->img->pos.x += 5;
            *droite -= 1;
        }
        if (*droite != 0)
            sfClock_restart(arg->pnj[0]->animation);
        end_of_walk(arg, droite, start);
    }
}
