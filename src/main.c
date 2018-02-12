#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int keyboard_mapper(const SDL_Event * event)
{
	if (event->key.type == SDL_KEYUP)
		printf("Release:- \n");
	else
		printf("Press:- \n");
}

int mouse_mapper(const SDL_Event * event)
{
	printf("Current mouse position is: (%d, %d)\n", event->motion.x, event->motion.y);
}

int event_scheduler()
{
	SDL_Event event;
	while (SDL_WaitEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				keyboard_mapper(&event);
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				mouse_mapper(&event);
				break;
			case SDL_QUIT:
				return 0;
		}
	}
	return 1;
}

int main(int argc, const char * argv[])
{
	SDL_Window * window = NULL;
	SDL_Surface * screenSurface = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	window = SDL_CreateWindow("temp-name", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if (window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	screenSurface = SDL_GetWindowSurface(window);
	SDL_Thread * threads[10];
	int threadCount = 0;
	threads[threadCount++] = SDL_CreateThread(&event_scheduler, "", (void *)NULL);

	for (int i = 0; i < threadCount; i++) {
		int ret;
		SDL_WaitThread(threads[i], &ret);
	}

	SDL_Quit();
	return 0;
}
