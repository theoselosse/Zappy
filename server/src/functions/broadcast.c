/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which works with broadcast command
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"
#include "../../include/functions.h"

int get_dir(int x1, int y1, int x2, int y2)
{
    int x3 = x1 - x2;
    int y3 = y1 - y2;
    int final;

    if (x3 > 0)
        return (4);
    else if (x3 < 0)
        return (2);
    else {
        if (y3 > 0)
            return (1);
        else if (y3 < 0)
            return (3);
        else
            return (-1);
    }
    return (-2);
}

int compute_dir_two(int dir, client_t *client)
{
    if (client->dir == 3) {
        switch (dir) {
            case 1:
                return (3);
                break;
            case 2:
                return (4);
                break;
            case 3:
                return (1);
                break;
            case 4:
                return (2);
                break;
        }
    }
}

int compute_dir_one(int dir, client_t *client)
{
    if (client->dir == 2) {
        switch (dir) {
            case 1:
                return (4);
                break;
            case 2:
                return (1);
                break;
            case 3:
                return (2);
                break;
            case 4:
                return (3);
                break;
        }
    } else if (client->dir == 3)
        return (compute_dir_two(dir, client));
    else
        return (compute_dir_three(dir, client));
}

void deploy(parameters_t *p, char *message)
{
    client_t *client = p->client;
    client_t *current = p->all_clients;
    int	dir;

    while (current != NULL) {
        if (current->fd != client->fd) {
            dir = get_dir(client->x, client->y, current->x, current->y);
            if (client->dir != 1)
                dir = compute_dir_one(dir, current);
	        dprintf(p->fd_cur, "%s %d\n", message, dir);
	    }
        current = current->next;
	}
}

void broadcast(parameters_t *p)
{
    if (p->arg == NULL)
        return;
    char *message = NULL;

    if (p->arg == NULL) {
        message = strdup(p->arg);
        deploy(p, message);
        //rfc_graph_pbc(z, c, msg);
        dprintf(p->fd_cur, "ko\n");
        free(message);
        return;
    } else
        dprintf(p->fd_cur, "ko\n");
    printf("broadcast\n");
}