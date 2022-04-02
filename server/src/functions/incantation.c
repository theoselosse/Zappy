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

void incantation_part2(parameters_t *p)
{
    switch(p->client->elevation) {
            case 5:
                incant_lvl_six(p);
                break;
            case 6:
                incant_lvl_seven(p);
                break;
            case 7:
                incant_lvl_height(p);
                break;
            default:
                dprintf(p->client->fd, "ko\n");
                break;
    }
}

void incant_lvl_height(parameters_t *p)
{
    int requirements[7] = {6, 2, 2, 2, 2, 2, 1};
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
    p->client->elevation = 8;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 8);
}

void incant_lvl_seven(parameters_t *p)
{
    int requirements[7] = {6, 1, 2, 3, 0, 1, 0};
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
    p->client->elevation = 7;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 7);
}

void incant_lvl_six(parameters_t *p)
{
    int requirements[7] = {4, 1, 2, 1, 3, 0, 0};
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
    p->client->elevation = 6;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 6);
}

void incant_lvl_five(parameters_t *p)
{
    int requirements[7] = {4, 1, 1, 2, 0, 1, 0};
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
    p->client->elevation = 5;
    dprintf(p->fd_cur, "Elevation underway\n");
    dprintf(p->fd_cur, "Current level:%d\n", 5);
}