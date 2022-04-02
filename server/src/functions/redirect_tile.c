/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions which redirect tiles orientation
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/list.h"
#include "../../include/struct.h"
#include "../../include/my.h"
#include "../../include/functions.h"

int compute_dir_three(int dir, client_t *client)
{
    if (client->dir == 4) {
        switch(dir) {
            case 1:
                return (2);
                break;
            case 2:
                return (3);
                break;
            case 3:
                return (4);
                break;
            case 4:
                return (1);
                break;
        }
    }
}

tile_t *redirect_step_three(tile_t *current, int direction, int step)
{
    switch(direction) {
            case 1:
                return (current->right);
            case 2:
                return (current->up);
            case 3:
                return (current->left);
            case 4:
                return (current->down);
    }
}

tile_t *redirect_step_two(tile_t *current, int direction, int step)
{
    switch(direction) {
        case 1:
            return (current->left);
        case 2:
            return (current->down);
        case 3:
            return (current->right);
        case 4:
            return (current->up);
    }
}

tile_t *redirect_step_one(tile_t *current, int direction, int step)
{
    if (step == 1) {
        switch(direction) {
            case 1:
                return (current->up);
            case 2:
                return (current->left);
            case 3:
                return (current->down);
            case 4:
                return (current->right);
        }
    } else if (step == 2)
        return (redirect_step_two(current, direction, step));
    else
        return (redirect_step_three(current, direction, step));
}