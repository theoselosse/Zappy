##
## EPITECH PROJECT, 2021
## Zappy Gui
## File description:
## Makefile
##

NAME	=	zappy_gui

CXX	=	g++
CXXFLAGS	+=	-I./include
CXXFLAGS	+=	-Wall -Wextra
CXXFLAGS	+=	-lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio

SRC	=	./src/main.cpp		\
		./src/Error.cpp		\
		./src/GraphicalModule.cpp		\
		./src/Socket.cpp		\

OBJ	=	$(SRC:.cpp=.o)

RM	=	rm -f

all:	gui

gui:	$(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: clean fclean all