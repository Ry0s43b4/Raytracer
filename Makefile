##
## EPITECH PROJECT, 2026
## raytracer
## File description:
## Makefile
##

NAME		=	raytracer
TEST_NAME	=	unit_tests
PLUGIN_DIR	=	plugin

UNAME_S		:=	$(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	PLUGIN_EXT		=	dylib
	SHARED_FLAGS		=	-dynamiclib -fPIC
	BREW_PREFIX		=	/opt/homebrew
	SFML_INCLUDE		=	-I$(BREW_PREFIX)/opt/sfml/include
	SFML_LDFLAGS		=	-L$(BREW_PREFIX)/opt/sfml/lib \
					-lsfml-graphics -lsfml-window -lsfml-system
	DL_LDFLAGS		=
	LIBCONFIG_INCLUDE	=	-I$(BREW_PREFIX)/opt/libconfig/include
	LIBCONFIG_LDFLAGS	=	-L$(BREW_PREFIX)/opt/libconfig/lib -lconfig++
else
	PLUGIN_EXT		=	so
	SHARED_FLAGS		=	-shared -fPIC
	SFML_INCLUDE		=
	SFML_LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system
	DL_LDFLAGS		=	-ldl
	LIBCONFIG_INCLUDE	=
	LIBCONFIG_LDFLAGS	=	-lconfig++
endif


CXX		=	g++

CXXFLAGS	=	-std=c++17 -Wall -Wextra -Werror -Iinclude \
			$(LIBCONFIG_INCLUDE) $(SFML_INCLUDE)

LDFLAGS		=	$(LIBCONFIG_LDFLAGS) $(SFML_LDFLAGS) $(DL_LDFLAGS)

CRITERION_CFLAGS = $(shell pkg-config --cflags criterion)
CRITERION_LIBS   = $(shell pkg-config --libs criterion)


SRC_DIR		=	src
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
	   src/Core/Intersection.cpp

SRC		=	$(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJ		=	$(SRC:.cpp=.o)


SFML_PLUGIN_SRC		=	plugins/sfml/SFMLDisplay.cpp
SFML_PLUGIN_OBJ		=	plugins/sfml/SFMLDisplay.o
SFML_PLUGIN_NAME	=	$(PLUGIN_DIR)/libsfml_display.$(PLUGIN_EXT)

PLUGINS		=	$(SFML_PLUGIN_NAME)

TEST_FILES	=	tests/scene_parser_test.cpp \
			tests/scene_test.cpp \
			tests/camera_test.cpp
TEST_SRC	=	$(TEST_FILES) \
			src/Scene/Scene.cpp \
			src/Scene/Camera.cpp \
			src/Math/Ray.cpp \
			src/Math/Vector3D.cpp \
			src/Scene/SceneParser.cpp \
			src/Core/RaytracerError.cpp
TEST_OBJ	=	$(TEST_SRC:.cpp=.o)


all: $(NAME) $(PLUGINS)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(LDFLAGS)

$(SFML_PLUGIN_NAME): plugins/sfml/SFMLDisplay.cpp src/Core/Image.cpp src/Core/RaytracerError.cpp
	@mkdir -p $(PLUGIN_DIR)
	$(CXX) $(CXXFLAGS) -fPIC $(SHARED_FLAGS) \
		-Iinclude \
		-o $@ plugins/sfml/SFMLDisplay.cpp src/Core/Image.cpp src/Core/RaytracerError.cpp \
		$(SFML_LDFLAGS)


$(TEST_NAME): CXXFLAGS += $(CRITERION_CFLAGS) \
	-Wno-error=deprecated-declarations \
	-Wno-error=unused-parameter
$(TEST_NAME): $(TEST_OBJ)
	$(CXX) -o $(TEST_NAME) $(TEST_OBJ) $(LIBCONFIG_LDFLAGS) $(CRITERION_LIBS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests_run: $(TEST_NAME)
	./$(TEST_NAME)

clean:
	rm -f $(OBJ) $(TEST_OBJ) $(SFML_PLUGIN_OBJ)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)
	rm -f $(PLUGINS)

re: fclean all

.PHONY: all clean fclean re tests_run
