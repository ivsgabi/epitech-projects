/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_struct_arg.c
*/

#include "my.h"
#include "struct.h"
#include "init.h"
#include <fcntl.h>
#include <stdlib.h>
#include "utils.h"

void init_sprite_main_map(arg_t *arg)
{
    sfVector2f vector = {-1000.0f, -900.0f};
    sfIntRect rectangle_map = {1307, 1860, 2272, 2496};
    sfVector2f scale_map = {2, 1.8};
    char *path_bg = "assets/map4.png";
    arg->map_img = init_struct_img(vector, rectangle_map, path_bg, scale_map);
}

void init_text_box_img(arg_t *arg)
{
    sfIntRect rect = {0, 0, 1500, 200};
    sfVector2f scale = {1.0f, 1.0f};
    sfVector2f vect = {200, 800};
    arg->text_box = init_struct_img(vect, rect, "assets/text_box.png", scale);
    arg->text_box->is_visible = 0;

    rect = (sfIntRect) {0, 0, 512, 512};
    scale = (sfVector2f) {0.15f, 0.15f};
    vect = (sfVector2f) {1000, 450};
    arg->info_pnj = init_struct_img(vect, rect, "assets/info.png", scale);
    arg->info_pnj->is_visible = 0;
    arg->view = sfView_createFromRect((sfFloatRect){0.0, 0.0, 1920.0, 1030.0});
    sfRenderWindow_setView(arg->window, arg->view);
}

void init_save_elt_arg(arg_t *arg)
{
    arg->can_move = 0;
    arg->save_rect_map.height = arg->map_img->rect.height;
    arg->save_rect_map.left = arg->map_img->rect.left;
    arg->save_rect_map.width = arg->map_img->rect.width;
    arg->save_rect_map.top = arg->map_img->rect.top;
    arg->save_vect_map.x = arg->map_img->pos.x;
    arg->save_vect_map.y = arg->map_img->pos.y;
    arg->save_pos_player.x = 358;
    arg->save_pos_player.y = 433;
}

arg_t *init_struct_arg(void)
{
    arg_t *arg = malloc(sizeof(arg_t));
    if (arg == NULL)
        return NULL;
    arg->video_mode = (sfVideoMode) {1920, 1080, 32};
    arg->window = sfRenderWindow_create(arg->video_mode, "My_rpg", sfResize |
    sfClose, NULL);
    sfRenderWindow_setFramerateLimit(arg->window, 60);
    arg->pnj = init_all_pnj();
    init_text_box_img(arg);
    init_str_text(arg);
    arg->replace_pokemon = 0;
    arg->map = read_map("maps/game_map.txt");
    arg->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->map == NULL)
        return NULL;
    init_sprite_main_map(arg);
    init_struct_battle(arg);
    init_3d_obj(arg);
    init_save_elt_arg(arg);
    return arg;
}
