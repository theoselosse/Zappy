/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** map_utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../include/list.h"
#include "../../include/my.h"

void dump_circular(tile_t *list, int size)
{
    tile_t *current = list;
    int i = 0;

    while (i < size) {
        printf("x:%d\ty:%d\n", current->x, current->y);
        current = current->right;
        i++;
    }
    printf("\n");
}

void dump_reverse(tile_t *list)
{
    tile_t *current = list;

    while (current->right != NULL)
        current = current->right;
    while (current != NULL) {
        printf("x:%d\ty:%d\n", current->x, current->y);
        current = current->left;
    }
}

void dump(tile_t *list)
{
    tile_t *current = list;

    while (current != NULL) {
        printf("x:%d\ty:%d\n", current->x, current->y);
        current = current->right;
    }
    printf("\n");
}

void dump_ressources(tile_t *list, int size)
{
    tile_t *current = list;
    int i = 0;

    while (i < size) {
        //printf("x:%d y:%d %c:%d\n", current->x, current->y, current->r[0].name[0], current->r[1].nb, current->r[1].name[0], current->r[2].nb, current->r[2].name[0], current->r[3].nb, current->r[3].name[0], current->r[4].nb, current->r[4].name[0], current->r[5].nb, current->r[5].name[0], current->r[6].nb, current->r[6].name[0], current->r[6].nb);
        printf("x:%d y:%d %c:%d\n", current->x, current->y, current->r[0]->name[0], current->r[0]->nb);
        current = current->right;
        i++;
    }
    printf("\n");
}

void free_circular(tile_t *list, int size)
{
    tile_t *current = list;
    tile_t *tmp;
    int i = 0;

    while (i < size) {
        tmp = current;
        current = current->right;
        free(tmp->r[0]->name);
        free(tmp->r[1]->name);
        free(tmp->r[2]->name);
        free(tmp->r[3]->name);
        free(tmp->r[4]->name);
        free(tmp->r[5]->name);
        free(tmp->r[6]->name);

        free(tmp->r[0]);
        free(tmp->r[1]);
        free(tmp->r[2]);
        free(tmp->r[3]);
        free(tmp->r[4]);
        free(tmp->r[5]);
        free(tmp->r[6]);
        free(tmp->r);
        free(tmp);
        i++;
    }
}