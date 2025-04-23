/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** free_pokemon.c
*/

#include "struct.h"
#include "free.h"
#include <stdlib.h>

void free_pokemon(pokemon_t *pokemon)
{
    free(pokemon->name);
    free(pokemon->type);
    destroy_img(pokemon->f1);
    destroy_img(pokemon->f2);
    destroy_img(pokemon->dos_f1);
    destroy_img(pokemon->dos_f2);
    free(pokemon);
}

void free_all_pokemons(pokemon_t **pokemons)
{
    for (int i = 0; pokemons[i] != NULL; i++) {
        free_pokemon(pokemons[i]);
    }
    free(pokemons);
}

void free_inventory(inventory_t *inventory)
{
    free_all_pokemons(inventory->pokemons);
    destroy_text(inventory->text);
    free(inventory);
}

void free_pnj(player_t **pnj)
{
    for (int i = 0; pnj[i] != NULL; i++) {
        free_player(pnj[i]);
    }
    free(pnj);
}

void free_player(player_t *player)
{
    destroy_img(player->img);
    free(player);
}
