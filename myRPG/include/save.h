/*
** EPITECH PROJECT, 2023
** header
** File description:
** for savec in my_rpg
*/

#include <SFML/Graphics.h>

#ifndef SAVE_H
    #define SAVE_H
typedef struct save_game_s {
    sfVector2i player_pos_to_save;
    sfIntRect map_pos_to_save;
    sfTexture *player_texture_to_save;;
    sfSprite *player_sprite_to_save;
    char *gotten_pokemons_names_to_save;
    int *level_to_save;
    int *xp_to_save;
    int pnj_already_spoken_to;
} save_game_t;
#endif
