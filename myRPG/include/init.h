/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** init.h
*/

#ifndef INIT_H
    #define INIT_H

    #include "struct.h"

arg_t *init_struct_arg(void);
img_t *init_struct_img(sfVector2f vector, sfIntRect rect, char const *file,
sfVector2f scale);
player_t *init_struct_player(char *file, sfVector2i position,
sfVector2f vector);
pokemon_t **init_all_pokemons(arg_t *arg);
player_t **init_all_pnj(void);
text_t **init_all_text(void);
void init_str_text(arg_t *arg);
void init_3d_obj(arg_t *arg);
void init_struct_battle(arg_t *arg);
text_t *init_text(sfVector2f vector, sfColor color, int size);
fight_t *init_struct_fight(arg_t *arg);
pokemon_t *init_struct_pokemons(char **info);
pokemon_t *fill_attack(pokemon_t *pokemon);
void init_choose(choose_t *choose);
void destroy_choose(choose_t *choose);

#endif /* INIT_H */
