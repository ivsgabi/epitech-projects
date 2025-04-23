/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_bag.c
*/

#include "struct.h"
#include "battle.h"
#include "my.h"
#include "display.h"

static int choose_obj(arg_t *arg, fight_t *fight)
{
    if (arg->battle->battle_img[4]->pos.y == 360.0) {
        if (capture_pokemon(arg, fight) == 1)
            return 2;
    }
    if (arg->battle->battle_img[4]->pos.y == 430.0) {
        if (arg->inventory->potions > 0) {
            arg->inventory->use_potion = 1;
            choose_pokemon(arg);
            arg->inventory->potions -= 1;
        }
        return 0;
    }
    return 1;
}

int potion_pokeball(arg_t *arg, fight_t *fight)
{
    int check = 0;
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        check = choose_obj(arg, fight);
        if (check == 2)
            return 2;
        if (check == 0)
            return 0;
        return 1;
    }
    return 0;
}

int display_bag(arg_t *arg, fight_t *fight)
{
    arg->battle->battle_img[4]->pos.x = 920.0;
    arg->battle->battle_img[4]->pos.y = 360.0;
    arg->inventory->text->str = "A device for catching\nwild Pokemon.";
    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_clear(arg->window, sfBlack);
        display_background_battle(arg, fight);
        display_battle_options(arg, fight);
        display_elt_battle(arg, fight);
        display_inventary(arg);
        if (select_inventory(arg) == 1)
            return 0;
        int check = potion_pokeball(arg, fight);
        if (check == 1)
            return 0;
        if (check == 2)
            return 1;
        sfRenderWindow_display(arg->window);
    }
    return 0;
}
