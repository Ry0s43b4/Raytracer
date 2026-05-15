##
## EPITECH PROJECT, 2026
## raytracer
## File description:
## Makefile
##

NAME	=	raytracer
TEST_NAME =	unit_tests

CXX	=	g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinclude -I/opt/homebrew/opt/libconfig/include
LDFLAGS  = -L/opt/homebrew/opt/libconfig/lib -lconfig++
CRITERION_CFLAGS = $(shell pkg-config --cflags criterion)
CRITERION_LIBS = $(shell pkg-config --libs criterion)

SRC_DIR	=	src

SRC	=	$(shell find $(SRC_DIR) -type f -name "*.cpp")
TEST_FILES = tests/scene_parser_test.cpp \
	   tests/scene_test.cpp \
	   tests/camera_test.cpp
TEST_SRC = $(TEST_FILES) \
	   src/Scene/Scene.cpp \
	   src/Scene/Camera.cpp \
	   src/Transformation/Rotation.cpp \
	   src/Math/Ray.cpp \
	   src/Math/Vector3D.cpp \
	   src/Scene/SceneParser.cpp \
	   src/Core/RaytracerError.cpp \
	   src/Core/Intersection.cpp \
	   src/Materials/Metal.cpp \
	   src/Materials/ReflectionMaterial.cpp

OBJ	=	$(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

$(TEST_NAME): CXXFLAGS += $(CRITERION_CFLAGS) \
	-Wno-error=deprecated-declarations \
	-Wno-error=unused-parameter
$(TEST_NAME): $(TEST_OBJ)
	$(CXX) -o $(TEST_NAME) $(TEST_OBJ) $(LDFLAGS) $(CRITERION_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests_run: $(TEST_NAME)
	./$(TEST_NAME)

clean:
	rm -f $(OBJ) $(TEST_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re tests_run
