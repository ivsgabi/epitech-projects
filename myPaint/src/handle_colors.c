/*
** EPITECH PROJECT, 2023
** handle_colors
** File description:
** to handle colors in mypaint
*/

#include "../include/paint.h"

void handle_colors3(window_t *window, colors_t *colors, sfVector2i mouse_pos)
{
    if (mouse_pos.x >= colors->green.x && mouse_pos.x
    <= colors->green.x + colors->green_size.x &&
        mouse_pos.y >= colors->green.y && mouse_pos.y
        <= colors->green.y + colors->green_size.y) {
        window->current_color = sfGreen;
        window->status = 2;
        }
}

void handle_colors2(window_t *window, colors_t *colors, sfVector2i mouse_pos)
{
    if (mouse_pos.x >= colors->red.x && mouse_pos.x
    <= colors->red.x + colors->red_size.x &&
        mouse_pos.y >= colors->red.y && mouse_pos.y
        <= colors->red.y + colors->red_size.y) {
        window->current_color = sfRed;
        window->status = 2;
    } if (mouse_pos.x >= colors->blue.x && mouse_pos.x
    <= colors->blue.x + colors->blue_size.x &&
        mouse_pos.y >= colors->blue.y && mouse_pos.y
        <= colors->blue.y + colors->blue_size.y) {
        window->current_color = sfBlue;
        window->status = 2;
    } handle_colors3(window, colors, mouse_pos);
}

void handle_colors(window_t *window, colors_t *colors, sfVector2i mouse_pos)
{
    mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    if ((mouse_pos.x >= colors->black.x && mouse_pos.x
    <= colors->black.x + colors->black_size.x &&
        mouse_pos.y >= colors->black.y && mouse_pos.y
        <= colors->black.y + colors->black_size.y) ||
        (mouse_pos.x >= colors->pen.x && mouse_pos.x
        <= colors->pen.x + colors->pen_size.x &&
        mouse_pos.y >= colors->pen.y && mouse_pos.y
        <= colors->pen.y + colors->pen_size.y)) {
        window->current_color = sfBlack;
        window->status = 2;
    } if (mouse_pos.x >= colors->white.x && mouse_pos.x
    <= colors->white.x + colors->white_size.x &&
        mouse_pos.y >= colors->white.y && mouse_pos.y
        <= colors->white.y + colors->white_size.y) {
        window->current_color = sfWhite;
        window->status = 2;
    } handle_colors2(window, colors, mouse_pos);
}
