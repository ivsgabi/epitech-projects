/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** start_fight.c
*/

#include "struct.h"
#include "display.h"
#include "init.h"
#include "battle.h"
#include <stdlib.h>
#include <stdio.h>
#include "my.h"

void put_damage_pokemon(arg_t *arg, pokemon_t *p, int attack_random)
{
    int damage = p->attack * p->damage_attack[attack_random] / 100;
    int hp = arg->inventory->pokemons[arg->inventory->pokemon_choose]->hp;
    int degat = hp - damage;
    if (degat < 0) {
        degat = 0;
    }
    arg->inventory->pokemons[arg->inventory->pokemon_choose]->hp = degat;
}

pokemon_t *select_pokemon_wild_master(arg_t *arg)
{
    if (arg->battle->in_battle_master == 1)
        return arg->battle->pokemon_maitre[arg->battle->num_pokemon];
    else
        return arg->battle->all_pokemon[arg->battle->num_pokemon];
}

int wild_pokemon_attack(arg_t *arg, fight_t *fight)
{
    int attack_random = rand() % 4;
    pokemon_t *p = select_pokemon_wild_master(arg);
    put_damage_pokemon(arg, p, attack_random);
    int check = end_of_battle(arg, fight);
    if (check == 1)
        return 1;
    if (check == 5)
        return 5;
    sfClock *sleep_clock = sfClock_create();
    text_t *attack_enemy = init_text((sfVector2f) {820, 850}, sfBlack, 35);
    attack_enemy->str = p->attack_names[attack_random];
    while (sfClock_getElapsedTime(sleep_clock).microseconds / 100000 < 30.0) {
        display_background_battle(arg, fight);
        display_battle_options(arg, fight);
        display_elt_battle(arg, fight);
        display_attack_wild_pokemon(arg, fight, attack_enemy);
        sfRenderWindow_display(arg->window);
    }
    sfClock_destroy(sleep_clock);
    return 0;
}

int check_value_manage_options(arg_t *arg, fight_t *fight, sfMusic *battle)
{
    int check = manage_options(arg, fight);
    if (check == 1) {
        end_music_fight(arg, battle);
        return 1;
    }
    if (check == 5) {
        end_music_fight(arg, battle);
        return 5;
    }
    return 0;
}

int start_fight(arg_t *arg)
{
    battle_num_pokemon(arg);
    int i, check = 0;
    for (i = 0; arg->inventory->pokemons[i] != NULL &&
    arg->inventory->pokemons[i]->hp <= 0; i++);
    if (i == 6)
        return 0;
    arg->inventory->pokemon_choose = i;
    fight_t *fight = init_struct_fight(arg);
    sfMusic *battle = music_start_fight(arg);
    while (sfRenderWindow_isOpen(arg->window)) {
        display_start_battle_elt(arg, fight);
        check = check_value_manage_options(arg, fight, battle);
        if (check != 0)
            return check;
        display_text(arg, fight->life);
        sfRenderWindow_display(arg->window);
    }
    end_music_fight(arg, battle);
    return 2;
}
