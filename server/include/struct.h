/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** struct.h
*/

#ifndef STRUCT_H_
#define STRUCT_H_

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <time.h>
#include "functions.h"



typedef struct client_s client_t;
typedef struct tile_s tile_t;
typedef struct s_parameters parameters_t;
typedef struct commands_s command_t;

typedef struct s_team {
    char *name;
    int max_clients;
} team_t;

typedef struct args_s {
    int port;
    int width;
    int height;
    int nb_teams;
    int nb_clients;
    float frequency;
} args_t;

typedef struct s_server {
    int fd;
    struct sockaddr_in saddr;
    args_t *args;
    team_t **teams;
    // char **teams;
    client_t *all_clients;
    client_t *graphicals;
    fd_set fd_read;
    int current;
    int m_sock;
    int new_c;
    const float *freq;
    tile_t *map;
    char **cmd;

    /* time_t before;
    time_t difference;
    int msec; */
    struct timespec tstart, tend/* ={0,0}, tend={0,0} */;
    double delta;
} server_t;

typedef struct s_args_checker {
    char *flag;
    void (*func_ptr)(args_t *, char *);
} args_checker_t;

// Prototypes
void check_port(args_t *args, char *value);
void check_width(args_t *args, char *value);
void check_height(args_t *args, char *value);
void check_nb_client(args_t *args, char *value);
void check_freq(args_t *args, char *value);

static const float freq[7] = {
    0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05
};

static const args_checker_t arguments[] = {
    {"-p", &check_port},
    {"-x", &check_width},
    {"-y", &check_height},
    {"-c", &check_nb_client},
    {"-f", &check_freq},
};

#endif /* STRUCT_H_ */