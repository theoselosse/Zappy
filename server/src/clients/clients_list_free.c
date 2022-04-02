/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** free clients linked list
*/

#include "../../include/list.h"

void free_one_client(client_t *tmp)
{
    tmp->pos->nb_p--;
    free(tmp->t_name);
    for (int i = 0; i <= 6; i++) {
        free(tmp->inventory[i]->name);
        free(tmp->inventory[i]);
    }
    free(tmp->inventory);
    free(tmp);
}

void free_clients(client_t *head)
{
    client_t* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free_one_client(tmp);
    }
}

client_t *remove_first(client_t *head, int fd)
{
    client_t *current = head;
    client_t *return_current;

    if (head == NULL)
        return (head);
    if (current->fd == fd) {
        return_current = head->next;
        free_one_client(current);
        return (return_current);
    }
    return (return_current);
}

client_t *free_last_client(client_t *current, client_t *previous, client_t *head)
{
    free_one_client(current);
    previous->next = NULL;
    return (head);
}

client_t *remove_at(client_t *head, int fd)
{
    client_t *current = head;
    client_t *previous = head;

    if (head == NULL || head->fd == fd)
        return (remove_first(head, fd));
    for (int i = 0; current != NULL; i++) {
        if (fd == current->fd) {
            if (current->next != NULL) {
                previous->next = current->next;
                free_one_client(current);
                return (head);
            }
        }
        if (fd == current->fd && current->next == NULL)
            return (free_last_client(current, previous, head));
        if (i != 0)
            previous = previous->next;
        current = current->next;
    }
    return (head);
}