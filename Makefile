##
## EPITECH PROJECT, 2026
## raytracer
## File description:
## Makefile
##

NAME	=	raytracer

CXX	=	g++
CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -Iinclude

SRC	=	src/main.cpp				\
		src/math/Vector3D.cpp		\
		src/math/Ray.cpp

OBJ	=	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
