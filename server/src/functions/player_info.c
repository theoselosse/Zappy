/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** player_info
*/

#include "../../include/my.h"

void drop(parameters_t *p)
{
    if (p->arg == NULL)
        return;
    int res = atoi(p->arg);

    if (res < 0 || res >= 7) {
        printf("ko\n");
        dprintf(p->fd_cur, "ko\n");
        return;
    }
    if (p->client->inventory[res]->nb > 0) {
        printf("ok\n");
        dprintf(p->fd_cur, "ok\n");
        p->client->inventory[res]->nb--;
        p->client->pos->r[res]->nb++;
    } else {
        printf("ko\n");
        dprintf(p->fd_cur, "ko\n");
    }
    update_file(p->map, p->w, p->h, p->all_clients);
}

void pickup(parameters_t *p)
{
    if (p->arg == NULL)
        return;
    int res = atoi(p->arg);

    if (res < 0 || res >= 7) {
        printf("ko\n");
        dprintf(p->fd_cur, "ko\n");
        return;
    }
    if (p->client->pos->r[res]->nb > 0) {
        printf("ok\n");
        p->client->pos->r[res]->nb--;
        p->client->inventory[res]->nb++;
        dprintf(p->fd_cur, "ok\n");
    } else {
        printf("ko\n");
        dprintf(p->fd_cur, "ko\n");
    }
    update_file(p->map, p->w, p->h, p->all_clients);
}

void dead(parameters_t *params)
{
    printf("dead\n");
    dprintf(params->fd_cur, "dead\n");
}

void position(parameters_t *p)
{
    printf("ppo %d %d %d %d\n", p->client->id, p->client->x,
    p->client->y, p->client->dir);
    //dprintf(p->client->fd, "ppo %d %d %d %d\n", p->client->id,
    //p->client->x, p->client->y, , p->client->dir);
}

void level(parameters_t *p)
{
    printf("plv %d %d\n", p->client->id, p->client->elevation);
    //dprintf(p->client->fd, "plv %d %d\n", p->client->id, p->client->elevation);
}