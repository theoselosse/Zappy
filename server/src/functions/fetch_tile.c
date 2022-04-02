/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which works with look command and fetch tiles info
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"
#include "../../include/functions.h"

char *make_res_tile(tile_t *current, char *tile_message, int first)
{
    for (int i = 0; i <= 6; i++) {
        for (int j = 1; j <= current->r[i]->nb; j++) {
            if (!(strlen(tile_message) == 0))
                tile_message = strcat(tile_message, " ");
            tile_message = strcat(tile_message, current->r[i]->name);
        }
    }
    return (tile_message);
}

char *make_pl_tile(tile_t *current, char *tile_message, int first,
client_t *list)
{
    client_t *current_cl = list;
    int count = 0;

    while (current_cl != NULL) {
        if (current_cl->x == current->x && current_cl->y == current->y) {
            if (first != 1 || count != 0)
                tile_message = strcat(tile_message, " ");
            count++;
            tile_message = strcat(tile_message, "player");
        }
        current_cl = current_cl->next;
    }
    return (tile_message);
}

int count_res_tile(tile_t *current, int length, int first)
{
    for (int i = 0; i <= 6; i++) {
        for (int j = 1; j <= current->r[i]->nb; j++) {
            length++;
            length += strlen(current->r[i]->name);
        }
    }
    return (length);
}

int count_pl_tile(tile_t *current, int length, int first, client_t *list) 
{
    client_t *current_cl = list;
    int count = 0;

    if (first == 1 || first == 2)
        length--;
    while (current_cl != NULL) {
        if (current_cl->x == current->x && current_cl->y == current->y) {
            if (first != 1 || count != 0)
                length++;
            count++;
            length += strlen("player");
        }
        current_cl = current_cl->next;
    }
    return (length);
}

char *fetch_res_tile(tile_t *current, int first, char *message, client_t *list)
{
    char *tile_message;
    int length = 2;

    length = count_pl_tile(current, length, first, list);
    length = count_res_tile(current, length, first);
    tile_message = xmalloc(sizeof(char) * (length + 1));
    if (tile_message == NULL)
        return (NULL);
    for (int i = 0; i < length + 1; i++)
        tile_message[i] = '\0';
    tile_message = make_pl_tile(current, tile_message, first, list);
    tile_message = make_res_tile(current, tile_message, first);
    if (first != 2)
        tile_message = strcat(tile_message, ",");
    tile_message[length - 1] = '\0';
    message = realloc(message, (strlen(tile_message) + strlen(message) + 2));
    message = strcat(message, tile_message);
    if (first == 2)
        message = strcat(message, "]");
    free(tile_message);
    return (message);
}