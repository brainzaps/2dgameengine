build:
	g++ -Wall -std=c++17 src/*.cpp -o gameengine -I/opt/homebrew/include -L/opt/homebrew/lib -I"./libs/" -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -l lua5.4

run:
	./gameengine

clean:
	rm gameengine