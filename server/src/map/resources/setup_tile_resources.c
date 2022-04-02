/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which manage resources
*/

#include <string.h>
#include <stdlib.h>
#include "../../../include/list.h"
#include "../../../include/my.h"

tile_t *setup_tile_res(tile_t *current)
{
    char *resources_list[8] = {"food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", NULL};

    current->r = xmalloc(sizeof(resource_t) * 8);
    if (current->r == NULL)
        return (NULL);
    current->r[7] = NULL;
    for (int i = 0; resources_list[i] != NULL; i++) {
        current->r[i] = xmalloc(sizeof(resource_t));
        if (current->r[i] == NULL)
            return (NULL);
        current->r[i]->name = strdup(resources_list[i]);
        current->r[i]->nb = 0;
    }
    return (current);
}

client_t *setup_tile_res_cl(client_t *current)
{
    char *resources_list[8] = {"food", "linemate", "deraumere", "sibur",
    "mendiane", "phiras", "thystame", NULL};

    current->inventory = xmalloc(sizeof(resource_t) * 8);
    if (current->inventory == NULL)
        return (NULL);
    current->inventory[7] = NULL;
    for (int i = 0; resources_list[i] != NULL; i++) {
        current->inventory[i] = xmalloc(sizeof(resource_t));
        if (current->inventory[i] == NULL)
            return (NULL);
        current->inventory[i]->name = strdup(resources_list[i]);
        current->inventory[i]->nb = 0;
    }
    return (current);
}