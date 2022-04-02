/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** arguments_checker.c
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../../include/struct.h"
#include "../../include/my.h"

void check_port(args_t *args, char *value)
{
    for (int i = 0; value[i]; i++) {
        if (value[i] < '0' || value[i] > '9') {
            fprintf(stderr, "port must be a positive number\n");
            exit(84);
        }
    }
    args->port = atoi(value);
    if (args->port <= 0) {
        fprintf(stderr, "port must be a positive number\n");
        exit(84);
    }
}

void check_width(args_t *args, char *value)
{
    for (int i = 0; value[i]; i++) {
        if (value[i] < '0' || value[i] > '9') {
            fprintf(stderr, "width must be a positive number\n");
            exit(84);
        }
    }
    args->width = atoi(value);
    if (args->width <= 0) {
        fprintf(stderr, "width must be a positive number\n");
        exit(84);
    }
}

void check_height(args_t *args, char *value)
{
    for (int i = 0; value[i]; i++) {
        if (value[i] < '0' || value[i] > '9') {
            fprintf(stderr, "height must be a positive number\n");
            exit(84);
        }
    }
    args->height = atoi(value);
    if (args->height <= 0) {
        fprintf(stderr, "height must be a positive number\n");
        exit(84);
    }
}

void check_nb_client(args_t *args, char *value)
{
    for (int i = 0; value[i]; i++) {
        if (value[i] < '0' || value[i] > '9') {
            fprintf(stderr, "nb_client must be a positive number\n");
            exit(84);
        }
    }
    args->nb_clients = atoi(value);
    if (args->nb_clients <= 0) {
        fprintf(stderr, "nb_client must be a positive number\n");
        exit(84);
    }
}

void check_freq(args_t *args, char *value)
{
    for (int i = 0; value[i]; i++) {
        if (((value[i] != '.' && value[i] < '0') || value[i] > '9')) {
            fprintf(stderr, "frequency must be a positive number\n");
            exit(84);
        }
    }
    args->frequency = atof(value);
    if (args->frequency <= 0) {
        fprintf(stderr, "frequency must be a positive number\n");
        exit(84);
    }
}