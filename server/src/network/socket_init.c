/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** socket_init.c
*/

#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/struct.h"
#include "../../include/my.h"

server_t *binding_and_listening(server_t *new)
{
    if (bind(new->fd,
        (struct sockaddr *)&new->saddr, sizeof(struct sockaddr)) == -1) {
        free(new);
        return (write(2, "Can't bind to this port\n", 25), NULL);
    }
    if (listen(new->fd, 10) == -1) {
        free(new);
        return (write(2, "Listen failed\n", 15), NULL);
    }
    return (new);
}

server_t *init_server_addr(int port, server_t *new)
{
    memset(&new->saddr, 0, sizeof(new->saddr));
    new->saddr.sin_family = AF_INET;
    new->saddr.sin_port = htons(port);
    new->saddr.sin_addr.s_addr = INADDR_ANY;
    return (binding_and_listening(new));
}

int accept_socket(server_t *serv)
{
    int addrlen = sizeof(serv->saddr);

    if ((serv->new_c = accept(serv->fd,
        (struct sockaddr *) &serv->saddr, (socklen_t *) &addrlen)) < 0) {
        perror("accept() error");
        return -1;
    }
    return 0;
}

server_t *init_server(int port)
{
    server_t *new = NULL;

    if (port < 1 || port > 65535)
        return (write(2, "Port must be between 1 and 65535\n", 34), NULL);
    new = (server_t *)malloc(sizeof(server_t));
    if (new == NULL)
        return (write(2, "Malloc failed\n", 15), NULL);
    new->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (new->fd == -1) {
        free(new);
        return (write(2, "Socket creation failed\n", 24), NULL);
    }
    if (setsockopt(new->fd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) == -1) {
        free(new);
        return (write(2, "Setsockopt failed\n", 19), NULL);
    }
    return (init_server_addr(port, new));
}

void exit_client(server_t *serv, int fd)
{
    dprintf(fd, "Destroying #%d\n", get_current(serv->all_clients, serv->current)->id);
    if (close(fd) == -1) {
        perror("close(): ");
    }
    serv->all_clients = remove_at(serv->all_clients, fd);
}