/*
** EPITECH PROJECT, 2021
** server
** File description:
** command_handling
*/

#include "../../include/my.h"

void passing_time(server_t *serv, parameters_t *p)
{
    client_t *client = serv->all_clients;

    while (client != NULL) {
        if (client->actions != NULL) {
            p->fd_cur = client->actions->fd;
            //printf("#%d name: %s time: %f\n", client->id,
            //client->actions->name, client->actions->time);
            client->actions->time -= (serv->delta * 1000);
            /* client->life -= serv->delta * 1000;
            if (client->life <= 0)
                client->life = (double)-1; */
            if (client->actions->time <= 0)
                client->actions->time = (double)-1;
            //printf("#%d name: %s new_time: %f\n", client->id,
            //client->actions->name, client->actions->time);
            p->arg = client->actions->a;
            if (client->actions->time == -1) {
                client->actions->func_ptr(p);
                client->actions = remove_first_a(client->actions);
            }
        }
        client = client->next;
    }
}

client_t *get_current_c(client_t *clients, int fd)
{
    client_t *current = clients;

    while (current != NULL) {
        if (current->fd == fd)
            return current;
        current = current->next;
    }
    return NULL;
}

parameters_t *setup_param(parameters_t *params, server_t *serv,
client_t *client, char **cmd)
{
    params->serv = serv;
    params->all_clients = serv->all_clients;
    params->map = serv->map;
    params->w = serv->args->width;
    params->h = serv->args->height;
    params->client = client;
    params->teams = serv->teams;
    params->freq = serv->args->frequency;
    if (cmd[0] != NULL && cmd[1] != NULL)
        params->arg = cmd[1];
}

int check_cmd(server_t *serv, char *buffer)
{
    char **cmd = str_to_word_array(buffer, " \t\n");
    client_t *client = get_current(serv->all_clients, serv->current);
    char *arg;

    if (cmd[0][0] == '\0')
        return 1;
    if (cmd[1] != NULL)
        arg = cmd[1];
    serv->cmd = cmd;
    for (int i = 0; i < 16; i++) {
        if (strncmp(cmd[0], commands[i].command,
        strlen(commands[i].command)) == 0) {
            client->actions = push_action_back(client->actions, commands[i], serv->current, arg);
            return 1;
        }
    }
    return 1;
}