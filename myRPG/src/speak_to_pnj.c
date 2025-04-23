/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** speak_to_pnj.c
*/

#include "struct.h"

static void open_text_box(arg_t *arg, int i)
{
    if (arg->event.type == sfEvtKeyPressed &&
    arg->event.key.code == sfKeyA && arg->texts[i]->is_visible == 0) {
        arg->pnj[i]->already_speak = 1;
        if (i == 1)
            arg->inventory->potions += 2;
        arg->texts[i]->is_visible = 1;
        arg->text_box->is_visible = 1;
        arg->can_move = 0;
        arg->pnj[i]->img->rect.top = 0;
    }
}

void speak_to_pnj(arg_t *arg)
{
    for (int i = 0; arg->pnj[i] != NULL; i++) {
        if (arg->player->img->pos.x >= arg->pnj[i]->img->pos.x -35
        && arg->player->img->pos.x <= arg->pnj[i]->img->pos.x + 35
        && arg->player->img->pos.y >= arg->pnj[i]->img->pos.y - 30
        && arg->player->img->pos.y <= arg->pnj[i]->img->pos.y + 30) {
            (arg->pnj[i]->already_speak == 0) ? arg->info_pnj->is_visible = 1
            : 0;
            open_text_box(arg, i);
            break;
        } else {
            arg->info_pnj->is_visible = 0;
        }
    }
}

int close_text_box(arg_t *arg, int check)
{
    for (int i = 0; arg->pnj[i]; i++) {
        if (arg->event.type == sfEvtKeyPressed &&
            arg->event.key.code == sfKeyA &&
            arg->texts[i]->is_visible == 1) {
            arg->texts[i]->is_visible = 0;
            arg->can_move = 1;
            check = 1;
        }
    }
    return check;
}
