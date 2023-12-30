all:
	g++ -Iinclude/header/Screens -Iinclude/header -Iinclude/raylib -o main src/*.cpp src/Screens/*.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall