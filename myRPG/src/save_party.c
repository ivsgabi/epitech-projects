/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** save_party.c
*/

#include "struct.h"
#include <fcntl.h>
#include "utils.h"
#include <unistd.h>

static void save_pokemon(arg_t *arg, int fd)
{
    for (int i = 0; i < 6; i++) {
        if (arg->inventory->pokemons[i] != NULL) {
            mini_printf(fd, "%s;%d;%d\n", arg->inventory->pokemons[i]->name,
            arg->inventory->pokemons[i]->hp,
            arg->inventory->pokemons[i]->attack);
        } else {
            mini_printf(fd, "\n");
        }
    }
}

void save_party(arg_t *arg)
{
    int fd = open("save_game.txt", O_CREAT | O_WRONLY |
    O_TRUNC | O_APPEND, 0666);
    if (fd == -1)
        return;
    mini_printf(fd, "%d;%d\n", arg->map_img->rect.left,
    arg->map_img->rect.top);
    mini_printf(fd, "%s;%d;%d\n", arg->player_path, arg->player->pos.x,
    arg->player->pos.y);
    mini_printf(fd, "%d;%d;%d\n", arg->inventory->money,
    arg->inventory->pokeballs, arg->inventory->potions);
    save_pokemon(arg, fd);
    for (int i = 0; i < 3; i++) {
        mini_printf(fd, "%f;%f;%d\n", arg->pnj[i]->img->pos.x,
        arg->pnj[i]->img->pos.y, arg->pnj[i]->already_speak);
    }
    for (int i = 0; arg->obj_3d[i] != NULL; i++) {
        mini_printf(fd, "%f;%f\n", arg->obj_3d[i]->pos.x,
        arg->obj_3d[i]->pos.y);
    }
    close(fd);
}
