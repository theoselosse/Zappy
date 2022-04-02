/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which works with incantation command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"
#include "../../include/functions.h"

void incant_lvl_four(parameters_t *p)
{
    int requirements[7] = {2, 2, 0, 1, 0, 2, 0};
    int info[7];

    info[0] = fetch_nbr_pl(p->all_clients, p->client->pos);
    info[1] = p->client->pos->r[1]->nb;
    info[2] = p->client->pos->r[2]->nb;
    info[3] = p->client->pos->r[3]->nb;
    info[4] = p->client->pos->r[4]->nb;
    info[5] = p->client->pos->r[5]->nb;
    info[6] = p->client->pos->r[6]->nb;
    for (int i = 0; i < 7; i++) {
        if (info[i] != requirements[i])
            dprintf(p->fd_cur, "ko\n");
            return;
    }
    p->client->elevation = 4;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 4);
}

void incant_lvl_three(parameters_t *p)
{
    int requirements[7] = {2, 1, 1, 1, 0, 0, 0};
    int info[7];

    info[0] = fetch_nbr_pl(p->all_clients, p->client->pos);
    info[1] = p->client->pos->r[1]->nb;
    info[2] = p->client->pos->r[2]->nb;
    info[3] = p->client->pos->r[3]->nb;
    info[4] = p->client->pos->r[4]->nb;
    info[5] = p->client->pos->r[5]->nb;
    info[6] = p->client->pos->r[6]->nb;
    for (int i = 0; i < 7; i++) {
        if (info[i] != requirements[i])
            dprintf(p->fd_cur, "ko\n");
            return;
    }
    p->client->elevation = 3;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 3);
}

void incant_lvl_two(parameters_t *p)
{
    int requirements[7] = {1, 1, 0, 0, 0, 0, 0};
    int info[7];

    info[0] = fetch_nbr_pl(p->all_clients, p->client->pos);
    info[1] = p->client->pos->r[1]->nb;
    info[2] = p->client->pos->r[2]->nb;
    info[3] = p->client->pos->r[3]->nb;
    info[4] = p->client->pos->r[4]->nb;
    info[5] = p->client->pos->r[5]->nb;
    info[6] = p->client->pos->r[6]->nb;
    for (int i = 0; i < 7; i++) {
        if (info[i] != requirements[i])
            dprintf(p->fd_cur, "ko\n");
            return;
    }
    p->client->elevation = 2;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 2);
}

void incantation(parameters_t *p)
{
    switch(p->client->elevation) {
            case 1:
                incant_lvl_two(p);
                break;
            case 2:
                incant_lvl_three(p);
                break;
            case 3:
                incant_lvl_four(p);
                break;
            case 4:
                incant_lvl_five(p);
                break;
            default:
                incantation_part2(p);
                break;
    }
}

int fetch_nbr_pl(client_t *list, tile_t *pos) 
{
    int count = 0;
    client_t *current = list;

    while (current  != NULL) {
        if (pos->x == current->x && pos->y == current->y)
            count++;
        current = current->next;
    }
    return (count);
}