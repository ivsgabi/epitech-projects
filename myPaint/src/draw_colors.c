/*
** EPITECH PROJECT, 2023
** draw
** File description:
** functions to draw for mypaint
*/

#include "../include/paint.h"

void draw_colors(struct window_t *window, t_point *points)
{
    for (t_point *p = points; p != NULL; p = p->next) {
    sfCircleShape_setRadius(window->circle, p->size);
    sfCircleShape_setFillColor(window->circle, p->color);
    sfCircleShape_setPosition(window->circle, (sfVector2f){p->x, p->y});
    sfRenderWindow_drawCircleShape(window->window, window->circle, NULL);
    }
}
