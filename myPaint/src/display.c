/*
** EPITECH PROJECT, 2023
** display
** File description:
** jsp
*/

#include "../include/paint.h"

void display(window_t *window, t_point **points)
{
    sfRenderWindow_clear(window->window, sfWhite);
    sfRenderWindow_drawSprite(window->window, window->base_sprite, NULL);
    rect_page(window);
    button_file(window);
    if (window->status == 3) {
        draw_colors(window, *points);
        sfRenderWindow_drawSprite(window->window, window->dropdown1, NULL);
        handle_thickness(window);
        handle_file_button(window, points);
    } if (window->status == 2) {
        draw_colors(window, *points);
        handle_file_button(window, points);
    } if (window->status == 1) {
        draw_colors(window, *points);
        sfRenderWindow_drawSprite(window->window, window->options_sprite, NULL);
        handle_file_button(window, points);
        handle_thickness(window);
    }

}
