/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_inventory.c
*/

#include "struct.h"
#include "display.h"
#include "utils.h"
#include "init.h"

void display_inventary(arg_t *arg)
{
    display_img(arg->battle->battle_img[14], arg->window);
    text_t *text = init_text((sfVector2f) {1350.0, 355.0}, sfBlack, 40);
    text->str = my_itoa(arg->inventory->pokeballs);
    display_text(arg, text);
    text->pos = (sfVector2f) {1350.0, 425.0};
    text->str = my_itoa(arg->inventory->potions);
    display_text(arg, text);
    text->pos = (sfVector2f) {1280.0, 780.0};
    text->str = my_itoa(arg->inventory->money);
    display_text(arg, text);
}

void display_fail_capture(arg_t *arg, fight_t *fight)
{
    arg->battle->battle_img[4]->pos.x = 1000;
    arg->battle->battle_img[4]->pos.y = 850;
    sfClock *sleep_clock = sfClock_create();
    text_t *text = init_text((sfVector2f) {700, 850}, sfBlack, 35);
    text->str = "Oh no ! The Pokemon escaped...";

    while (sfClock_getElapsedTime(sleep_clock).microseconds / 100000 < 20.0) {
        display_background_battle(arg, fight);
        display_elt_battle(arg, fight);
        display_img(arg->battle->battle_img[8], arg->window);
        display_text(arg, text);
        sfRenderWindow_display(arg->window);
    }
    sfClock_destroy(sleep_clock);
}

void display_succeed_capture(arg_t *arg, fight_t *fight)
{
    sfClock *sleep_clock = sfClock_create();
    text_t *text = init_text((sfVector2f) {550, 850}, sfBlack, 35);
    text->str = "Congratulation, you caught a Pokemon !";

    while (sfClock_getElapsedTime(sleep_clock).microseconds / 100000 < 20.0) {
        display_background_battle(arg, fight);
        display_elt_battle(arg, fight);
        display_img(arg->battle->battle_img[8], arg->window);
        display_text(arg, text);
        sfRenderWindow_display(arg->window);
    }
    sfClock_destroy(sleep_clock);
}
