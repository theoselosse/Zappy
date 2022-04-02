/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** clients_list.c
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"

client_t *create_node(int fd, float freq, tile_t *pos)
{
    client_t *tmp = xmalloc(sizeof(client_t));

    if (tmp == NULL)
        return (NULL);
    tmp = memset(tmp, 0, sizeof(client_t));
    tmp->next = NULL;
    tmp->fd = fd;
    tmp->pos = pos;
    tmp->pos->nb_p++;
    //tmp->life = 126000 / freq;
    tmp->t_name = strdup("NONE");
    tmp->elevation = 1;
    tmp->dir = 4;
    tmp->quitting = false;

    tmp = setup_tile_res_cl(tmp);
    return (tmp);
}

client_t *push_back(client_t *head, int fd, tile_t *pos, float freq)
{
    client_t *tmp;
    client_t *current = head;
    int i = 1;

    tmp = create_node(fd, freq, pos);
    if (head == NULL)
        return tmp;
    while (current->next != NULL) {
        if (current->fd == fd) {
            if (tmp != NULL)
                free_one_client(tmp);
            return (head);
        }
        current = current->next;
        i++;
    }
    tmp->id += i;
    current->next = tmp;
    return (head);
}