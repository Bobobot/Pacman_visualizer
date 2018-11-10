#include "pacman_visualizer.h"

PacmanVisualizer::PacmanVisualizer(int mapWidth, int mapHeight) {
	tileSize = 30;
	width = mapWidth * tileSize;
	height = mapHeight * tileSize;

	if (!initSDL()) 
		throw "SDL initialization error!";
	initTimer();
}

void PacmanVisualizer::resize(int width, int height) {
	this->width = width;
	this->height = height;
	SDL_SetWindowSize(window, width, height);
}

int PacmanVisualizer::getTileSize() {
	return tileSize;
}

void PacmanVisualizer::drawMap(Map map) {
	std::stringstream windowTitle;
	windowTitle << "Tick: " << map.currentTick << " | Depth: " << map.currentDepth;
	SDL_SetWindowTitle(window, windowTitle.str().c_str());
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int pointRadius = tileSize / 8;
	int boosterRadius = tileSize / 4;
	int ghostRadius = tileSize / 3;

	for (unsigned int y = 0; y < map.getWidth(); y++) {
		auto row = map[y];
		for (unsigned int x = 0; x < row.size(); x++) {
			char c = row[x];

			int tileX1 = x * tileSize;
			int tileY1 = y * tileSize;
			int tileX2 = tileX1 + tileSize;
			int tileY2 = tileY1 + tileSize;

			int circleMidX = (x * tileSize) + tileSize / 2;
			int circleMidY = (y * tileSize) + tileSize / 2;

			switch (c) {
			case 'F':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x66, 0xFF, 0xFF);
				break;
			case '_':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				break;
			case '1':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				filledCircleRGBA(renderer, circleMidX, circleMidY, pointRadius, 0xCC, 0xCC, 0xCC, 0xFF);
				break;
			case '+':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				filledCircleRGBA(renderer, circleMidX, circleMidY, boosterRadius, 0xDD, 0x00, 0x00, 0xFF);
				break;
			case 'G':
				boxRGBA(renderer, tileX1 + tileSize / 4, tileY1, tileX2 - tileSize / 4, tileY2, 0x00, 0x66, 0xFF, 0xFF);
				break;
			case 'S':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				filledCircleRGBA(renderer, circleMidX, circleMidY, ghostRadius, 0xFF, 0x80, 0x00, 0xFF);
				break;
			case 'K':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				filledCircleRGBA(renderer, circleMidX, circleMidY, ghostRadius, 0x00, 0x00, 0xCC, 0xFF);
				break;
			case 'P':
				boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0x00, 0x00, 0x00, 0xFF);
				filledCircleRGBA(renderer, circleMidX, circleMidY, ghostRadius, 0xFF, 0xFF, 0x00, 0xFF);
				break;
			}
		}
	}

	for (Point p : map.pacmanTiles) {
		int tileX1 = p.x * tileSize;
		int tileY1 = p.y * tileSize;
		int tileX2 = tileX1 + tileSize;
		int tileY2 = tileY1 + tileSize;
		boxRGBA(renderer, tileX1, tileY1, tileX2, tileY2, 0xFF, 0xFF, 0x00, 0x80);
	}

	SDL_RenderPresent(renderer);
}

PacmanVisualizer::~PacmanVisualizer() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool PacmanVisualizer::initSDL() {
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		logErrorSDL("Unable to initialize SDL: %s");
		success = false;
	} else {
		window = SDL_CreateWindow(windowTitle.c_str(),
								  SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED,
								  width,
								  height,
								  0);
		if (window == nullptr) {
			logErrorSDL("Error while creating the window: %s");
			success = false;
		} else {
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == nullptr) {
				logErrorSDL("Failed to create the global renderer: %s");
				success = false;
			}
		}
	}

	return success;
}

void PacmanVisualizer::logErrorSDL(const char* errorMessage) {
	printf("%s\n%s", errorMessage, SDL_GetError());
}

void PacmanVisualizer::initTimer() {
	int delay = 1000 / 60;
	SDL_TimerID fpsTimer = SDL_AddTimer(delay, this->fpsTimerCallback, 0);
}

Uint32 PacmanVisualizer::fpsTimerCallback(Uint32 delay, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = FPSTIMER;
	SDL_PushEvent(&event);

	return delay;
}
