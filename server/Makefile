##
## EPITECH PROJECT, 2021
## Zappy Server
## File description:
## Makefile
##

NAME	=	zappy_server

CXX	=	gcc
CXXFLAGS	+=	-I./include
CXXFLAGS	+=	-Wall -Wextra -g

SRC	=	./src/main.c		\
		./src/arguments/arguments_parser.c		\
		./src/arguments/arguments_checker.c		\
		./src/network/socket_init.c		\
		./src/network/command_handling.c		\
		./src/network/select.c		\
		./src/utils/str_to_word_array.c		\
		./src/utils/get_next_line.c		\
		./src/utils/xmalloc.c		\
		./src/clients/clients_list.c		\
		./src/clients/clients_list_free.c		\
		./src/action_list/action_list.c		\
		./src/action_list/action_list_free.c		\
		./src/map/resources/setup_tile_resources.c		\
		./src/map/free_map_list.c		\
		./src/map/map_utils.c		\
		./src/map/tiles_generator.c		\
		./src/map/test_main.c		\
		./src/functions/actions.c		\
		./src/functions/moving.c		\
		./src/functions/server_events.c		\
		./src/functions/player_info.c		\
		./src/functions/look.c		\
		./src/functions/fetch_tile.c		\
		./src/functions/redirect_tile.c		\
		./src/functions/elevation.c		\
		./src/functions/incantation.c		\
		./src/functions/broadcast.c		\

OBJ	=	$(SRC:.c=.o)

RM	=	rm -f

all:	server

server:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all