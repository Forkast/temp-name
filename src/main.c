#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "event_handler.h"
#include "map_holder.h"
#include "screen_renderer.h"

/**
 * Główna pętla programu
 */
int main_loop()
{
	MapHolder * MH = MH_createMapHolder();
	ScreenRenderer * SR = SR_createScreenRenderer(MH);
	int quit = 0;
	int input_status[ACTION_NUMBER];

	for (int i = 0; i < ACTION_NUMBER; i++) {
		input_status[i] = 0;
	}

	EventHandler * EV = EV_createEventHandler();

	while (!quit) {
		//event
		quit = handle_event(input_status, EV);
		//logic
		//render
		SR_render(SR);
	}

	SR_destroyScreenRenderer(&SR);
	EV_destroyEventHandler(&EV);
	MH_destroyMapHolder(&MH);
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
