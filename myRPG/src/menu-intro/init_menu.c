/*
** EPITECH PROJECT, 2023
** intro
** File description:
** for my_rpg
*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"
#include "game_menu.h"

void handle_events(arg_t *arg, intro_t *intro)
{
    intro->mouse_pos = sfMouse_getPosition((sfWindow*) arg->window);
    arg->event.type == sfEvtClosed || sfKeyboard_isKeyPressed(sfKeyEscape)
    || (arg->event.type == sfEvtMouseButtonPressed && intro->mouse_pos.x >= 1365
    && intro->mouse_pos.x <= 1805 && intro->mouse_pos.y >= 60
    && intro->mouse_pos.y <= 157) ? sfRenderWindow_close(arg->window) : 0;
    slide_pages(arg, intro);
}

int main_loop(arg_t *arg, intro_t *intro, buttons_t *buttons,
sfMusic **music)
{
    game_menu_t *game_menu = malloc(sizeof(game_menu_t));
    if (game_menu == NULL)
        return (84);
    init_game_menu(game_menu);
    while (sfRenderWindow_isOpen(arg->window)) {
        intro->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
        while (sfRenderWindow_pollEvent(arg->window, &arg->event)) {
            handle_events(arg, intro);
        } sfRenderWindow_clear(arg->window, sfWhite);
        if (pages_display_conditions(arg, intro, buttons, game_menu)
        == BACK_TO_MENU)
            continue;
        if (intro->in_menu_status != 0) {
            is_on_settings(arg, intro, buttons);
            draw_quit_rect(arg, buttons);
            draw_setting_rect(arg, intro, buttons);
            if_settings_clicked(arg, intro, buttons, music);
        } sfRenderWindow_display(arg->window);
    }
    return (0);
}

int init_menu(arg_t *arg)
{
    struct intro_t *intro = malloc(sizeof(struct intro_t));
    if (intro == NULL) {
        return (84);
    }
    struct buttons_t *buttons = malloc(sizeof(struct buttons_t));
    if (buttons == NULL) {
        return (84);
    }
    init_intro(intro);
    intro->music = sfMusic_createFromFile("intro_assets/music_pokemon.ogg");
    arg->music = intro->music;
    arg->music_volume = &intro->music_volume;
    sfMusic_play(intro->music);
    sfMusic_setLoop(intro->music, sfTrue);
    set_intro_pages(intro);
    init_buttons(buttons);
    sfMusic_setVolume(intro->music, intro->music_volume);
    main_loop(arg, intro, buttons, &intro->music);
    return (0);
}
