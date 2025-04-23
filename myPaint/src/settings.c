/*
** EPITECH PROJECT, 2023
** setting_pen
** File description:
** pen parameters for mypaint
*/

#include "../include/paint.h"

void handle_file_button(window_t *window, t_point **points)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    if (mouse_pos.x >= 1263 && mouse_pos.x <= 1403 &&
        mouse_pos.y >= 146 && mouse_pos.y <= 206 &&
        window->event.type == sfEvtMouseButtonPressed) {
        free_list(points);
        }
}

void handle_thickness(window_t *window)
{
    sfVector2i mouse_pos = sfMouse_getPositionRenderWindow(window->window);
    if (mouse_pos.x >= 107 && mouse_pos.x <= 150 &&
        mouse_pos.y >= 555 && mouse_pos.y <= 802) {
        window->thickness = 20.f;
    } if (mouse_pos.x >= 160 && mouse_pos.x <= 170 &&
        mouse_pos.y >= 555 && mouse_pos.y <= 802) {
        window->thickness = 6.f;
    }
}
