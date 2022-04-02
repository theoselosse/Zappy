/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** server_events
*/

#include "../../include/my.h"

void teams(parameters_t *p)
{
    bool f = false;
    int z = 0;

    if (strncmp(p->arg, "debug", 6) == 0) {
        dprintf(p->fd_cur, "%d\n", -1);
        return;
    }
    for (int i = 0; p->teams && p->teams[i]; i++) {
        if (strncmp(p->teams[i]->name, p->arg, strlen(p->teams[i]->name)) == 0) {
            dprintf(p->fd_cur, "%d\n", p->teams[i]->max_clients);
            f = true;
            z = i;
            free(p->client->t_name);
            p->client->t_name = strdup(p->teams[i]->name);
        }
    }
    if (!f || p->teams[z]->max_clients <= 0)
        exit_client(p->serv, p->client->fd);
    p->teams[z]->max_clients--;
}

void new_player(parameters_t *p)
{
    printf("pnw #%d %d %d %d %d %s\n", p->client->id, p->client->x,
    p->client->y, p->client->dir, p->client->elevation, p->client->t_name);
    /* dprintf(p->client->fd, "pnw #%d %d %d %d %d %s\n", p->client->id,
    p->client->x, p->client->y,
    p->client->dir, p->client->elevation, p->client->t_name); */
}

void map_sz(client_t *client, int width, int height)
{
    printf("msz %d %d\n", width, height);
    dprintf(client->fd, "msz %d %d\n", width, height);
}


void unknown(parameters_t *p)
{
    dprintf(p->fd_cur, "unknown command\n");
}

void tiles_content(parameters_t *p)
{
    tile_t *current = p->map;
    tile_t *line;

    for (int i = 0; i < p->h; i++) {
        line = current;
        for (int j = 0; j < p->w; j++) {
            printf("bct %d %d %d %d %d %d %d %d %d\n", line->x, line->y,
            line->r[0]->nb, line->r[1]->nb, line->r[2]->nb,
            line->r[3]->nb, line->r[4]->nb, line->r[5]->nb, line->r[6]->nb);
            line = line->right;
        }
        current = current->down;
    }
}