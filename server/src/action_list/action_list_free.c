/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** action_list_free
*/

#include "../../include/list.h"
#include <stdio.h>

void free_one_action(action_t *tmp)
{
    free(tmp->name);
    free(tmp);
}

void free_actions(action_t *head)
{
    action_t* tmp;

    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        free_one_action(tmp);
    }
}

action_t *remove_first_a(action_t *head)
{
    action_t *current = head;
    action_t *return_current;
    int size = 0;

    if (head == NULL)
        return (head);
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    size = head->size - 1;
    return_current = head->next;
    return_current->size = size;
    return_current->position--;
    free_one_action(current);
    return (return_current);
}

void dump_actions(action_t *head)
{
    action_t *current = head;

    if (head == NULL) {
        printf("empty\n");
        return;
    }
    while (current != NULL) {
        printf("name: %s %d\n", current->name, current->position);
        current = current->next;
    }
}