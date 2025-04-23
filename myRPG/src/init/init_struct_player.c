/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_struct_player.c
*/

#include "utils.h"
#include "my.h"
#include "init.h"
#include "free.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

player_t *init_struct_player(char *file, sfVector2i position, sfVector2f vec)
{
    player_t *player = malloc(sizeof(player_t));

    if (player == NULL)
        return NULL;
    player->pos = position;
    player->animation = sfClock_create();
    sfVector2f vector = vec;
    sfIntRect rectangle_player = {0, 0, 64, 64};
    sfVector2f scale_player = {1.0f, 1.0f};
    char *path_player = file;
    player->img = init_struct_img(vector, rectangle_player, path_player,
        scale_player);
    player->already_speak = 0;
    return player;
}

static player_t *init_pnj(char **info)
{
    sfVector2i pos = {my_atoi(info[0]), my_atoi(info[1])};
    sfVector2f vect = {my_atof(info[2]), my_atof(info[3])};
    player_t *pnj = init_struct_player(info[4], pos, vect);
    return pnj;
}

player_t **init_all_pnj(void)
{
    char **info_pnj = NULL;
    char **info_all_pnj = read_map("config/pnj.txt");
    int nb_pnj = 0, index = 0;
    if (info_all_pnj == NULL)
        return NULL;
    for (int i = 1; info_all_pnj[i] != NULL; i++, nb_pnj++);
    player_t **all_pnj = malloc(sizeof(player_t) * (nb_pnj + 1));
    all_pnj[nb_pnj] = NULL;
    for (int i = 1; info_all_pnj[i] != NULL; i++, index++) {
        info_pnj = parse_line(info_all_pnj[i]);
        if (info_pnj == NULL)
            return NULL;
        all_pnj[index] = init_pnj(info_pnj);
        if (all_pnj[index] == NULL)
            return NULL;
    }
    all_pnj[1]->img->rect.top = 128;
    free_array(info_all_pnj);
    free_array(info_pnj);
    return all_pnj;
}
