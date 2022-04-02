/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which works with look command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"
#include "../../include/functions.h"

char *alloc_tot_lgt(tile_t *current, char *message, client_t *current_c,
int elevation)
{
    message = xmalloc(sizeof(char) * 2);
    message[1] = '\0';
    message[0] = '[';
    return (message);
}

char *look_cat_tiles(tile_t *current, int elevation, client_t *current_c,
client_t *list)
{
    int nbr_tiles = 3;
    char *message = alloc_tot_lgt(current, message, current_c, elevation);
    tile_t *tmp = current;

    message = fetch_res_tile(current, 1, message, list);
    for (int i = elevation; i >= 1; i--, nbr_tiles += 2) {
        current = tmp;
        current = redirect_step_one(current, current_c->dir, 1);
        current = redirect_step_one(current, current_c->dir, 2);
        message = fetch_res_tile(current, 0, message, list);
        tmp = current;
        for (int y = 1; y < nbr_tiles - 1; y++) {
            current = redirect_step_one(current, current_c->dir, 3);
            message = fetch_res_tile(current, 0, message, list);
        }
        current = redirect_step_one(current, current_c->dir, 3);
        message = fetch_res_tile(current, 2, message, list);
    }
    return (message);
}

void look(parameters_t *p)
{
    client_t *current_c = p->client;
    tile_t *current_t = p->client->pos;
    char *message;

    message = look_cat_tiles(current_t, current_c->elevation, current_c,
    p->all_clients);
    dprintf(p->fd_cur, "%s\n", message);
    free(message);
}