#include <string>
#include <SDL.h>

#include "pacman_visualizer.h"
#include "map_container.h"


int main(int argc, char *args[]) {

	MapContainer mapContainer("stdin.txt");

	PacmanVisualizer pVis(mapContainer.getWidth(), mapContainer.getHeight());

	bool running = true;
	SDL_Event e;
	while ((SDL_WaitEvent(&e) != 0) && running) {
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
			}
		}
	}

	return 0;
}
