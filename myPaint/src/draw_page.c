/*
** EPITECH PROJECT, 2023
** rect_init
** File description:
** rectangles initialisation for my paint
*/

#include <SFML/Graphics.h>
#include "../include/paint.h"


void rect_page(struct window_t *window)
{
    sfRectangleShape *page = sfRectangleShape_create();
    sfVector2f rect_size = {1350, 740};
    sfVector2f rect_pos = {370, 300};
    sfRectangleShape_setSize(page, rect_size);
    sfRectangleShape_setPosition(page, rect_pos);
    sfRectangleShape_setFillColor(page, sfWhite);
    sfRenderWindow_drawRectangleShape(window->window, page, NULL);
    window->back = page;
}
