/*
** EPITECH PROJECT, 2021
** B-YEP-410-LIL-4-1-zappy-theo.selosse
** File description:
** functions
*/

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "struct.h"
#include "list.h"

typedef struct s_parameters parameters_t;
typedef struct s_team team_t;
typedef struct s_server server_t;

// functions/server_events.c
void teams(parameters_t *p);

//functions/moving.c
void move(client_t *client, int dir, parameters_t *args);
void up(client_t *client, tile_t *line);
void down(client_t *client, tile_t *line);
void left(client_t *client, tile_t *line);
void right(client_t *client, tile_t *line);

//functions/actions.c
void expulse(parameters_t *params);
void turn_l(parameters_t *params);
void turn_r(parameters_t *params);
void inventory(parameters_t *params);
void forward(parameters_t *p);

// functions/player_info.c
void drop(parameters_t *params);
void pickup(parameters_t *params);
void dead(parameters_t *params);
void position(parameters_t *params);
void level(parameters_t *params);

void tiles_content(parameters_t *p);
void new_player(parameters_t *p);
void teams(parameters_t *p);
void unknown(parameters_t *p);

//functions/look.c
void look(parameters_t *params);
tile_t *redirect_step_one(tile_t *current, int direction, int step);
tile_t *redirect_step_two(tile_t *current, int direction, int step);
tile_t *redirect_step_three(tile_t *current, int direction, int step);
char *look_cat_tiles(tile_t *current, int elevation, client_t *current_c, client_t *list);
char *alloc_tot_lgt(tile_t *current, char *message, client_t *current_c, int elevation);
char *fetch_res_tile(tile_t *current, int first, char *message, client_t *list);
int count_pl_tile(tile_t *current, int length, int first, client_t *list);
int count_res_tile(tile_t *current, int length, int first);
char *make_pl_tile(tile_t *current, char *tile_message, int first, client_t *list);
char *make_res_tile(tile_t *current, char *tile_message, int first);

//functions/elevation.c
void incantation(parameters_t *params);
void incant_lvl_two(parameters_t *params);
void incant_lvl_three(parameters_t *params);
void incant_lvl_four(parameters_t *params);
void incant_lvl_five(parameters_t *params);
void incant_lvl_six(parameters_t *params);
void incant_lvl_seven(parameters_t *params);
void incant_lvl_height(parameters_t *params);
int fetch_nbr_pl(client_t *list, tile_t *pos);

//functions/broadcast.c
void broadcast(parameters_t *params);
void deploy(parameters_t *p, char *message);
int compute_dir_one(int dir, client_t *client);
int compute_dir_two(int dir, client_t *client);
int compute_dir_three(int dir, client_t *client);
int get_dir(int x1, int y1, int x2, int y2);
int compute_dir_three(int dir, client_t *client);
void incantation_part2(parameters_t *p);

typedef struct s_parameters {
    client_t *all_clients;
    client_t *client;
    size_t map_size;
    int w;
    int h;
    tile_t *map;
    char *arg;
    team_t **teams;
    server_t *serv;
    int fd_cur;
    float freq;
} parameters_t;

typedef struct s_commands {
    char *command;
    void (*func_ptr)(parameters_t *);
    double time;
    bool valid;
} commands_t;

static const commands_t commands[] = {
    {"unknown", &unknown, 0, 0},
    {"dead", &dead, 0, 0},
    {"Set", &drop, 7000, 1},
    {"Take", &pickup, 7000, 1},
    {"Forward", &forward, 7000, 1},
    {"Left", &turn_l, 7000, 1},
    {"Right", &turn_r, 7000, 1},
    {"Eject", &expulse, 7000, 1},
    {"Inventory", &inventory, 1000, 1},
    {"Look", &look, 7000, 1},
    {"Incantation", &incantation, 300000, 1},
    //Debug
    {"level", &level, 0, 0},
    {"position", &position, 0, 0},
    {"team:", &teams, 0, 0},
    {"New_Player", &new_player, 0, 0},
    {"tiles_content", &tiles_content, 0, 0},
    //{"Size", &map_sz},
};

#endif /* !FUNCTIONS_H_ */
