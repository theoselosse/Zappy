
/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** map_utils.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../../include/list.h"
#include "../../include/my.h"

tile_t *get_cur_node(tile_t *map, int x, int y, int w, int h)
{
    tile_t *line;
    tile_t *current = map;

    for (int i = 0; i < h; i++) {
        line = current;
        for (int j = 0; j < w; j++) {
            if (line->x == x)
                break;
            line = line->right;
        }
        if (line->y == y && line->x == x)
            break;
        current = current->down;
    }
    return line;
}

void disp_high(FILE *f, client_t *current, int w, int h)
{
    client_t *client = current;
    client_t max;

    if (current == NULL)
        return;
    max = *client;
    while (client != NULL) {
        if (client->x == w && client->y == h) {
            //max = *client;
            fprintf(f, "%s;%d;%d/", client->t_name, client->elevation, client->dir);
        }
        client = client->next;
    }
}

bool is_p(int v)
{
    return (v > 0);
}

void update_file(tile_t *head, int w, int h, client_t *clients)
{
    tile_t *map = head;
    tile_t *l;
    FILE *f;

    f = fopen("map.txt", "w+");
    if (f == NULL) {
        perror("fopen():");
        return;
    }
    fprintf(f, "%d:%d\n", h, w);
    for (int i = 0; i < h; i++) {
        l = map;
        for (int j = 0; j < w; j++) {
            fprintf(f, "%d,%d#%d%d%d%d%d%d%d:%d|", l->x, l->y, is_p(l->r[0]->nb),
            is_p(l->r[1]->nb), is_p(l->r[2]->nb), is_p(l->r[3]->nb),
            is_p(l->r[4]->nb),
            is_p(l->r[5]->nb), is_p(l->r[6]->nb), l->nb_p);
            disp_high(f, clients, j, i);
            fprintf(f, "\n");
            l = l->right;
        }
        map = map->down;
    }
    fclose(f);
}