
CC = g++

LFLAGS = -lGL -lglfw
SOURCE_FILES = src/main.cpp src/game.cpp src/render.cpp src/controls.cpp
OBJECT_FILES =
CFLAGS = $(shell pkg-config --cflags gl glfw3)

all:.DotGame.out


.DotGame.out: $(SOURCE_FILES)
	$(CC) $(SOURCE_FILES) $(LFLAGS) $(CFLAGS) -o dotGame.out 
