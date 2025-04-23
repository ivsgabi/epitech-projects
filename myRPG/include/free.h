/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** free.h
*/

#ifndef FREE_H
    #define FREE_H

    #include "struct.h"

void free_array(char **arr);
void free_pokemon(pokemon_t *pokemon);
void free_all_pokemons(pokemon_t **pokemons);
void free_inventory(inventory_t *inventory);
void free_pnj(player_t **pnj);
void destroy_img(img_t *img);
void destroy_text(text_t *text);
void destroy_all_texts(text_t **texts);
void destroy_all_img(img_t **imgs);
void free_battle(battle_t *battle);
void free_player(player_t *player);
void free_arg(arg_t *arg);
void free_all(arg_t *arg);

#endif /* FREE_H */
