/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** shop.c
*/

#include "struct.h"
#include "my.h"
#include "battle.h"
#include "init.h"
#include "utils.h"

void manage_f1(fight_t *fight)
{
    sfTime time = sfClock_getElapsedTime(fight->clock);
    if (time.microseconds / 100000 >= 3.0 && fight->f1 == 0) {
        sfClock_restart(fight->clock);
        fight->f1 = 1;
    } else {
        check_time(fight, time);
    }
}

void heal_pokemon(pokemon_t **pokemons, arg_t *arg)
{
    sfMusic_setVolume(arg->music, 0);
    sfMusic *heal = sfMusic_createFromFile("assets/center.ogg");
    sfMusic_setVolume(heal, *arg->music_volume * 10);
    sfClock *clock = sfClock_create();
    sfMusic_play(heal);
    while (sfClock_getElapsedTime(clock).microseconds / 100000 < 50.0);
    sfMusic_stop(heal);
    sfMusic_destroy(heal);
    sfClock_destroy(clock);
    for (int i = 0; pokemons[i] != NULL; i++) {
        pokemons[i]->hp = pokemons[i]->save_hp;
    }
    sfMusic_setVolume(arg->music, *arg->music_volume);
}

int buy_potion_pokeball(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        arg->inventory->money -= 200;
        if (arg->battle->battle_img[4]->pos.y == 360.0) {
            arg->inventory->pokeballs += 1;
        }
        if (arg->battle->battle_img[4]->pos.y == 430.0) {
            arg->inventory->potions += 1;
        }
    }
    return 0;
}

void shop(arg_t *arg)
{
    arg->battle->battle_img[4]->pos.x = 920.0;
    arg->battle->battle_img[4]->pos.y = 360.0;
    arg->inventory->text->str = "A device for catching\nwild Pokemon.";
    text_t *text = init_text((sfVector2f) {1280.0, 780.0}, sfBlack, 35);
    sfView_zoom(arg->view, 2.0f);
    sfRenderWindow_setView(arg->window, arg->view);
    while (sfRenderWindow_isOpen(arg->window)) {
        sfRenderWindow_clear(arg->window, sfBlack);
        display_all_img(arg, arg->window);
        sfRenderWindow_setView(arg->window, arg->view);
        display_img(arg->battle->battle_img[19], arg->window);
        if (select_inventory(arg) == 1)
            break;
        buy_potion_pokeball(arg);
        text->str = my_itoa(arg->inventory->money);
        display_text(arg, text);
        sfRenderWindow_display(arg->window);
    }
    sfView_zoom(arg->view, 0.5f);
    sfRenderWindow_setView(arg->window, arg->view);
}
