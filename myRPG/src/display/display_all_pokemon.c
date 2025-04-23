/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** dispay_all_pokemon.c
*/

#include "struct.h"
#include "display.h"
#include "my.h"

static int first_i_order(arg_t *arg, int i)
{
    if (i == 0) {
        arg->battle->battle_img[4]->pos.x = 300.0;
        arg->battle->battle_img[4]->pos.y = 350.0;
        return 1;
    }
    if (i == 1) {
        arg->battle->battle_img[4]->pos.x = 300.0;
        arg->battle->battle_img[4]->pos.y = 500.0;
        return 1;
    }
    if (i == 2) {
        arg->battle->battle_img[4]->pos.x = 300.0;
        arg->battle->battle_img[4]->pos.y = 650.0;
        return 1;
    }
    return 0;
}

void change_pos_fleche(arg_t *arg, int i)
{
    if (first_i_order(arg, i) == 1)
        return;
    if (i == 3) {
        arg->battle->battle_img[4]->pos.x = 1000.0;
        arg->battle->battle_img[4]->pos.y = 350.0;
        return;
    }
    if (i == 4) {
        arg->battle->battle_img[4]->pos.x = 1000.0;
        arg->battle->battle_img[4]->pos.y = 500.0;
        return;
    }
    if (i == 5) {
        arg->battle->battle_img[4]->pos.x = 1000.0;
        arg->battle->battle_img[4]->pos.y = 650.0;
        return;
    }
}

static int event_change_pokemon_order(arg_t *arg, int nb)
{
    sfVector2i mouse = sfMouse_getPosition((sfWindow *) arg->window);

    while (sfRenderWindow_pollEvent(arg->window, &arg->event)) {
        if (arg->event.type == sfEvtMouseButtonPressed &&
        mouse.x >= 100 && mouse.x <= 236 && mouse.y >= 100 && mouse.y <= 240)
            return 1;
        if (arg->event.type == sfEvtMouseButtonPressed) {
            check_pos_mouse(arg, nb);
        }
    }
    return 0;
}

void display_all_pokemon(arg_t *arg)
{
    int nb = 0;
    sfSprite_rotate(arg->battle->battle_img[4]->sprite, 90.0);

    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_clear(arg->window, sfBlack);
        display_img(arg->battle->battle_img[10], arg->window);
        for (; arg->inventory->pokemons[nb] != NULL; nb++);
        display_all_btn(arg, nb);
        if (event_change_pokemon_order(arg, nb) == 1)
            break;
        for (int i = 0; i < nb - 1; i++) {
            change_pos_fleche(arg, i);
            display_img(arg->battle->battle_img[4], arg->window);
        }
        display_img(arg->battle->battle_img[16], arg->window);
        sfRenderWindow_display(arg->window);
    }
    sfSprite_rotate(arg->battle->battle_img[4]->sprite, -90.0);
}
