/*
** EPITECH PROJECT, 2022
** rpg
** File description:
** free_img.c
*/

#include "struct.h"
#include "free.h"
#include <stdlib.h>

void destroy_img(img_t *img)
{
    sfSprite_destroy(img->sprite);
    sfTexture_destroy(img->texture);
    free(img);
}

void destroy_text(text_t *text)
{
    sfText_destroy(text->text);
    sfFont_destroy(text->font);
    free(text);
}

void destroy_all_texts(text_t **texts)
{
    for (int i = 0; texts[i] != NULL; i++) {
        destroy_text(texts[i]);
    }
    free(texts);
}

void destroy_all_img(img_t **imgs)
{
    for (int i = 0; imgs[i] != NULL; i++) {
        destroy_img(imgs[i]);
    }
    free(imgs);
}

void free_battle(battle_t *battle)
{
    destroy_all_img(battle->battle_img);
    free_all_pokemons(battle->all_pokemon);
    sfClock_destroy(battle->pop_pokemon);
    free(battle);
}
