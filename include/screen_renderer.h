#ifndef SCREEN_RENDERER_H
#define SCREEN_RENDERER_H
#include <SDL2/SDL.h>
#include <stdlib.h>

#include "map_holder.h"

typedef struct ScreenRenderer
{
	MapHolder * map_holder;
	SDL_Window * window;
	SDL_Surface * surface;
} ScreenRenderer;

/**
 * Konstruktor dla ScreenRenderer
 */
ScreenRenderer * SR_createScreenRenderer(MapHolder * MH);

/**
 * Destruktor
 * NOTE: Nie niszczy MapHoldera
 */
void SR_destroyScreenRenderer(ScreenRenderer ** SR);

/**
 * Renderuje
 */
void SR_render(ScreenRenderer * SR);

#endif /* SCREEN_RENDERER_H */
