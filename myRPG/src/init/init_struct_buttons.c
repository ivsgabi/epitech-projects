/*
** EPITECH PROJECT, 2023
** init_struct_buttons
** File description:
** for myrpg
*/

#include "intro_struct.h"
#include "intro_proto.h"

void init_buttons_again(buttons_t *buttons)
{
    buttons->window_settings =
    sfTexture_createFromFile("intro_assets/window_dsettings.png", NULL);
    buttons->window_settings_sprite = sfSprite_create();
    buttons->window_settings_pos = (sfVector2f) {-60, 140};
    buttons->window_settings_scale = (sfVector2f) {1.2, 1.2};

    buttons->boys_rect = sfRectangleShape_create();
    buttons->boys_size = (sfVector2f) {230, 47};
    buttons->boys_pos = (sfVector2f) {600, 856};
    buttons->boys_color = sfTransparent;
    buttons->girls_rect = sfRectangleShape_create();
    buttons->girls_size = (sfVector2f) {230, 47};
    buttons->girls_pos = (sfVector2f) {1020, 856};
    buttons->girls_color = sfTransparent;
}

void init_buttons_suite(buttons_t *buttons)
{
    buttons->dropdown_settings =
    sfTexture_createFromFile("intro_assets/dropdown_settings.png", NULL);
    buttons->dropdown_settings_sprite = sfSprite_create();
    buttons->dropdown_settings_pos = (sfVector2f) {74, 100};
    buttons-> dropdown_settings_scale = (sfVector2f) {0.65, 0.65};
    sfSprite_setTexture(buttons->dropdown_settings_sprite,
    buttons->dropdown_settings, sfTrue);
    sfSprite_setScale(buttons->dropdown_settings_sprite,
    buttons->dropdown_settings_scale);
    sfSprite_setPosition(buttons->dropdown_settings_sprite,
    buttons->dropdown_settings_pos);

    buttons->sound_settings =
    sfTexture_createFromFile("intro_assets/sound_dsettings.png", NULL);
    buttons->sound_settings_sprite = sfSprite_create();
    buttons->sound_settings_pos = (sfVector2f) {-27, 155};
    buttons->sound_settings_scale = (sfVector2f) {1, 1};
    init_buttons_again(buttons);
}

void init_buttons(buttons_t *buttons)
{
    buttons->settings_rect = sfRectangleShape_create();
    buttons->settings_size = (sfVector2f) {390, 77};
    buttons->settings_pos = (sfVector2f) {138, 62};
    buttons->settings_color = sfTransparent;
    sfRectangleShape_setSize(buttons->settings_rect,
    buttons->settings_size);
    sfRectangleShape_setPosition(buttons->settings_rect,
    buttons->settings_pos);

    buttons->quit_rect = sfRectangleShape_create();
    buttons->quit_size = (sfVector2f) {390, 77};
    buttons->quit_pos = (sfVector2f) {1393, 57};
    buttons->quit_color = sfTransparent;
    sfRectangleShape_setSize(buttons->quit_rect,
    buttons->quit_size);
    sfRectangleShape_setPosition(buttons->quit_rect,
    buttons->quit_pos);
    init_buttons_suite(buttons);
}
