/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** list.h
*/

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef struct s_parameters parameters_t;
typedef struct s_commands commands_t;

typedef struct resource_s {
    char *name;
    int nb;
} resource_t;

typedef struct tile_s {
    int x, y;
    int nb_p;
    struct tile_s *up;
    struct tile_s *down;
    struct tile_s *right;
    struct tile_s *left;
    resource_t **r;
} tile_t;

typedef struct action_s {
    int position;
    int size;
    char *name;
    double time;
    char *a;
    bool valid;
    int fd;
    void (*func_ptr)(parameters_t *);
    struct action_s *next;

} action_t;

typedef struct client_s {
    int id;
    int fd;
    int x;
    int y;
    int dir;
    //double life;
    int elevation;
    char *t_name;
    bool quitting;
    tile_t *pos;
    resource_t **inventory;
    action_t *actions;
    struct client_s *next;
} client_t;

// map/utils.c
void dump_circular(tile_t *list, int size);
void dump_reverse(tile_t *list);
void dump(tile_t *list);
void dump_ressources(tile_t *list, int size);
void dump_map(tile_t *head, int height, int width);

// map/generator.c
void add_back(tile_t *list);
tile_t *create_list(int size, int y);
void circular(tile_t *head);
void linking(tile_t *fi, tile_t *se, int size);
tile_t *create_map(int av1, int av2);

// free_map_list.c
void free_circular(tile_t *list, int size);
void free_map(tile_t *head, int height, int width);

// map/resources/setup_tile_resources.c
tile_t *setup_tile_res(tile_t *current);
client_t *setup_tile_res_cl(client_t *current);

// clients/clients_list.c
client_t *create_node(int, float, tile_t *);
client_t *push_back(client_t *, int, tile_t *, float freq);
tile_t *get_cur_node(tile_t *map, int x, int y, int w, int h);
void dump_list(client_t *);

// clients_list_free.c
void free_clients(client_t *);
void free_one_client(client_t *tmp);
client_t *remove_first(client_t *, int);
client_t *remove_at(client_t *, int);

// action/action_list.c
action_t *create_action(double time, char *f_name, bool valid,
void (*f)(parameters_t *));
action_t *push_action_back(action_t *, commands_t, int, char *);

// action_list_free.c
void free_actions(action_t *);
void free_one_action(action_t *tmp);
action_t *remove_first_a(action_t *);
action_t *remove_at_a(action_t *, int);

void dump_actions(action_t *head);

#endif /* LIST_H_ */