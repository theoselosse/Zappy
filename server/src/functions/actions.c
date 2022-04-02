/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** actions
*/

#include "../../include/my.h"

void forward(parameters_t *p)
{
    tile_t *line = p->client->pos;

    switch (p->client->dir) {
        case 1:
            up(p->client, line);
            break;
        case 2:
            left(p->client, line);
            break;
        case 3:
            down(p->client, line);
            break;
        case 4:
            right(p->client, line);
            break;
    }
    dprintf(p->fd_cur, "ok\n");
}

void expulse(parameters_t *p)
{
    client_t *cur = p->all_clients;

    while (cur != NULL) {
        if (cur->fd != p->client->fd && cur->x == p->client->x && cur->y == p->client->y) {
            move(cur, p->client->dir, p);
        }
        else if (cur->fd != p->client->fd)
            dprintf(p->fd_cur, "ok\n");
        cur = cur->next;
    }
}

void turn_l(parameters_t *p)
{
    if (p->client->dir + 1 > 4)
        p->client->dir = 1;
    else
        p->client->dir++;
    dprintf(p->fd_cur, "ok\n");
}

void turn_r(parameters_t *p)
{
    if (p->client->dir - 1 < 1)
        p->client->dir = 4;
    else
        p->client->dir--;
    dprintf(p->fd_cur, "ok\n");
}

void inventory(parameters_t *p)
{
    /* printf("pin %d %d %d %d %d %d %d %d %d %d\n", p->client->id, p->client->x,
    p->client->y, p->client->inventory[0]->nb, p->client->inventory[1]->nb,
    p->client->inventory[2]->nb, p->client->inventory[3]->nb,
    p->client->inventory[4]->nb, p->client->inventory[5]->nb,
    p->client->inventory[6]->nb); */

    dprintf(p->fd_cur, "[%s %d, %s %d, %s %d, %s %d, %s %d, %s %d, %s %d]\n",
    p->client->inventory[1]->name, p->client->inventory[1]->nb,
    p->client->inventory[2]->name, p->client->inventory[2]->nb,
    p->client->inventory[3]->name, p->client->inventory[3]->nb,
    p->client->inventory[4]->name, p->client->inventory[4]->nb,
    p->client->inventory[5]->name, p->client->inventory[5]->nb,
    p->client->inventory[6]->name, p->client->inventory[6]->nb,
    p->client->inventory[0]->name, p->client->inventory[0]->nb);
}