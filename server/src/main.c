/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** main.c
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include "../include/struct.h"
#include "../include/my.h"

void display_help(void)
{
    write(1, "USAGE: \
./zappy_server -p port -x width -y height -n name1 name2 ... \
-c clientNb -f freq\n\
\tport\tis the port number\n\
\twidth\tis the width of the world\n\
\theight\tis the height of the world\n\
\tnameX\tis the name of the team X\n\
\tclientNb\tis the number of authorized clients per team\n\
\tfreq\tis the reciprocal of time unit for execution of actions\n", 332);
}

tile_t *generate_res(tile_t *map, args_t *args, const float freq[7])
{
    int v;
    int l = 0;

    tile_t *cur = map;
    tile_t *cur2 = map;
    tile_t *line = cur;
    tile_t *line2 = cur2->left->up;

    for (int k = 0; k < 7; k++) {
        l = args->width * args->height * freq[k];
        for (int i = 0; i < args->height; i++) {
            for (int j = 0; j < args->width; j++) {
                if (l > 0) {
                    v = rand();
                    if (v % 100 < freq[k] * 100) {
                        l--;
                        line->r[k]->nb += 1;
                        if (l > 0) {
                            l--;
                            line2->r[k]->nb += 1;
                        }
                    }
                }
                line = line->right;
                line2 = line2->left;
            }
            cur = cur->down;
            cur2 = cur2->up;
            line = cur;
            line2 = cur2;
            if (l != 0 && i == args->height - 1) {
                line->up->left->r[k]->nb += l;
                l = 0;
            }
        }
    }
    return map;
}

server_t *init_extra(server_t *server, args_t *args)
{
    server->args = args;
    server->all_clients = NULL;
    server->m_sock = server->fd;
    server->freq = freq;
    if (server->args->width * server->args->height > 100000 || server->args->height != server->args->width) {
        free(server);
        printf("Too big map\n");
        exit(84);
    }
    server->map = create_map(args->width, args->height);
    server->map = generate_res(server->map, server->args, freq);
    update_file(server->map, server->args->width, server->args->height,
    server->all_clients);
    return server;
}

int main(int argc, char **argv)
{
    args_t *args = NULL;
    server_t *server = NULL;

    srand(time(NULL));
    signal(SIGPIPE, SIG_IGN);
    if (argc == 2 && strncmp(argv[1], "-help", strlen(argv[1])) == 0) {
        return (display_help(), 0);
    } else if (argc >= 14) {
        args = check_args(argc, argv);
        server = init_server(args->port);
        if (server == NULL)
            return (84);
        server->teams = init_teams(argc, argv, args);
        if (args == NULL || server == NULL || server->teams == NULL)
            return (84);
        server = init_extra(server, args);
        accept_client(server);
    } else {
        return (write(2, "Bad args, retry with -h\n", 25), 84);
    }
    free(server);
    return (0);
}