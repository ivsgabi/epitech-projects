/*
** EPITECH PROJECT, 2023
** init_strut
** File description:
** intialize struc for my_rpg menu + intro
*/

#include "intro_struct.h"
#include "intro_proto.h"

void set_intro_nb(intro_t *intro)
{
    intro-> status = 0;
    intro->in_menu_status = 0;
    intro->in_intro_status = 0;
    intro->in_game_status = 0;
    intro->dropdown_status = 0;
    intro->is_clicked = 0;
    intro->music_volume = 30.0;
    intro->scale = (sfVector2f) {1, 1};
}

void intro_pages_suite(intro_t *intro)
{
    intro->intro5 = sfTexture_createFromFile("intro_assets/intro5.jpg", NULL);
    intro->sprite5 = sfSprite_create();
    sfSprite_setTexture(intro->sprite5, intro->intro5, sfTrue);
    sfSprite_setScale(intro->sprite5, intro->scale);

    intro->intro6 = sfTexture_createFromFile("intro_assets/intro6.jpg", NULL);
    intro->sprite6 = sfSprite_create();
    sfSprite_setTexture(intro->sprite6, intro->intro6, sfTrue);
    sfSprite_setScale(intro->sprite6, intro->scale);

    intro->intro7 = sfTexture_createFromFile("intro_assets/intro7.jpg", NULL);
    intro->sprite7 = sfSprite_create();
    sfSprite_setTexture(intro->sprite7, intro->intro7, sfTrue);
    sfSprite_setScale(intro->sprite7, intro->scale);

    intro->intro_choose =
    sfTexture_createFromFile("intro_assets/choosecharacter.jpg", NULL);
    intro->sprite_choose = sfSprite_create();
    sfSprite_setTexture(intro->sprite_choose, intro->intro_choose, sfTrue);
    sfSprite_setScale(intro->sprite_choose, intro->scale);
}

void set_intro_pages(intro_t *intro)
{
    intro->menu = sfTexture_createFromFile("intro_assets/menu.jpg", NULL);
    intro->sprite_menu = sfSprite_create();
    sfSprite_setTexture(intro->sprite_menu, intro->menu, sfTrue);
    intro->intro1 = sfTexture_createFromFile("intro_assets/intro1.jpg", NULL);
    intro->sprite1 = sfSprite_create();
    sfSprite_setTexture(intro->sprite1, intro->intro1, sfTrue);
    sfSprite_setScale(intro->sprite1, intro->scale);
    intro->intro2 = sfTexture_createFromFile("intro_assets/intro2.jpg", NULL);
    intro->sprite2 = sfSprite_create();
    sfSprite_setTexture(intro->sprite2, intro->intro2, sfTrue);
    sfSprite_setScale(intro->sprite2, intro->scale);
    intro->intro3 = sfTexture_createFromFile("intro_assets/intro3.jpg", NULL);
    intro->sprite3 = sfSprite_create();
    sfSprite_setTexture(intro->sprite3, intro->intro3, sfTrue);
    sfSprite_setScale(intro->sprite3, intro->scale);
    intro->intro4 = sfTexture_createFromFile("intro_assets/intro4.jpg", NULL);
    intro->sprite4 = sfSprite_create();
    sfSprite_setTexture(intro->sprite4, intro->intro4, sfTrue);
    sfSprite_setScale(intro->sprite4, intro->scale);
    intro_pages_suite(intro);
}

void init_intro(intro_t *intro)
{
    set_intro_nb(intro);
    set_intro_pages(intro);
}
