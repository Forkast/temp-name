#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "event_handler.h"
#include "map_holder.h"

/**
 * Główna pętla programu
 */
int main_loop()
{
	/* NOTE: ten fragment wyląduje w jakimś rendererze */
	MapHolder * MH = MH_createMapHolder();
	SDL_Window * window = NULL;
	SDL_Surface * surface = NULL;
	window = SDL_CreateWindow("temp-name",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  MH_getWidth(MH),
							  MH_getHeight(MH),
							  SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	surface = SDL_GetWindowSurface(window);
	SDL_LockSurface(surface);
	for (int x = 0; x < MH_getWidth(MH); x++) {
		for (int y = 0; y < MH_getHeight(MH); y++) {
			Uint32 *target_pixel = (Uint8 *) surface->pixels
									+ y * surface->pitch
									+ x * sizeof *target_pixel;
			*target_pixel = MH_getPixel(MH, x, y);
			printf("Ustawiono pixel(%d, %d) na wartosc %d.\n", x, y, *target_pixel);
		}
	}
	SDL_UnlockSurface(surface);
	/* end of ten fragment */


	int quit = 0;
	int input_status[ACTION_NUMBER];

	for (int i = 0; i < ACTION_NUMBER; i++) {
		input_status[i] = 0;
	}

	EventHandler EV;
	EV_setActionMap(&EV);

	while (!quit) {
		//event
		quit = handle_event(input_status, &EV);
		//logic
		//render
	}

	EV_deleteActionMap(&EV);
	MH_deleteMapHolder(&MH);
	SDL_DestroyWindow(window);
	return 0;
}

int main(int argc, const char * argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	// pozwala używać informacji o zmianie myszy od ostatniego położenia
	if (SDL_SetRelativeMouseMode(1) < 0) {
		printf("SDL could not set relative mouse mode! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	int res = main_loop();

	SDL_Quit();
	return res;
}
