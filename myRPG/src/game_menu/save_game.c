/*
** EPITECH PROJECT, 2023
** save
** File description:
** for my_rpg menu & game menu
*/

#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "game_menu.h"
#include "intro_struct.h"
#include "save.h"

int read_save_file(save_game_t *save)
{
    FILE *file = fopen("save.txt", "wb");

    if (file == NULL) {
        return (84);
    }
    fread(&save, sizeof(save_game_t), 1, file);
    fclose(file);
    return (0);
}

int write_save_file(save_game_t *save)
{
    FILE *file = fopen("save.txt", "wb");

    if (file == NULL) {
        return (84);
    }
    fwrite(&save, sizeof(save_game_t), 1, file);
    fclose(file);
    return (0);
}

int handle_save_game(arg_t *arg)
{
    save_game_t *save = malloc(sizeof(save_game_t));
    if (save == NULL)
        return (84);
    init_save_struct(arg, save);
    write_save_file(save);
    read_save_file(save);
    return (0);
}

void display_save_done(arg_t *arg, intro_t *intro)
{
    sfClock *clock = sfClock_create();
    float time = 0;

    sfTexture* saveok_texture =
    sfTexture_createFromFile("intro_assets/saveok.png", NULL);
    sfSprite* saveok_sprite = sfSprite_create();
    sfVector2f saveok_pos = {100, 100};
    sfVector2f saveok_scale = {1, 1};

    sfSprite_setTexture(saveok_sprite, saveok_texture, sfTrue);
    sfSprite_setPosition(saveok_sprite, saveok_pos);
    sfSprite_setScale(saveok_sprite, saveok_scale);

    while (time <= 3) {
        sfRenderWindow_drawSprite(arg->window, saveok_sprite, NULL);
        time += sfTime_asSeconds(sfClock_getElapsedTime(clock));
        sfClock_restart(clock);
    }
    sfClock_destroy(clock);
}

void gm_save_game(arg_t *arg, intro_t *intro, game_menu_t *game_menu)
{
    intro->mouse_pos = sfMouse_getPosition((sfWindow*)arg->window);
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 1243 && intro->mouse_pos.x <= 1476
    && intro->mouse_pos.y >= 211 && intro->mouse_pos.y <= 247) {
        intro->in_menu_status = 0;
        intro->in_intro_status = 0;
        intro->in_game_status = 1;
        if (resume_game(arg) == 1)
            return;
        game_menu_t *game_menu = malloc(sizeof(game_menu_t));
        init_game_menu(game_menu);
        main_game(arg, intro, game_menu, 1);
    }
    if (arg->event.type == sfEvtMouseButtonPressed
    && intro->mouse_pos.x >= 1414 && intro->mouse_pos.x <= 1566
    && intro->mouse_pos.y >= 230 && intro->mouse_pos.y <= 265
    || (arg->event.type == sfEvtKeyPressed
    && arg->event.key.code == sfKeyS)) {
        save_party(arg); display_save_done(arg, intro);
    }
}
