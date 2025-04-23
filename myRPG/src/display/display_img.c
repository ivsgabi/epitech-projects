/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** display_img.c
*/

#include "struct.h"
#include "display.h"

void display_img(img_t *img, sfRenderWindow *window)
{
    sfSprite_setTextureRect(img->sprite, img->rect);
    sfSprite_setPosition(img->sprite, img->pos);
    sfRenderWindow_drawSprite(window, img->sprite, NULL);
}

void display_all_img(arg_t *arg, sfRenderWindow *window)
{
    display_img(arg->map_img, window);
    for (int i = 0; arg->pnj[i] != NULL && arg->can_move != 2; i++)
        display_img(arg->pnj[i]->img, window);
    display_img(arg->player->img, window);
    if (arg->battle->fight == 1)
        display_img(arg->battle->all_pokemon[0]->f1, window);
    for (int i = 0; arg->obj_3d[i] != NULL && arg->can_move != 2; i++)
        display_img(arg->obj_3d[i], window);
    if (arg->info_pnj->is_visible == 1 && arg->can_move != 2)
        display_img(arg->info_pnj, arg->window);
    display_text_box(arg, window);
}
