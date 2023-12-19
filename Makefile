all:
	g++ -Iinclude -Iinclude/header -Iinclude/raylib -Llib -o main src/*.cpp -lraylib -lopengl32 -lgdi32 -lwinmm -Wall