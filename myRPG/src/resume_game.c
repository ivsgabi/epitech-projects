/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** resume_game.c
*/

#include "struct.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"
#include "my.h"
#include "init.h"

void resume_player(arg_t *arg, char **info)
{
    char **map = parse_line(info[0]);
    arg->map_img->rect.left = my_atoi(map[0]);
    arg->map_img->rect.top = my_atoi(map[1]);

    char **player = parse_line(info[1]);
    arg->player_path = player[0];
    arg->player = init_struct_player(arg->player_path,
    (sfVector2i) {358, 433}, (sfVector2f) {950.0f, 500.0f});
    arg->player->pos.x = my_atoi(player[1]);
    arg->player->pos.y = my_atoi(player[2]);

    char **inventory = parse_line(info[2]);
    arg->inventory->money = my_atoi(inventory[0]);
    arg->inventory->pokeballs = my_atoi(inventory[1]);
    arg->inventory->potions = my_atoi(inventory[2]);
}

void resume_pokemon(arg_t *arg, char **info)
{
    char **p = NULL;
    int index = 0, j;
    for (int i = 3; i < 9; i++, index++) {
        p = parse_line(info[i]);
        if (p[0][0] == '\0' || p[0][0] == '\n')
            break;
        for (j = 0; arg->battle->all_pokemon[j] != NULL &&
        my_strcmp(p[0], arg->battle->all_pokemon[j]->name) != 0; j++);
        add_pokemon_to_inventory(arg, index, arg->battle->all_pokemon[j]);
        arg->inventory->pokemons[index]->hp = my_atoi(p[1]);
        arg->inventory->pokemons[index]->attack = my_atoi(p[2]);
    }
}

void resume_pnj(arg_t *arg, char **info)
{
    char **p = NULL;
    for (int i = 9, index = 0; i < 12; i++, index++) {
        p = parse_line(info[i]);
        if (p[0][0] == '\0' || p[0][0] == '\n') {
            continue;
        }

        arg->pnj[index]->img->pos.x = my_atof(p[0]);
        arg->pnj[index]->img->pos.y = my_atof(p[1]);
        arg->pnj[index]->already_speak = my_atoi(p[2]);
    }
}

void resume_3d_obj(arg_t *arg, char **info)
{
    char **p = NULL;
    for (int i = 12, index = 0; info[i] != NULL; i++, index++) {
        p = parse_line(info[i]);
        arg->obj_3d[index]->pos.x = my_atof(p[0]);
        arg->obj_3d[index]->pos.y = my_atof(p[1]);
    }
}

int resume_game(arg_t *arg)
{
    size_t size;
    FILE *file = fopen("save_game.txt", "r");
    if (file == NULL)
        return 1;
    char **info = malloc(sizeof(char *) * 42);
    char *line = NULL;
    int i = 0;
    while (getline(&line, &size, file) != EOF) {
        info[i] = my_strdup(line);
        i++;
    }
    info[i] = NULL;
    fclose(file);
    resume_player(arg, info);
    resume_pokemon(arg, info);
    resume_pnj(arg, info);
    resume_3d_obj(arg, info);
    arg->can_move = 1;
    return 0;
}
