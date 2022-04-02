/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#include <time.h>
#include <sys/time.h>

#include "struct.h"
#include "list.h"
#include "functions.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// arguments/arguments_checker.c
void check_port(args_t *args, char *value);
void check_width(args_t *args, char *value);
void check_height(args_t *args, char *value);
void check_nb_client(args_t *args, char *value);
void check_freq(args_t *args, char *value);

int check_cmd(server_t *serv, char *buffer);
void passing_time(server_t *serv, parameters_t *p);
parameters_t *setup_param(parameters_t *params, server_t *serv,
client_t *client, char **cmd);

// arguments/arguments_parser.c
team_t **get_teams(int argc, char **argv, args_t *args, team_t **new);
team_t **init_teams(int argc, char **argv, args_t *args);
int count_args(char **argv, args_t *new);
args_t *check_args(int argc, char **argv);

// network/socket_init.c
server_t *binding_and_listening(server_t *new);
server_t *init_server_addr(int port, server_t *new);
server_t *init_server(int port);
int accept_socket(server_t *serv);
int accept_client(server_t *serv);
void exit_client(server_t *serv, int fd);

client_t *is_active(server_t *serv, struct sockaddr_in addr);
client_t *get_current(client_t *clients, int current);

// utils.c
void *xmalloc(size_t size);
int is_a_sep(char c, char *sep);
int len_word(char const *str, char *sep);
int count_words(char const *str, char *sep);
void fill_word(char **word, char **str, int len);
char **str_to_word_array(char const *str, char *sep);

//functions/moving.c
int fetch_x(client_t *client, int w);
int fetch_y(client_t *client, int h);

// main.c
void display_help(void);
void update_file(tile_t *head, int w, int h, client_t *clients);
int main(int argc, char **argv);

#endif /* MY_H_ */

#ifndef GNL_H_
#define GNL_H_
#define READ_SIZE 100

// get_next_line.c
char *get_line(int *size_read, char *line);
char *get_buff_after_line(int *size_read, char *buffer);
char *my_next_strcat(char *buffer, char *line);
char *reach_end_of_line(int fd, int *size_read, char *buff, char *line);
char *get_next_line(int fd);

#endif /* GNL_H_ */