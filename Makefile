all:
	g++ src/main.cpp src/map_container.cpp src/pacman_visualizer.cpp -std=c++11 `sdl2-config --cflags` -o Pacman_visualizer -lSDL2 -lSDL2_gfx
