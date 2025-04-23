/*
** EPITECH PROJECT, 2023
** intro proto header
** File description:
** menu + intro
*/

#include "struct.h"
#include "intro_struct.h"

#ifndef INTRO_PROTO_H
    #define INTRO_PROTO_H
int init_menu(arg_t *arg);
int main_loop(arg_t *arg, intro_t *intro, buttons_t *buttons,
sfMusic **music);
void handle_events(arg_t *arg, intro_t *intro);
void init_settings_dropdown_sprite(buttons_t *buttons);
void is_on_settings(arg_t *arg, intro_t *intro, buttons_t *buttons);
void draw_setting_rect(arg_t *arg, intro_t *intro, buttons_t *buttons);
void is_on_quit(arg_t *arg, buttons_t *buttons);
void draw_quit_rect(arg_t *arg, buttons_t *buttons);
void slide_pages(arg_t *arg, intro_t *intro);
void draw_sound_settings_sprite(arg_t *arg, buttons_t *buttons);
void draw_window_settings_sprite(arg_t *arg, buttons_t *buttons);
void settings_opt(arg_t *arg, intro_t *intro, buttons_t *buttons);
void if_settings_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons,
sfMusic **music);
void init_buttons(buttons_t *buttons);
void init_buttons_suite(buttons_t *buttons);
void init_intro_suite(intro_t *intro);
void init_intro(intro_t *intro);
void if_cross_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons);
void if_sound_clicked(arg_t *arg, intro_t *intro, buttons_t *buttons);
void if_window_clicked(arg_t *arg, intro_t *intro,
buttons_t *buttons);
void if_ssounds_close_is_clicked(arg_t *arg, intro_t *intro,
buttons_t *buttons);
void if_swindow_close_is_clicked(arg_t *arg, intro_t *intro,
buttons_t *buttons);
void music_volume_settings(arg_t *arg, intro_t *intro, sfMusic **music);
void sound_effects_volume(void);
void sound_settings_opt(arg_t *arg, intro_t *intro, sfMusic **music);
void window_size_settings(arg_t *arg);
void window_settings_opt(arg_t *arg);
int draw_character_choice_rect(arg_t *arg, buttons_t *buttons);
void set_intro_pages(intro_t *intro);
#endif
