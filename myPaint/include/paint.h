/*
** EPITECH PROJECT, 2023
** paint csfml header
** File description:
** for mypaint
*/

#include <stdbool.h>
#include <stdarg.h>
#include <SFML/Window/Export.h>
#include <SFML/Window/Joystick.h>
#include <SFML/Window/Keyboard.h>
#include <SFML/Window/Mouse.h>
#include <SFML/Window/Sensor.h>
#include <SFML/Graphics.h>
#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/Graphics/Export.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Graphics/Transform.h>
#include <SFML/Graphics/Types.h>
#include <SFML/System/Vector2.h>

typedef struct colors_s {
    sfVector2f black;
    sfVector2f black_size;
    sfVector2f white;
    sfVector2f white_size;
    sfVector2f green;
    sfVector2f green_size;
    sfVector2f red;
    sfVector2f red_size;
    sfVector2f blue;
    sfVector2f blue_size;
    sfVector2f pen;
    sfVector2f pen_size;
} colors_t;

typedef struct s_point {
    int x;
    int y;
    sfColor color;
    float size;
    struct s_point *next;
} t_point;

typedef struct window_t {
    sfVideoMode video_mode;
    sfRenderWindow *window;
    sfTexture *texture1;
    sfSprite *base_sprite;
    sfTexture *texture2;
    sfSprite *options_sprite;
    sfTexture *texture3;
    sfSprite *dropdown1;
    sfTexture *texture4;
    sfSprite *menu_sprite;
    sfRectangleShape *back;
    sfCircleShape *circle;
    sfColor current_color;
    sfEvent event;
    sfBool draw_circle;
    sfColor sfTransBlack;
    sfRectangleShape* button_file;
    int status;
    float thickness;
} window_t;

struct button_s {
    sfRectangleShape* rect;
    sfVector2f size;
    sfVector2f pos;
    sfColor color;
    sfColor txt_color;
};

#ifndef PAINT_H_
    #define PAINT_H_
t_point *create_elem(int x, int y, struct window_t* window);
bool insert_elem(struct window_t* window, t_point **list, int x, int y);
void my_list_printer(t_point **list);
int init_csfml(void);
void display(window_t *window, t_point **points);
void handle_colors(window_t *window, colors_t *colors, sfVector2i mouse_pos);
void handle_colors2(window_t *window, colors_t *colors, sfVector2i mouse_pos);
void handle_events(window_t *window, colors_t *colors, sfVector2i *mouse_pos);
void handle_file_button(window_t *window, t_point **points);
void button_file(window_t *window);
void button_file_opt(window_t *window);
sfBool is_in(struct window_t *window, sfVector2i mouse_pos);
void free_list(t_point **points);
void rect_file(window_t *window);
void handle_thickness(window_t *window);
void draw_colors(struct window_t *window, t_point *points);
void rect_page(struct window_t *window);
int mouse_options(struct window_t* window, sfEvent event, int i);
int mini_printf(const char *format, ...);
void conditions(va_list ap, int i, const char *format, ...);
void my_putchar(char c);
int my_putstr(char *str);
int my_put_nbr(int nb);
int my_strlen(char const *str);
#endif
