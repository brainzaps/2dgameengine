INCLUDE_PATHS = -I/opt/homebrew/include -L/opt/homebrew/lib -I"./libs/"
SRC_FILES = ./src/*.cpp ./src/Game/*.cpp ./src/Logger/*.cpp ./src/ECS/*.cpp ./src/AssetStore/*.cpp
LINGER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -l lua5.4
OBJ_NAME = gameengine

build:
	g++ -Wall -std=c++17 $(SRC_FILES) -o $(OBJ_NAME) $(INCLUDE_PATHS)  $(LINGER_FLAGS)

run:
	./$(OBJ_NAME)

clean:
	rm $(OBJ_NAME)