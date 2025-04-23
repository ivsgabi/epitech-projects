/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** attack_pressed.c
*/

#include "struct.h"

static int put_damage_wild(arg_t *arg, int i)
{
    pokemon_t **p;
    if (arg->battle->in_battle_master == 1)
        p = arg->battle->pokemon_maitre;
    else
        p = arg->battle->all_pokemon;
    if (arg->inventory->pokemons[arg->inventory->pokemon_choose] == NULL)
        return 0;
    int damage =
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->attack *
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->damage_attack[i]
    / 100;
    int hp = p[arg->battle->num_pokemon]->hp;
    int degat = hp - damage;
    if (degat < 0) {
        degat = 0;
    }
    p[arg->battle->num_pokemon]->hp = degat;
    arg->battle->battle_img[4]->pos.x = 1000;
    arg->battle->battle_img[4]->pos.y = 850;
    return 0;
}

int attack_pressed(arg_t *arg)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyEnter) {
        if (arg->battle->battle_img[4]->pos.x == 560 &&
        arg->battle->battle_img[4]->pos.y == 850)
            return put_damage_wild(arg, 0);
        if (arg->battle->battle_img[4]->pos.x == 560 &&
        arg->battle->battle_img[4]->pos.y == 910)
            return put_damage_wild(arg, 1);
        if (arg->battle->battle_img[4]->pos.x == 800 &&
        arg->battle->battle_img[4]->pos.y == 850)
            return put_damage_wild(arg, 2);
        if (arg->battle->battle_img[4]->pos.x == 800 &&
        arg->battle->battle_img[4]->pos.y == 910)
            return put_damage_wild(arg, 3);
    }
    return 2;
}
