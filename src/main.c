#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "event_handler.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

/**
 * Główna pętla programu
 */
int main_loop()
{
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
	return 0;
}

int main(int argc, const char * argv[])
{
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	// pozwala używać informacji o zmianie myszy od ostatniego położenia
	if (SDL_SetRelativeMouseMode(1) < 0) {
		printf("SDL could not set relative mouse mode! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	window = SDL_CreateWindow("temp-name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	screenSurface = SDL_GetWindowSurface(window);
	int res = main_loop();

	SDL_Quit();
	return res;
}
