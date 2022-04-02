/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** arguments_parser.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../include/struct.h"
#include "../../include/my.h"

team_t **get_teams(int argc, char **argv, args_t *args, team_t **new)
{
    int nbr = 0;

    for (unsigned int i = 0; argv && argv[i]; i++) {
        if (argv[i][0] == '-')
            break;
        nbr++;
    }
    if (nbr < 2)
        return (NULL);
    new = (team_t **)malloc(sizeof(team_t *) * (nbr + 1));
    if (new == NULL)
        return (NULL);
    for (unsigned int i = 0; i < nbr; i++) {
        new[i] = malloc(sizeof(team_t));
        if (new[i] == NULL)
            return (NULL);
        new[i]->name = strdup(argv[i]);
        new[i]->max_clients = args->nb_clients;
    }
    new[nbr] = NULL;
    return (new);
}

team_t **init_teams(int argc, char **argv, args_t *args)
{
    team_t **new = NULL;

    for (unsigned int i = 0; argv && argv[i]; i++) {
        if (strncmp(argv[i], "-n", 2) == 0 && argv[i + 1] != NULL) {
            new = get_teams(argc, &argv[i + 1], args,  new);
        }
    }
    return (new);
}

int count_args(char **argv, args_t *new)
{
    int flags_nbr = 0;
    char *flags[7] = {"-p", "-x", "-y", "-c", "-f", "-n", NULL};

    for (unsigned int i = 1; argv[i] != NULL && flags[i] != NULL; i++) {
        if (strncmp(argv[i], flags[i], 2) == 0) {
            flags_nbr++;
        }
    }
    if (flags_nbr == 6)
        return (0);
    return (1);
}

args_t *check_args(int argc, char **argv)
{
    args_t *new = NULL;

    new = xmalloc(sizeof(args_t));
    if (new == NULL)
        return (NULL);
    memset(new, 0, sizeof(args_t));
    if (count_args(argv, new) != 1)
        return (NULL);
    for (unsigned int i = 0; argv && argv[i]; i++) {
        for (unsigned int j = 0; j < 5; j++) {
            if (strncmp(argv[i], arguments[j].flag, 2) == 0
                && argv[i + 1] != NULL) {
                (*arguments[j].func_ptr)(new, argv[i + 1]);
            }
        }
    }
    return (new);
}