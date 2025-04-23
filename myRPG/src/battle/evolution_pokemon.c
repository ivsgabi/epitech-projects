/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** evolution_pokemon.c
*/

#include "struct.h"
#include "my.h"
#include "init.h"
#include "battle.h"
#include "utils.h"

static pokemon_t *change_pokemon_evolution(pokemon_t *pokemon, char **info)
{
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
    pokemon->name = my_strdup(info[17]);
    return pokemon;
}

static char **fill_file(pokemon_t *pokemon)
{
    char **file;

    if (pokemon->level == 5)
        file = read_map("config/evolution1.txt");
    else
        file = read_map("config/evolution2.txt");
    return file;
}

static void evolution_pokemon(pokemon_t *pokemon)
{
    char **file;
    char **line;
    int i = 0;

    if (pokemon->level >= 15)
        return;
    if (pokemon->level == 5)
        file = read_map("config/pokemon.txt");
    if (pokemon->level == 10)
        file = read_map("config/evolution1.txt");
    for (; file[i] != NULL; i++) {
        line = parse_line(file[i]);
        if (my_strcmp(line[17], pokemon->name) == 0)
            break;
    }
    file = fill_file(pokemon);
    if (file[i][0] == '\0')
        return;
    line = parse_line(file[i]);
    pokemon = change_pokemon_evolution(pokemon, line);
}

void add_exp_level(arg_t *arg)
{
    for (int i = 0; arg->inventory->pokemons[i] != NULL; i++) {
        if (arg->inventory->pokemons[i]->hp > 0) {
            arg->inventory->pokemons[i]->exp += 100;
        }
        if (arg->inventory->pokemons[i]->exp >= 500) {
            arg->inventory->pokemons[i]->attack += 10;
            arg->inventory->pokemons[i]->speed += 10;
            arg->inventory->pokemons[i]->def += 10;
            arg->inventory->pokemons[i]->hp += 7;
            arg->inventory->pokemons[i]->save_hp += 7;
            arg->inventory->pokemons[i]->level += 1;
            arg->inventory->pokemons[i]->exp = 0;
        }
        if (arg->inventory->pokemons[i]->level % 5 == 0) {
            evolution_pokemon(arg->inventory->pokemons[i]);
        }
    }
}
