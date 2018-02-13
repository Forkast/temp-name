#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

enum ACTION {
	FORWARD,
	BACKWARD,
	LEFTWARD,
	RIGHTWARD,
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

void EV_setActionMap(EventHandler * am);
void EV_deleteActionMap(EventHandler * am);

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
