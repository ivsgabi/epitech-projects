/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** change_pokemon_combat.c
*/

#include "struct.h"

static void use_potion(arg_t *arg, int i)
{
    if (arg->inventory->use_potion == 1) {
        if (arg->inventory->pokemons[i]->hp + 20 <=
        arg->inventory->pokemons[i]->save_hp)
            arg->inventory->pokemons[i]->hp += 20;
        else {
            arg->inventory->pokemons[i]->hp =
            arg->inventory->pokemons[i]->save_hp;
        }
        arg->inventory->use_potion = 0;
    } else {
        arg->inventory->pokemon_choose = i;
        arg->replace_pokemon = 0;
    }
}

static int change_pokemon_part1(arg_t *arg)
{
    if (arg->battle->battle_img[12]->pos.y == 300.0 &&
    arg->battle->battle_img[12]->pos.x == 300.0 &&
    (arg->inventory->pokemons[0]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 0);
        return 1;
    }
    if (arg->battle->battle_img[12]->pos.y == 450.0 &&
    arg->battle->battle_img[12]->pos.x == 300.0 &&
    (arg->inventory->pokemons[1]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 1);
        return 1;
    }
    if (arg->battle->battle_img[12]->pos.y == 600.0 &&
    arg->battle->battle_img[12]->pos.x == 300.0 &&
    (arg->inventory->pokemons[2]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 2);
        return 1;
    }
    return 0;
}

static int change_pokemon_part2(arg_t *arg)
{
    if (arg->battle->battle_img[12]->pos.y == 300.0 &&
    arg->battle->battle_img[12]->pos.x == 1000.0 &&
    (arg->inventory->pokemons[3]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 3);
        return 1;
    }
    if (arg->battle->battle_img[12]->pos.y == 450.0 &&
    arg->battle->battle_img[12]->pos.x == 1000.0 &&
    (arg->inventory->pokemons[4]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 4);
        return 1;
    }
    if (arg->battle->battle_img[12]->pos.y == 600.0 &&
    arg->battle->battle_img[12]->pos.x == 1000.0 &&
    (arg->inventory->pokemons[5]->hp > 0 || arg->replace_pokemon == 1)) {
        use_potion(arg, 5);
        return 1;
    }
    return 0;
}

int change_pokemon_combat(arg_t *arg)
{
    if (change_pokemon_part1(arg) == 1)
        return 1;
    if (change_pokemon_part2(arg) == 1)
        return 1;
    return 0;
}
