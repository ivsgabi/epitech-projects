/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** teleportation.c
*/

#include "struct.h"

int teleportation_house(arg_t *arg)
{
    if (arg->map[arg->player->pos.y - 1][arg->player->pos.x] == 'P') {
        arg->save_rect_map.height = arg->map_img->rect.height;
        arg->save_rect_map.left = arg->map_img->rect.left;
        arg->save_rect_map.width = arg->map_img->rect.width;
        arg->save_rect_map.top = arg->map_img->rect.top;
        arg->save_vect_map.x = arg->map_img->pos.x;
        arg->save_vect_map.y = arg->map_img->pos.y;
        arg->save_pos_player.x = arg->player->pos.x;
        arg->save_pos_player.y = arg->player->pos.y;
        arg->map_img->pos.x = 550;
        arg->map_img->pos.y = -900;
        arg->map_img->rect = (sfIntRect) {0, 2375, 2272, 1000};
        arg->player->pos = (sfVector2i) {50, 486};
        arg->player->img->pos.x = 860;
        arg->player->img->pos.y = 630;
        arg->can_move = 2;
        sfView_zoom(arg->view, 0.5f);
        return 1;
    }
    return 0;
}

int teleportation_retour(arg_t *arg)
{
    arg->map_img->rect.height = arg->save_rect_map.height;
    arg->map_img->rect.left = arg->save_rect_map.left;
    arg->map_img->rect.width = arg->save_rect_map.width;
    arg->map_img->rect.top = arg->save_rect_map.top;
    arg->map_img->pos.x = arg->save_vect_map.x;
    arg->map_img->pos.y = arg->save_vect_map.y;
    arg->player->pos.x = arg->save_pos_player.x;
    arg->player->pos.y = arg->save_pos_player.y;
    arg->player->img->pos.x = 950;
    arg->player->img->pos.y = 500;
    sfSprite_setScale(arg->player->img->sprite, (sfVector2f) {1.0, 1.0});
    sfView_zoom(arg->view, 2.0f);
    arg->can_move = 1;
    return 0;
}

int teleportation_center(arg_t *arg)
{
    if (arg->map[arg->player->pos.y - 1][arg->player->pos.x] == 'C') {
        arg->save_rect_map.height = arg->map_img->rect.height;
        arg->save_rect_map.left = arg->map_img->rect.left;
        arg->save_rect_map.width = arg->map_img->rect.width;
        arg->save_rect_map.top = arg->map_img->rect.top;
        arg->save_vect_map.x = arg->map_img->pos.x;
        arg->save_vect_map.y = arg->map_img->pos.y;
        arg->save_pos_player.x = arg->player->pos.x;
        arg->save_pos_player.y = arg->player->pos.y;
        arg->map_img->pos.x = 530;
        arg->map_img->pos.y = -900;
        arg->map_img->rect = (sfIntRect) {0, 1880, 2272, 1000};
        arg->player->pos = (sfVector2i) {50, 388};
        arg->player->img->pos.x = 950;
        arg->player->img->pos.y = 600;
        arg->can_move = 2;
        sfView_zoom(arg->view, 0.5f);
        return 1;
    }
    return 0;
}

int teleportation_shop(arg_t *arg)
{
    if (arg->map[arg->player->pos.y - 1][arg->player->pos.x] == 'S') {
        arg->save_rect_map.height = arg->map_img->rect.height;
        arg->save_rect_map.left = arg->map_img->rect.left;
        arg->save_rect_map.width = arg->map_img->rect.width;
        arg->save_rect_map.top = arg->map_img->rect.top;
        arg->save_vect_map.x = arg->map_img->pos.x;
        arg->save_vect_map.y = arg->map_img->pos.y;
        arg->save_pos_player.x = arg->player->pos.x;
        arg->save_pos_player.y = arg->player->pos.y;
        arg->map_img->pos.x = 530;
        arg->map_img->pos.y = -900;
        arg->map_img->rect = (sfIntRect) {0, 1480, 2272, 1000};
        arg->player->pos = (sfVector2i) {50, 284};
        arg->player->img->pos.x = 950;
        arg->player->img->pos.y = 600;
        arg->can_move = 2;
        sfView_zoom(arg->view, 0.5f);
        return 1;
    }
    return 0;
}

int teleportation_arene(arg_t *arg)
{
    if (arg->map[arg->player->pos.y - 1][arg->player->pos.x] == 'A') {
        arg->save_rect_map.height = arg->map_img->rect.height;
        arg->save_rect_map.left = arg->map_img->rect.left;
        arg->save_rect_map.width = arg->map_img->rect.width;
        arg->save_rect_map.top = arg->map_img->rect.top;
        arg->save_vect_map.x = arg->map_img->pos.x;
        arg->save_vect_map.y = arg->map_img->pos.y;
        arg->save_pos_player.x = arg->player->pos.x;
        arg->save_pos_player.y = arg->player->pos.y;
        arg->map_img->pos.x = 500;
        arg->map_img->pos.y = -900;
        arg->map_img->rect = (sfIntRect) {0, 1080, 2272, 1000};
        arg->player->pos = (sfVector2i) {50, 150};
        arg->player->img->pos.x = 950;
        arg->player->img->pos.y = 650;
        arg->can_move = 2;
        sfView_zoom(arg->view, 0.5f);
        return 1;
    }
    return 0;
}
