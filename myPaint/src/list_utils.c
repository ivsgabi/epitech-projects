/*
** EPITECH PROJECT, 2023
** list_utils
** File description:
** lists handling in my_paint
*/

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/paint.h"

t_point *create_elem(int x, int y, struct window_t *window)
{
    t_point *node = malloc(sizeof(t_point));

    if (node == NULL)
        return NULL;
    node->x = x;
    node->y = y;
    node->color = window->current_color;
    node->size = window->thickness;
    node->next = NULL;
    return node;
}

bool insert_elem(struct window_t *window, t_point **list, int x, int y)
{
    t_point *node = create_elem(x, y, window);
    t_point *tmp;

    if (node == NULL)
        return false;
    if (*list == NULL) {
        *list = node;
    } else {
        for (tmp = *list; tmp->next != NULL; tmp = tmp->next);
        tmp->next = node;
    }
    return true;
}

void my_list_printer(t_point **list)
{
    my_putchar('\n');
    t_point *temp = *list;
    while (temp != NULL) {
        mini_printf("[x: %d - y: %d]", temp->x, temp->y);
        temp = temp->next;
    }
    my_putchar('\n');
}

void free_list(t_point **points)
{
    t_point *list = *points;
    t_point *tmp;
    while (list != NULL) {
        tmp = list;
        list = list->next;
        free(tmp);
    } *points = NULL;
}
