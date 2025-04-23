/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** choose_pokemon.c
*/

#include "struct.h"
#include "display.h"
#include "battle.h"

static int pressed_pokemon_button(arg_t *arg, int nb, int *pressed)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        while (arg->event.type != sfEvtKeyReleased) {
            sfRenderWindow_pollEvent(arg->window, &arg->event);
            sfRenderWindow_clear(arg->window, sfBlack);
            display_img(arg->battle->battle_img[10], arg->window);
            display_all_btn(arg, nb);
            select_pokemon(arg, pressed, nb);
            sfSprite_setPosition(arg->battle->battle_img[13]->sprite,
            arg->battle->battle_img[12]->pos);
            sfRenderWindow_drawSprite(arg->window,
            arg->battle->battle_img[13]->sprite, NULL);
            sfRenderWindow_display(arg->window);
        }
        return 1;
    }
    return 0;
}

static int pressed_select(arg_t *arg, int *pressed, int nb)
{
    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_pollEvent(arg->window, &arg->event);
        sfRenderWindow_clear(arg->window, sfBlack);
        display_img(arg->battle->battle_img[10], arg->window);
        display_all_btn(arg, nb);
        if (pressed_pokemon_button(arg, nb, pressed) == 1 &&
        change_pokemon_combat(arg) == 1) {
            return 1;
        }
        select_pokemon(arg, pressed, nb);
        display_img(arg->battle->battle_img[12], arg->window);
        sfRenderWindow_display(arg->window);
    }
    return 0;
}

static int check_pressed(arg_t *arg, int *pressed, int nb)
{
    if (pressed_select(arg, pressed, nb) == 1)
        return 1;
    return 0;
}

void choose_pokemon(arg_t *arg)
{
    int nb = 0;
    int pressed = 0;

    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_pollEvent(arg->window, &arg->event);
        sfRenderWindow_clear(arg->window, sfBlack);
        display_img(arg->battle->battle_img[10], arg->window);
        for (; arg->inventory->pokemons[nb] != NULL; nb++);
        display_all_btn(arg, nb);
        if (check_pressed(arg, &pressed, nb) == 1)
            return;
        select_pokemon(arg, &pressed, nb);
        display_img(arg->battle->battle_img[12], arg->window);
        sfRenderWindow_display(arg->window);
    }
}
