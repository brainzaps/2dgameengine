build:
	g++ -Wall -std=c++17 src/*.cpp -o gameengine -I/opt/homebrew/include -L/opt/homebrew/lib -I"./libs/" -lSDL2

run:
	./gameengine

clean:
	rm gameengine