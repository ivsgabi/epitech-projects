/*
** EPITECH PROJECT, 2023
** struct header
** File description:
** for intro & menu in my_rpg
*/

#include <SFML/Audio.h>
#include <SFML/Graphics.h>

#ifndef INTRO_STRUCT_H
    #define INTRO_STRUCT_H
typedef struct intro_t {
    sfMusic *music;
    int in_menu_status;
    int in_intro_status;
    int in_game_status;
    int status;
    int dropdown_status;
    int is_clicked;
    float music_volume;
    sfTexture *menu;
    sfSprite *sprite_menu;
    sfTexture *intro1;
    sfSprite *sprite1;
    sfTexture *intro2;
    sfSprite *sprite2;
    sfTexture *intro3;
    sfSprite *sprite3;
    sfTexture *intro4;
    sfSprite *sprite4;
    sfTexture *intro5;
    sfSprite *sprite5;
    sfTexture *intro6;
    sfSprite *sprite6;
    sfTexture *intro7;
    sfSprite *sprite7;
    sfTexture *intro_choose;
    sfSprite *sprite_choose;
    sfVector2f scale;
    sfVector2i mouse_pos;
} intro_t;

typedef struct buttons_t {
    sfRectangleShape* settings_rect;
    sfVector2f settings_size;
    sfVector2f settings_pos;
    sfColor settings_color;

    sfRectangleShape* quit_rect;
    sfVector2f quit_size;
    sfVector2f quit_pos;
    sfColor quit_color;

    sfTexture *dropdown_settings;
    sfSprite *dropdown_settings_sprite;
    sfVector2f dropdown_settings_pos;
    sfVector2f dropdown_settings_scale;

    sfTexture *sound_settings;
    sfSprite *sound_settings_sprite;
    sfVector2f sound_settings_pos;
    sfVector2f sound_settings_scale;

    sfTexture *window_settings;
    sfSprite *window_settings_sprite;
    sfVector2f window_settings_pos;
    sfVector2f window_settings_scale;

    sfRectangleShape* boys_rect;
    sfVector2f boys_size;
    sfVector2f boys_pos;
    sfColor boys_color;

    sfRectangleShape* girls_rect;
    sfVector2f girls_size;
    sfVector2f girls_pos;
    sfColor girls_color;
} buttons_t;
#endif
