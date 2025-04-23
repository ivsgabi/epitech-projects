/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** my.h
*/

#ifndef MY_H
    #define MY_H

    #include "struct.h"
    #include "intro_struct.h"
    #include "game_menu.h"

char **read_map(char const *file);
int move_player(arg_t *arg);
arg_t *init_struct_arg(void);
int random_fight_pokemon(arg_t *arg);
void walk_png(arg_t *arg, int *bas, int *droite, int *start);
void speak_to_pnj(arg_t *arg);
int close_text_box(arg_t *arg, int check);
void add_pokemon_to_inventory(arg_t *arg, int i, pokemon_t *pokemon_to_add);
// sfSprite *create_img(sfVector2f pos, char *name, char *str2);
int display_button(sfVector2i mouse, arg_t *arg, char *name, float pos);
void manage_event(arg_t *arg, intro_t *intro, game_menu_t *game_menu);
int select_inventory(arg_t *arg);
int teleportation_arene(arg_t *arg);
int teleportation_shop(arg_t *arg);
int teleportation_center(arg_t *arg);
int teleportation_retour(arg_t *arg);
int teleportation_house(arg_t *arg);
void check_pos_mouse(arg_t *arg, int nb);
void display_start_battle_elt(arg_t *arg, fight_t *fight);
void end_music_fight(arg_t *arg, sfMusic *battle);
sfMusic *music_start_fight(arg_t *arg);
void heal_pokemon(pokemon_t **pokemons, arg_t *arg);
void shop(arg_t *arg);

#endif /* MY_H */
