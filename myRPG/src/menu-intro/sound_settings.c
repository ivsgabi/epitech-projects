/*
** EPITECH PROJECT, 2023
** sound_settings
** File description:
** handle sound settings in menu of myrpg
*/

#include <stdio.h>
#include "struct.h"
#include "intro_struct.h"
#include "intro_proto.h"

void music_volume_settings(arg_t *arg, intro_t *intro, sfMusic **music)
{
    intro->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 350 && intro->mouse_pos.x <= 388
    && intro->mouse_pos.y >= 242 && intro->mouse_pos.y <= 282) {
        intro->music_volume = intro->music_volume + 15.0;
        sfMusic_setVolume(*music, intro->music_volume);
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 393 && intro->mouse_pos.x <= 432
    && intro->mouse_pos.y >= 242 && intro->mouse_pos.y <= 282) {
        intro->music_volume = intro->music_volume - 15.0;
        sfMusic_setVolume(*music, intro->music_volume);
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 436 && intro->mouse_pos.x <= 472
    && intro->mouse_pos.y >= 242 && intro->mouse_pos.y <= 282) {
        intro->music_volume = 0;
        sfMusic_setVolume(*music, intro->music_volume);
    }
}

void sound_effects_volume(void)
{
    return;
}

void sound_settings_opt(arg_t *arg, intro_t *intro, sfMusic **music)
{
    music_volume_settings(arg, intro, music);
    sound_effects_volume();
}
