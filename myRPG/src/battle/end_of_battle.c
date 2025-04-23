/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** end_of_battle.c
*/

#include "struct.h"
#include "init.h"
#include "display.h"
#include "my.h"
#include "utils.h"
#include "battle.h"

int check_pokemon_hp_inventory(arg_t *arg)
{
    for (int i = 0; arg->inventory->pokemons[i] != NULL; i++) {
        if (arg->inventory->pokemons[i]->hp > 0)
            return 0;
    }
    return 1;
}

static int check_life_pokemon_master(arg_t *arg, pokemon_t **p)
{
    for (int i = 0; i < 4; i++) {
        if (p[arg->battle->num_pokemon]->hp <= 0 && i < 3) {
            arg->battle->num_pokemon = i + 1;
        }
        if (p[i]->hp > 0)
            return 0;
    }
    return 1;
}

static int check_hp_pokemon(arg_t *arg, int check)
{
    pokemon_t **p = select_pok(arg);
    if (check_pokemon_hp_inventory(arg) == 1)
        return 1;
    if (check == 1 &&
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->hp > 0 &&
    p[arg->battle->num_pokemon]->hp > 0)
        return 0;
    if (check == 1 &&
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->hp <= 0 &&
    p[arg->battle->num_pokemon]->hp > 0) {
        choose_pokemon(arg);
        return 0;
    }
    if (arg->battle->in_battle_master == 1) {
        if (check_life_pokemon_master(arg, p) == 0)
            return 0;
    }
    return 1;
}

static int print_lose_win(arg_t *arg, text_t *text_end)
{
    if (arg->inventory->pokemons[arg->inventory->pokemon_choose]->hp <= 0) {
        text_end->str =
        "You lost, you hurry to go to the nearest pokemon \n\
        center to heal your pokemons there...\0";
        return 5;
    } else {
        if (arg->battle->in_battle_master == 1) {
            arg->inventory->money += 1000;
            add_exp_level(arg);
            text_end->str = "You won ! Your pokemon earned XP,\n \
            You just earned 1000 Poke dollars !\0";
        } else {
            arg->inventory->money += 200;
            add_exp_level(arg);
            text_end->str = "You won ! Your pokemon earned XP,\n \
            You just earned 200 Poke dollars !\0";
        }
    }
    return 1;
}

int end_of_battle(arg_t *arg, fight_t *fight)
{
    text_t *text_end = init_text((sfVector2f) {600, 850}, sfBlack, 35);
    int check = 0;
    if (arg->inventory->pokemons[arg->inventory->pokemon_choose] == NULL)
        return 1;
    for (int i = 0; arg->inventory->pokemons[i] != NULL; i++) {
        if (arg->inventory->pokemons[i]->hp > 0)
            check = 1;
    }
    if (check_hp_pokemon(arg, check) == 0)
        return 0;
    check = print_lose_win(arg, text_end);
    display_end_of_battle(arg, fight, text_end);
    if (arg->battle->in_battle_master == 1) {
        arg->battle->pokemon_maitre[arg->battle->num_pokemon]->hp =
        arg->battle->pokemon_maitre[arg->battle->num_pokemon]->save_hp;
    } else {
        arg->battle->all_pokemon[arg->battle->num_pokemon]->hp =
        arg->battle->all_pokemon[arg->battle->num_pokemon]->save_hp;
    }
    return check;
}
