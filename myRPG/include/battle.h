/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** battle.h
*/

#ifndef BATTLE_H
    #define BATTLE_H

    #include "struct.h"

int attack_pressed(arg_t *arg);
int capture_pokemon(arg_t *arg, fight_t *fight);
void check_time(fight_t *fight, sfTime time);
int random_fight_pokemon(arg_t *arg);
int manage_options(arg_t *arg, fight_t *fight);
int options_pressed(arg_t *arg, fight_t *fight);
int start_fight(arg_t *arg);
int end_of_battle(arg_t *arg, fight_t *fight);
void manage_f1(fight_t *fight);
void select_attack(arg_t *arg);
int wild_pokemon_attack(arg_t *arg, fight_t *fight);
void choose_pokemon(arg_t *arg);
void change_pos_btn(arg_t *arg, int i);
void select_pokemon(arg_t *arg, int *pressed, int i);
int change_pokemon_combat(arg_t *arg);
void add_exp_level(arg_t *arg);
void battle_num_pokemon(arg_t *arg);
pokemon_t **select_pok(arg_t *arg);

#endif /* BATTLE_H */
