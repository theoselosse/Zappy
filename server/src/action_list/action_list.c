/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** action_list
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"

action_t *create_action(double time, char *f_name, bool valid,
void (*f)(parameters_t *))
{
    action_t *tmp = xmalloc(sizeof(action_t));

    if (tmp == NULL)
        return (NULL);
    tmp = memset(tmp, 0, sizeof(action_t));
    tmp->next = NULL;
    tmp->time = time;
    tmp->size = 1;
    tmp->valid = valid;
    tmp->func_ptr = f;
    tmp->name = strdup(f_name);
    return (tmp);
}

action_t *push_action_back(action_t *head, commands_t c, int cur_fd, char *arg)
{
    action_t *tmp;
    action_t *current = head;
    int i = 1;
    int size = 2;

    tmp = create_action(c.time, c.command, c.valid, c.func_ptr);
    tmp->a = arg;
    tmp->fd = cur_fd;
    if (head == NULL)
        return tmp;
    if (head->size == 10)
        return head;
    while (current->next != NULL) {
        current = current->next;
        i++;
        size++;
    }
    tmp->position += i;
    current->next = tmp;
    head->size = size;
    return (head);
}