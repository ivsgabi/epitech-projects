/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** init_struct_img.c
*/

#include "struct.h"
#include "utils.h"
#include "my.h"
#include "free.h"
#include <stdlib.h>

img_t *init_struct_img(sfVector2f vector, sfIntRect rect, char const *file,
sfVector2f scale)
{
    img_t *img = malloc(sizeof(*img));
    if (img == NULL)
        return NULL;
    img->pos = vector;
    img->rect = rect;
    sfTexture *texture = sfTexture_createFromFile(file, NULL);
    sfSprite *sprite = sfSprite_create();
    img->texture = texture;
    img->sprite = sprite;
    img->is_visible = 1;
    sfSprite_setTexture(img->sprite, img->texture, sfFalse);
    sfSprite_setTextureRect(img->sprite, img->rect);
    sfSprite_setPosition(img->sprite, img->pos);
    sfSprite_setScale(img->sprite, scale);
    return (img);
}

static img_t *init_obj(char **info)
{
    sfVector2f vect = {my_atof(info[0]), my_atof(info[1])};
    sfIntRect rect = {my_atoi(info[2]), my_atoi(info[3]),
    my_atoi(info[4]), my_atoi(info[5])};
    sfVector2f scale = {my_atof(info[6]), my_atof(info[7])};
    img_t *obj = init_struct_img(vect, rect, info[8], scale);
    return obj;
}

void init_3d_obj(arg_t *arg)
{
    char **info_obj = NULL;
    char **info_all_obj = read_map("config/3d_obj.txt");
    int nb_obj = 0, index = 0;
    if (info_all_obj == NULL)
        return;
    for (int i = 1; info_all_obj[i] != NULL; i++, nb_obj++);
    img_t **all_obj = malloc(sizeof(img_t) * (nb_obj + 1));
    all_obj[nb_obj] = NULL;
    for (int i = 1; info_all_obj[i] != NULL; i++, index++) {
        info_obj = parse_line(info_all_obj[i]);
        if (info_obj == NULL)
            return;
        all_obj[index] = init_obj(info_obj);
        if (all_obj[index] == NULL)
            return;
    }
    free_array(info_all_obj);
    free_array(info_obj);
    arg->obj_3d = all_obj;
}
