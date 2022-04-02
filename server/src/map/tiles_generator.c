/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** tile
*/

#include <stdlib.h>
#include <stdio.h>
#include "../../include/list.h"

void add_back(tile_t *list)
{
    tile_t *current = list;
    tile_t *new = NULL;

    while (current->right != NULL)
        current = current->right;
    new = malloc(sizeof(tile_t));
    if (!new)
        exit(84);
    new->right = NULL;
    new->left = current;
    new = setup_tile_res(new);
    current->right = new;
    current->right->x = current->x + 1;
    current->right->y = current->y;
    current->right->right = NULL;
}

tile_t *create_list(int size, int y)
{
    tile_t *list = malloc(sizeof(tile_t));

    if (!list) {
        fprintf(stderr, "%s\n", "Malloc failed");
        exit(84);
    }
    list->x = 0;
    list->y = y;
    list->left = NULL;
    list->right = NULL;
    list->up = NULL;
    list->down = NULL;
    list->nb_p = 0;
    list = setup_tile_res(list);
    if (size < 1) {
        fprintf(stderr, "%s\n", "Size of the list too small");
        exit(84);
    }
    for (int i = 0; i < size - 1; i++)
        add_back(list);
    return (list);
}

void circular(tile_t *head)
{
    tile_t *current = head;

    while (current->right != NULL)
        current = current->right;
    head->left = current;
    current->right = head;
}

void linking(tile_t *fi, tile_t *se, int size)
{
    tile_t *f = fi;
    tile_t *s = se;
    int i = 0;

    if (s == NULL) {
        while (i < size) {
            f->up = f;
            f->down = f;
            i++;
        }
        return;
    } else {
        while (i < size) {
            f->down = s;
            s->up = f;
            f = f->right;
            s = s->right;
            i++;
        }
    }
}

tile_t *create_map(int av1, int av2)
{
    int y = 0;
    int width;
    int height;
    tile_t *first;
    tile_t *second = NULL;
    tile_t *current = NULL;
    tile_t *tt;
    tile_t *map = NULL;


    width = av1;
    height = av2;
    map = create_list(width, y);
    circular(map);
    first = map;
    for (int i = 0; i < height; i++, y++) {
        if (i == 0) {
            linking(first, NULL, width);
        } else if (i == 1) {
            second = create_list(width, y);
            circular(second);
            linking(first, second, width);
        } else {
            second = create_list(width, y);
            circular(second);
            linking(first, second, width);
            linking(second, map, width);
        }
        first = first->down;
    }
    return (map);
}