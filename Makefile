##
## EPITECH PROJECT, 2026
## raytracer
## File description:
## Makefile
##

NAME	=	raytracer

CXX	=	g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinclude -I/opt/homebrew/opt/libconfig/include
LDFLAGS  = -L/opt/homebrew/opt/libconfig/lib -lconfig++

SRC_DIR	=	src

SRC	=	$(shell find $(SRC_DIR) -type f -name "*.cpp")

OBJ	=	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
