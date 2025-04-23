/*
** EPITECH PROJECT, 2023
** handle_dropdown
** File description:
** handle dropdown menu for my_rpg
*/

#include <stdio.h>
#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"

void draw_sound_settings_sprite(arg_t *arg, buttons_t *buttons)
{
    sfSprite_setTexture(buttons->sound_settings_sprite,
    buttons->sound_settings, sfTrue);
    sfSprite_setScale(buttons->sound_settings_sprite,
    buttons->sound_settings_scale);
    sfSprite_setPosition(buttons->sound_settings_sprite,
    buttons->sound_settings_pos);
    sfRenderWindow_drawSprite(arg->window,
    buttons->sound_settings_sprite, NULL);
}

void draw_window_settings_sprite(arg_t *arg, buttons_t *buttons)
{
    sfSprite_setTexture(buttons->window_settings_sprite,
    buttons->window_settings, sfTrue);
    sfSprite_setScale(buttons->window_settings_sprite,
    buttons->window_settings_scale);
    sfSprite_setPosition(buttons->window_settings_sprite,
    buttons->window_settings_pos);
    sfRenderWindow_drawSprite(arg->window,
    buttons->window_settings_sprite, NULL);
}

void settings_opt(arg_t *arg, intro_t *intro, buttons_t *buttons)
{
    if_cross_clicked(arg, intro, buttons);
    if_sound_clicked(arg, intro, buttons);
    if_window_clicked(arg, intro, buttons);
}

void if_settings_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons,
sfMusic **music)
{
    if (intro->dropdown_status == 1 && intro->is_clicked == 1) {
        settings_opt(arg, intro, buttons);
    }
    if (intro->dropdown_status == 1) {
        sfRenderWindow_drawSprite(arg->window,
        buttons->dropdown_settings_sprite, NULL);
    } if (intro->is_clicked == 2) {
        draw_sound_settings_sprite(arg, buttons);
        sound_settings_opt(arg, intro, music);
        if_ssounds_close_is_clicked(arg, intro, buttons);
    } if (intro->is_clicked == 3) {
        draw_window_settings_sprite(arg, buttons);
        window_settings_opt(arg);
        if_swindow_close_is_clicked(arg, intro, buttons);
    }
}
