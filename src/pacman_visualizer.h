#pragma once

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <string>
#include <vector>
#include <sstream>

#include "map.h"
#include "point.h"

static int const FPSTIMER = 0;

//using Maze = std::vector<std::vector<char>>;

class PacmanVisualizer {
	int width, height;
	SDL_Renderer* renderer;
	SDL_Window* window;
	std::string windowTitle = "Pacman";
	int tileSize;
	bool initSDL();
	void logErrorSDL(const char* errorMessage);
	void initTimer();
	static Uint32 fpsTimerCallback(Uint32 delay, void * param);
public:
	PacmanVisualizer(int width, int height);

	void resize(int width, int height);
	int getTileSize();
	void drawMap(Map m);

	~PacmanVisualizer();
};
