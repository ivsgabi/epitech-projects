/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** switch_pokemon.c
*/

#include "display.h"
#include "struct.h"

static void switch_pok(pokemon_t **pok1, pokemon_t **pok2)
{
    pokemon_t *tmp = *pok1;
    *pok1 = *pok2;
    *pok2 = tmp;
}

void check_pos_mouse(arg_t *arg, int nb)
{
    sfVector2i mouse = sfMouse_getPosition((sfWindow *) arg->window);
    if (mouse.x >= 270 && mouse.x <= 300 && mouse.y >= 350 &&
    mouse.y <= 380 && nb >= 2)
        switch_pok(&arg->inventory->pokemons[0], &arg->inventory->pokemons[1]);
    if (mouse.x >= 270 && mouse.x <= 300 && mouse.y >= 500 &&
    mouse.y <= 530 && nb >= 3)
        switch_pok(&arg->inventory->pokemons[1], &arg->inventory->pokemons[2]);
    if (mouse.x >= 270 && mouse.x <= 300 && mouse.y >= 650 &&
    mouse.y <= 680 && nb >= 4)
        switch_pok(&arg->inventory->pokemons[2], &arg->inventory->pokemons[3]);
    if (mouse.x >= 970 && mouse.x <= 1000 && mouse.y >= 350 &&
    mouse.y <= 380 && nb >= 5)
        switch_pok(&arg->inventory->pokemons[3], &arg->inventory->pokemons[4]);
    if (mouse.x >= 970 && mouse.x <= 1000 && mouse.y >= 500 &&
    mouse.y <= 530 && nb >= 6)
        switch_pok(&arg->inventory->pokemons[4], &arg->inventory->pokemons[5]);
}

sfMusic *music_start_fight(arg_t *arg)
{
    sfMusic *battle = sfMusic_createFromFile("assets/battle.ogg");
    sfMusic_setVolume(battle, *arg->music_volume);
    sfMusic_play(battle);
    sfMusic_setLoop(battle, sfTrue);
    return battle;
}

void end_music_fight(arg_t *arg, sfMusic *battle)
{
    sfMusic_stop(battle);
    sfMusic_destroy(battle);
    sfMusic_setVolume(arg->music, *arg->music_volume);
    arg->battle->in_battle_master = 0;
}

void display_start_battle_elt(arg_t *arg, fight_t *fight)
{
    display_background_battle(arg, fight);
    display_battle_options(arg, fight);
    display_elt_battle(arg, fight);
}
