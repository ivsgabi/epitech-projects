/*
** EPITECH PROJECT, 2022
** my_rpg2
** File description:
** init_choose.c
*/

#include "struct.h"

sfSprite *create_img(sfVector2f pos, char *file)
{
    sfTexture *texture = sfTexture_createFromFile(file, NULL);
    sfSprite *sprite = sfSprite_create();
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setPosition(sprite, pos);
    return sprite;
}

void init_choose(choose_t *choose)
{
    choose->bulbi = create_img((sfVector2f) {400.0, 300.0},
    "assets/bulbi_button.png");
    choose->bulbi_hover = create_img((sfVector2f) {400.0, 300.0},
    "assets/bulbi_hover.png");
    choose->bulbi_clicked = create_img((sfVector2f) {400.0, 300.0},
    "assets/bulbi_clicked.png");
    choose->salam = create_img((sfVector2f) {800.0, 300.0},
    "assets/salameche_button.png");
    choose->salam_hover = create_img((sfVector2f) {800.0, 300.0},
    "assets/salameche_hover.png");
    choose->salam_clicked = create_img((sfVector2f) {800.0, 300.0},
    "assets/salameche_clicked.png");
    choose->cara = create_img((sfVector2f) {1200.0, 300.0},
    "assets/carapuce_button.png");
    choose->cara_hover = create_img((sfVector2f) {1200.0, 300.0},
    "assets/carapuce_hover.png");
    choose->cara_clicked = create_img((sfVector2f) {1200.0, 300.0},
    "assets/carapuce_clicked.png");
}

void destroy_choose(choose_t *choose)
{
    sfSprite_destroy(choose->bulbi);
    sfSprite_destroy(choose->bulbi_hover);
    sfSprite_destroy(choose->bulbi_clicked);
    sfSprite_destroy(choose->salam);
    sfSprite_destroy(choose->salam_hover);
    sfSprite_destroy(choose->salam_clicked);
    sfSprite_destroy(choose->cara);
    sfSprite_destroy(choose->cara_hover);
    sfSprite_destroy(choose->cara_clicked);
    free(choose);
}
