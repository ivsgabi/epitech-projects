/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** capture_pokemon.c
*/

#include "struct.h"
#include "stdlib.h"
#include <stdio.h>
#include "display.h"
#include "init.h"
#include "battle.h"
#include "my.h"

static void replace_pokemon(arg_t *arg, fight_t *fight)
{
    arg->inventory->pokeballs -= 1;
    arg->replace_pokemon = 1;
    choose_pokemon(arg);
    add_pokemon_to_inventory(arg, arg->inventory->pokemon_choose,
    arg->battle->all_pokemon[arg->battle->num_pokemon]);
    arg->battle->all_pokemon[arg->battle->num_pokemon]->hp =
    arg->battle->all_pokemon[arg->battle->num_pokemon]->save_hp;
    display_succeed_capture(arg, fight);
    return;
}

static void fill_attack_names(arg_t *arg, int i, pokemon_t *pokemon_to_add)
{
    for (int j = 0; j < 4; j++) {
        arg->inventory->pokemons[i]->attack_names[j] =
        pokemon_to_add->attack_names[j];
        arg->inventory->pokemons[i]->damage_attack[j] =
        pokemon_to_add->damage_attack[j];
    }
}

void add_pokemon_to_inventory(arg_t *arg, int i, pokemon_t *pokemon_to_add)
{
    arg->inventory->pokemons[i] = malloc(sizeof(pokemon_t));
    if (arg->inventory->pokemons[i] == NULL)
        return;
    arg->inventory->pokemons[i]->attack = pokemon_to_add->attack;
    arg->inventory->pokemons[i]->def = pokemon_to_add->def;
    arg->inventory->pokemons[i]->hp = pokemon_to_add->hp;
    arg->inventory->pokemons[i]->save_hp = pokemon_to_add->save_hp;
    arg->inventory->pokemons[i]->name = pokemon_to_add->name;
    arg->inventory->pokemons[i]->speed = pokemon_to_add->speed;
    arg->inventory->pokemons[i]->type = pokemon_to_add->type;
    arg->inventory->pokemons[i]->f1 = pokemon_to_add->f1;
    arg->inventory->pokemons[i]->f2 = pokemon_to_add->f2;
    arg->inventory->pokemons[i]->dos_f1 = pokemon_to_add->dos_f1;
    arg->inventory->pokemons[i]->dos_f2 = pokemon_to_add->dos_f2;
    arg->inventory->pokemons[i]->exp = pokemon_to_add->exp;
    arg->inventory->pokemons[i]->level = pokemon_to_add->level;
    fill_attack_names(arg, i, pokemon_to_add);
}

int capture_pokemon(arg_t *arg, fight_t *fight)
{
    int i;
    if (arg->inventory->pokeballs == 0)
        return 0;
    if (arg->battle->in_battle_master == 1 ||
    arg->battle->all_pokemon[arg->battle->num_pokemon]->hp > 20) {
        display_fail_capture(arg, fight);
        return 0;
    }
    for (i = 0; arg->inventory->pokemons[i] != NULL && i < 6; i++);
    if (i == 6) {
        replace_pokemon(arg, fight);
        return 1;
    }
    add_pokemon_to_inventory(arg, i,
    arg->battle->all_pokemon[arg->battle->num_pokemon]);
    arg->inventory->pokeballs -= 1;
    arg->battle->all_pokemon[arg->battle->num_pokemon]->hp =
    arg->battle->all_pokemon[arg->battle->num_pokemon]->save_hp;
    display_succeed_capture(arg, fight);
    return 1;
}
