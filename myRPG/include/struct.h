/*
** EPITECH PROJECT, 2023
** rpg
** File description:
** struct.h
*/

#ifndef STRUCT_H
    #define STRUCT_H
    #define BACK_TO_MENU (47)
    #include <SFML/Graphics.h>
    #include <SFML/Audio.h>

    #define ERROR (-1)

typedef struct image_s {
    sfSprite *sprite;
    sfTexture *texture;
    sfVector2f pos;
    sfIntRect rect;
    int is_visible;
} img_t;

typedef struct player_s {
    sfVector2i pos;
    sfClock *animation;
    img_t *img;
    int already_speak;
} player_t;

typedef struct pokemons_s {
    char *name;
    char *type;
    int attack;
    int def;
    int speed;
    int hp;
    int save_hp;
    int exp;
    int level;
    char *attack_names[5];
    int damage_attack[4];
    img_t *f1;
    img_t *f2;
    img_t *dos_f1;
    img_t *dos_f2;
} pokemon_t;

typedef struct text_s {
    sfText *text;
    sfFont *font;
    sfVector2f pos;
    char *str;
    int is_visible;
} text_t;

typedef struct battle_s {
    img_t **battle_img;
    pokemon_t **all_pokemon;
    int nb_pokemons;
    sfClock *pop_pokemon;
    int pokemon_found;
    int fight;
    int random_nb;
    int num_pokemon;
    int in_battle_master;
    pokemon_t *pokemon_maitre[4];
    pokemon_t *pokemon_dresseur[2];
} battle_t;

typedef struct inventory_s {
    int potions;
    int pokemon_choose;
    pokemon_t **pokemons;
    int pokeballs;
    int money;
    int display_inventory;
    text_t *text;
    int use_potion;
} inventory_t;

typedef struct fight_s {
    int f1;
    text_t *life;
    text_t *life_enemy;
    text_t *name;
    text_t *name_enemy;
    text_t *attack;
    text_t *battle;
    sfClock *clock;
} fight_t;

typedef struct choose_pokemon {
    sfSprite *bulbi;
    sfSprite *bulbi_hover;
    sfSprite *bulbi_clicked;
    sfSprite *salam;
    sfSprite *salam_hover;
    sfSprite *salam_clicked;
    sfSprite *cara;
    sfSprite *cara_hover;
    sfSprite *cara_clicked;
} choose_t;

typedef struct arguments_s {
    int can_move;
    char *player_path;
    char **map;
    sfRenderWindow *window;
    sfVideoMode video_mode;
    player_t *player;
    inventory_t *inventory;
    player_t **pnj;
    img_t *map_img;
    img_t *text_box;
    img_t *info_pnj;
    img_t **obj_3d;
    battle_t *battle;
    sfVector2i mouse_pos;
    sfEvent event;
    text_t **texts;
    sfVector2i save_pos_player;
    sfVector2f save_vect_map;
    sfIntRect save_rect_map;
    sfView* view;
    int replace_pokemon;
    float *music_volume;
    sfMusic *music;
} arg_t;

#endif /* STRUCT_H */
