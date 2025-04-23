/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** free_all.c
*/

#include "struct.h"
#include <stdlib.h>
#include "free.h"

void free_array(char **arr)
{
    for (int i = 0; arr[i] != NULL; i++) {
        free(arr[i]);
    }
    free(arr);
}

void free_arg(arg_t *arg)
{
    free_array(arg->map);
    sfRenderWindow_destroy(arg->window);
    destroy_img(arg->map_img);
    destroy_img(arg->text_box);
    destroy_img(arg->info_pnj);
}

void free_all(arg_t *arg)
{
    free_arg(arg);
    free_inventory(arg->inventory);
    free_pnj(arg->pnj);
    free_battle(arg->battle);
    sfClock_destroy(arg->player->animation);
    destroy_all_texts(arg->texts);
    destroy_all_img(arg->obj_3d);
    free(arg);
}
