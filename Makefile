NAME	=	MagicCubeSolver

SRC	=	main.cpp				\
		MagicCubeDisplay.cpp			\
		MagicCubeSolver.cpp			\
		MagicCubeState.cpp

OBJ	=	$(SRC:.cpp=.o)

INCLUDE	=

LIB	=	-lboost_program_options -lSDL -lGL -lGLU

CC	=	g++

CXXFLAGS +=	-Wall -Wextra -Werror --std=c++11 -O3
CXXFLAGS +=	-g $(INCLUDE)

LFLAG	+=	$(INCLUDE) $(LIB)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) $(LFLAG) $(INCLUDE)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all

.PHONY:		re clean fclean all
