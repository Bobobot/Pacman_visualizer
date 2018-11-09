#include <string>
#include <SDL.h>

#include "pacman_visualizer.h"
#include "map_container.h"


int main(int argc, char *args[]) {
	PacmanVisualizer pVis(800, 600);

	MapContainer mapContainer("stdin.txt");


	bool running = true;
	SDL_Event e;
	while (running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
			} else if (e.type == SDL_USEREVENT) {
				if (e.user.code == FPSTIMER) {
					pVis.drawMap(mapContainer.currentMap());
				}
			} else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					mapContainer.nextMap();
					break;
				case SDLK_LEFT:
					mapContainer.previousMap();
					break;
				case SDLK_UP:
					break;
				case SDLK_DOWN:
					break;
				}
			}
		}
	}

	return 0;
}