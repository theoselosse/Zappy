/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** moving
*/

#include "../../include/my.h"

void up(client_t *client, tile_t *line)
{   
    client->pos->nb_p--;
    client->pos = client->pos->up;
    client->pos->nb_p++;
    client->y = client->pos->y;
    client->x = client->pos->x;
}

void down(client_t *client, tile_t *line)
{
    client->pos->nb_p--;
    client->pos = client->pos->down;
    client->pos->nb_p++;
    client->y = client->pos->y;
    client->x = client->pos->x;
}

void left(client_t *client, tile_t *line)
{
    client->pos->nb_p--;
    client->pos = client->pos->left;
    client->pos->nb_p++;
    client->y = client->pos->y;
    client->x = client->pos->x;
}

void right(client_t *client, tile_t *line)
{
    client->pos->nb_p--;
    client->pos = client->pos->right;
    client->pos->nb_p++;
    client->y = client->pos->y;
    client->x = client->pos->x;
}

void move(client_t *client, int dir, parameters_t *args)
{
    tile_t *line = NULL;

    switch (dir) {
        case 1:
            up(client, line);
            break;
        case 2:
            left(client, line);
            break;
        case 3:
            down(client, line);
            break;
        case 4:
            right(client, line);
            break;
    }
    dprintf(client->fd, "ok\n");
    update_file(args->map, args->w, args->h, args->all_clients);
}