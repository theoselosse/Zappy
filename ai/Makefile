##
## EPITECH PROJECT, 2021
## Zappy AI
## File description:
## Makefile
##

NAME	=	zappy_ai

CXX	=	g++
CXXFLAGS	+=	-I./include
CXXFLAGS	+=	-Wall -Wextra

SRC	=	./src/main.cpp		\
		./src/Error.cpp		\
		./src/Client.cpp	\

OBJ	=	$(SRC:.cpp=.o)

RM	=	rm -f

all:	ai

ai:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all