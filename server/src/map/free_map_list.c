/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** free_map_list.c
*/

#include "../../include/list.h"
#include "../../include/my.h"

void dump_map(tile_t *head, int height, int width)
{
    tile_t *current = head;
    
    for (int i = 0; i < height; i++) {
        dump_ressources(current, width);
        current = current->down;
    }
}

void free_map(tile_t *head, int height, int width)
{
    tile_t *current = head;
    tile_t *tt;

    for (int i = 0; i < height; i++) {
        tt = current;
        current = current->down;
        free_circular(tt, width);
    }
}