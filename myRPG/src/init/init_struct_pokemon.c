/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_struct_pokemon.c
*/

#include "my.h"
#include "init.h"
#include "utils.h"
#include "free.h"
#include <stdlib.h>


pokemon_t *fill_attack(pokemon_t *pokemon)
{
    char **all_attacks = read_map("config/attack.txt"), **lines = NULL;
    if (my_strcmp(pokemon->type, "feu\0") == 0)
        lines = parse_line(all_attacks[1]);
    if (my_strcmp(pokemon->type, "electrik\0") == 0)
        lines = parse_line(all_attacks[2]);
    if (my_strcmp(pokemon->type, "eau\0") == 0)
        lines = parse_line(all_attacks[3]);
    if (my_strcmp(pokemon->type, "vol\0") == 0)
        lines = parse_line(all_attacks[4]);
    if (my_strcmp(pokemon->type, "plante\0") == 0)
        lines = parse_line(all_attacks[5]);
    if (my_strcmp(pokemon->type, "poison\0") == 0)
        lines = parse_line(all_attacks[6]);
    if (my_strcmp(pokemon->type, "normal\0") == 0)
        lines = parse_line(all_attacks[7]);
    for (int i = 0, index = 0; i < 4; i++, index += 2) {
        pokemon->attack_names[i] = lines[index];
        pokemon->damage_attack[i] = my_atoi(lines[index + 1]);
    }
    return pokemon;
}

static pokemon_t *init_pokemon_part2(pokemon_t *pokemon, char **info)
{
    pokemon->type = my_strdup(info[8]);
    pokemon->attack = my_atoi(info[9]);
    pokemon->def = my_atoi(info[10]);
    pokemon->speed = my_atoi(info[11]);
    pokemon->hp = my_atoi(info[12]);
    pokemon->save_hp = my_atoi(info[12]);
    pokemon->name = my_strdup(info[17]);
    pokemon->exp = 100;
    pokemon->level = 1;
    return pokemon;
}

pokemon_t *init_struct_pokemons(char **info)
{
    pokemon_t *pokemon = malloc(sizeof(pokemon_t));
    sfVector2f vector = {my_atof(info[0]), my_atof(info[1])};
    sfVector2f vector_dos = {my_atof(info[0]) - 500.0, my_atof(info[1]) + 125};
    sfVector2f scale = {my_atof(info[2]), my_atof(info[3])};
    sfIntRect rectangle = {my_atoi(info[4]), my_atoi(info[5]),
    my_atoi(info[6]), my_atoi(info[7])};
    pokemon->f1 = init_struct_img(vector, rectangle,
    my_strdup(info[13]), scale);
    pokemon->f2 = init_struct_img(vector, rectangle,
    my_strdup(info[14]), scale);
    pokemon->dos_f1 = init_struct_img(vector_dos, rectangle,
    my_strdup(info[15]), scale);
    pokemon->dos_f2 = init_struct_img(vector_dos, rectangle,
    my_strdup(info[16]), scale);
    pokemon = init_pokemon_part2(pokemon, info);
    return pokemon;
}

pokemon_t **init_all_pokemons(arg_t *arg)
{
    char **info_pokemon = NULL;
    char **info_all_pokemon = read_map("config/pokemon.txt");
    int nb_pokemon = 0, index = 0;
    for (int i = 1; info_all_pokemon[i] != NULL; i++, nb_pokemon++);
    arg->battle->nb_pokemons = nb_pokemon;
    pokemon_t **all_pokemon = malloc(sizeof(pokemon_t) * (nb_pokemon + 1));
    all_pokemon[nb_pokemon] = NULL;
    for (int i = 1; info_all_pokemon[i] != NULL; i++, index++) {
        info_pokemon = parse_line(info_all_pokemon[i]);
        if (info_pokemon == NULL)
            return NULL;
        all_pokemon[index] = init_struct_pokemons(info_pokemon);
        all_pokemon[index] = fill_attack(all_pokemon[index]);
        if (all_pokemon[index] == NULL)
            return NULL;
    }
    free_array(info_all_pokemon);
    free_array(info_pokemon);
    return all_pokemon;
}
