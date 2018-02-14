#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

enum ACTION {
	FORWARD,
	BACK,
	LEFT,
	RIGHT,
	KEYBOARD_END,
	LOOK_Y,
	LOOK_X,
	END
};
static const int ACTION_NUMBER = END - FORWARD;

typedef struct EventHandler
{
	int * action_map;
} EventHandler;

/**
 * Konstruktor dla EventHandlera
 */
EventHandler * EV_createEventHandler();

/**
 * Destruktor dla EventHandlera
 */
void EV_destroyEventHandler(EventHandler ** am);

/**
 * Obsługuje wszystkie zdarzenia
 */
int handle_event(int * input_status, const EventHandler * EV);

/**
 * Tłumaczy keyboard input na zachowanie w grze
 */
int map_keyboard(const SDL_Event * event, int * input_status, const EventHandler * EV);

/**
 * Tłumaczy mouse input na zachowanie w grze
 */
int map_mouse(const SDL_Event * event, int * input_status, const EventHandler * EV);

#endif /* EVENT_HANDLER_H */
