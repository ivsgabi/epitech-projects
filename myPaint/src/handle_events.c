/*
** EPITECH PROJECT, 2023
** handle_events
** File description:
** handle events for mypaint
*/

#include "../include/paint.h"
// stop ici
void handle_events(window_t *window, colors_t *colors, sfVector2i *mouse_pos)
{
    window->event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape) ?
    sfRenderWindow_close(window->window) : 0;
    window->status = mouse_options(window, window->event, window->status);
    window->draw_circle = (window->event.type == sfEvtMouseButtonReleased) ?
    sfFalse : window->draw_circle;
    *mouse_pos = (window->event.type == sfEvtMouseMoved) ?
    sfMouse_getPositionRenderWindow(window->window) : *mouse_pos;
    if (window->event.type == sfEvtMouseButtonPressed &&
    sfMouse_isButtonPressed(sfMouseLeft)) {
        window->draw_circle = is_in(window, *mouse_pos) ?
        sfTrue : window->draw_circle;
        handle_colors(window, colors, *mouse_pos);
    }
}
