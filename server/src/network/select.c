/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** select
*/

#include "../../include/my.h"

void select_client(server_t *serv)
{
    int activity;
    client_t *client = serv->all_clients;

    FD_ZERO(&serv->fd_read);
    FD_SET(serv->fd, &serv->fd_read);
    while (client != NULL) {
        serv->current = client->fd;
        if (serv->current > 0)
            FD_SET(serv->current, &serv->fd_read);
        if (serv->current > serv->m_sock)
            serv->m_sock = serv->current;
        client = client->next;
    }
    activity = select(serv->m_sock + 1, &serv->fd_read, NULL, NULL, NULL);
    if (activity < 0 && errno != EINTR)
        perror("select() error");
}

client_t *get_current(client_t *clients, int current)
{
    client_t *client = clients;

    while (client != NULL) {
        if (client->fd == current)
            return client;
        client = client->next;
    }
    return NULL;
}

client_t *end_ntm(server_t *server, char *buffer, int length)
{
    exit_client(server, server->current);
    server->all_clients = remove_at(server->all_clients, server->current);
    server->all_clients = is_active(server, server->saddr);
    return (server->all_clients);
}

client_t *is_active(server_t *serv, struct sockaddr_in addr)
{
    int msg_size;
    char buffer[1025];
    client_t *client = serv->all_clients;
    parameters_t *params = NULL;

    while (client != NULL) {
        serv->current = client->fd;
        if (FD_ISSET(serv->current, &serv->fd_read)) {
            if ((msg_size = read(serv->current, buffer, 1024)) == 0) {
                serv->all_clients = end_ntm(serv, buffer, msg_size);
            } else {
                buffer[msg_size] = '\0';
                check_cmd(serv, buffer);
                if (get_current(serv->all_clients, serv->current)->quitting == true)
                    serv->all_clients = end_ntm(serv, buffer, msg_size);
                clock_gettime(CLOCK_MONOTONIC, &serv->tend);
                serv->delta = ((double)serv->tend.tv_sec + 1.0e-9 * serv->tend.tv_nsec) - 
                ((double)serv->tstart.tv_sec + 1.0e-9 * serv->tstart.tv_nsec);
                params = malloc(sizeof(parameters_t));
                params = setup_param(params, serv, client, serv->cmd);
                passing_time(serv, params);
                client_t *current = serv->all_clients;
                update_file(serv->map, serv->args->width, serv->args->height,
                serv->all_clients);
                /* printf("%f\n", params->client->life);
                if (params->client->life == -1)
                    exit_client(serv, serv->current); */
                free(params);
                //printf("it took about %.5f seconds\n", serv->delta);
            }
        }
        client = client->next;
    }
    return serv->all_clients;
}

int accept_client(server_t *serv)
{
    int max_clients = 30;
    char *msg = "Welcome on Zappy\r\n";
    parameters_t *params = NULL;

    while (1) {
        //serv->before = clock();
        clock_gettime(CLOCK_MONOTONIC, &serv->tstart);
        select_client(serv);
        if (FD_ISSET(serv->fd, &serv->fd_read)) {
            if (accept_socket(serv) == -1)
                return -1;
            printf("Connection from %s", inet_ntoa(serv->saddr.sin_addr));
            printf(":%d\n", ntohs(serv->saddr.sin_port));
            if (write(serv->new_c, msg, strlen(msg)) == -1)
                perror("write() error");
            serv->all_clients = push_back(serv->all_clients, serv->new_c, serv->map, serv->args->frequency);
            update_file(serv->map, serv->args->width, serv->args->height, serv->all_clients);
        }
        serv->all_clients = is_active(serv, serv->saddr);
    }
    return 0;
}