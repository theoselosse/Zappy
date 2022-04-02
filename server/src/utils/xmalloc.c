/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** xmalloc.c
*/

#include <stdlib.h>
#include <unistd.h>
#include "../../include/my.h"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (ptr == NULL)
        return (write(2, "Malloc failed\n", 15), NULL);
    return (ptr);
}