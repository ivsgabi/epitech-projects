/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_battle_inventory.c
*/

#include "struct.h"
#include "init.h"
#include "utils.h"
#include "free.h"
#include "my.h"
#include <stdlib.h>

static void init_struct_inventory(arg_t *arg)
{
    arg->inventory = malloc(sizeof(inventory_t));
    if (arg->inventory == NULL)
        return;
    arg->inventory->pokeballs = 2;
    arg->inventory->money = 1000;
    arg->inventory->potions = 0;
    arg->inventory->pokemon_choose = 0;
    arg->inventory->display_inventory = 0;
    arg->inventory->pokemons = malloc(sizeof(pokemon_t) * 7);
    arg->inventory->text = init_text((sfVector2f) {500.0, 700.0}, sfBlack, 40);
    arg->inventory->use_potion = 0;
    for (int i = 0; i < 7; i++)
        arg->inventory->pokemons[i] = NULL;
}

static img_t *fill_img_struct(char **info)
{
    sfVector2f vector = {my_atof(info[0]), my_atof(info[1])};
    sfVector2f scale = {my_atof(info[2]), my_atof(info[3])};
    sfIntRect rectangle = {my_atoi(info[4]), my_atoi(info[5]),
    my_atoi(info[6]), my_atoi(info[7])};
    return init_struct_img(vector, rectangle,
    my_strdup(info[8]), scale);
}

static img_t **init_img_battle(void)
{
    char **info_img_battle = NULL;
    char **info_all_img_battle = read_map("config/battle.txt");
    int nb_img_battle = 0, index = 0;
    if (info_all_img_battle == NULL)
        return NULL;
    for (int i = 1; info_all_img_battle[i] != NULL; i++, nb_img_battle++);
    img_t **all_img_battle = malloc(sizeof(img_t) * (nb_img_battle + 1));
    all_img_battle[nb_img_battle] = NULL;
    for (int i = 1; info_all_img_battle[i] != NULL; i++, index++) {
        info_img_battle = parse_line(info_all_img_battle[i]);
        if (info_img_battle == NULL)
            return NULL;
        all_img_battle[index] = fill_img_struct(info_img_battle);
        if (all_img_battle[index] == NULL)
            return NULL;
    }
    free_array(info_all_img_battle);
    free_array(info_img_battle);
    return all_img_battle;
}

void init_struct_battle(arg_t *arg)
{
    arg->battle = malloc(sizeof(battle_t));
    if (arg->battle == NULL)
        return;
    arg->battle->battle_img = init_img_battle();
    arg->battle->all_pokemon = init_all_pokemons(arg);
    arg->battle->pop_pokemon = sfClock_create();
    arg->battle->fight = 0;
    arg->battle->pokemon_found = 0;
    arg->battle->random_nb = 0;
    arg->battle->num_pokemon = 0;
    arg->battle->in_battle_master = 0;
    char **pokemons = read_map("config/pokemon_dresseur.txt");
    for (int i = 0; i < 4; i++) {
        char **line = parse_line(pokemons[i]);
        arg->battle->pokemon_maitre[i] = init_struct_pokemons(line);
        arg->battle->pokemon_maitre[i] =
        fill_attack(arg->battle->pokemon_maitre[i]);
    }
    init_struct_inventory(arg);
}
