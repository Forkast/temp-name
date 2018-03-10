#include "screen_renderer.h"

ScreenRenderer * SR_createScreenRenderer(MapHolder * MH)
{
	ScreenRenderer * SR = malloc(sizeof *SR);
	SR->map_holder = MH;
	SR->window = SDL_CreateWindow("temp-name",
							  SDL_WINDOWPOS_UNDEFINED,
							  SDL_WINDOWPOS_UNDEFINED,
							  MH_getWidth(MH),
							  MH_getHeight(MH),
							  SDL_WINDOW_SHOWN);
	if (SR->window == NULL) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(1); //NOTE: funkcja która kończy program?
	}
	SR->surface = SDL_GetWindowSurface(SR->window);

}

void SR_destroyScreenRenderer(ScreenRenderer ** SR)
{
	SDL_DestroyWindow((*SR)->window);
	(*SR)->window = NULL;
	(*SR)->surface = NULL;
	(*SR)->map_holder = NULL;
	free(*SR);
	(*SR) = NULL;
}

void SR_render(ScreenRenderer * SR)
{
	SDL_LockSurface(SR->surface);
	for (int x = 0; x < MH_getWidth(SR->map_holder); x++) {
		for (int y = 0; y < MH_getHeight(SR->map_holder); y++) {
			Uint32 *target_pixel = (Uint8 *) SR->surface->pixels
									+ y * SR->surface->pitch
									+ x * sizeof *target_pixel;
			*target_pixel = MH_getPixel(SR->map_holder, x, y);
		}
	}
	SDL_UnlockSurface(SR->surface);
	SDL_UpdateWindowSurface(SR->window);
}
