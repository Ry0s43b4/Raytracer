##
## EPITECH PROJECT, 2026
## raytracer
## File description:
## Makefile
##

NAME	=	raytracer

CXX	=	g++

CXXFLAGS	=	-std=c++20 -Wall -Wextra -Werror -Iinclude -lconfig++

SRC	=	src/main.cpp						\
		src/Math/Vector3D.cpp				\
		src/Math/Ray.cpp					\
		src/Scene/SceneParser.cpp			\
		src/Factory/PrimitiveFactory.cpp	\
		src/Primitive/Sphere.cpp			\
		src/Primitive/Plane.cpp

OBJ	=	$(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
