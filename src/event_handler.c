#include "event_handler.h"

void EV_setActionMap(EventHandler * EV)
{
	EV->action_map = malloc(ACTION_NUMBER * sizeof *(EV->action_map));
	EV->action_map[FORWARD] = SDL_SCANCODE_W;
	EV->action_map[BACK] = SDL_SCANCODE_S;
	EV->action_map[LEFT] = SDL_SCANCODE_A;
	EV->action_map[RIGHT] = SDL_SCANCODE_D;
	EV->action_map[LOOK_Y] = -1;
	EV->action_map[LOOK_X] = 1;
}

void EV_deleteActionMap(EventHandler * EV)
{
	free(EV->action_map);
	EV->action_map = NULL;
}

/**
 * NOTE: przy większej liczbie można zrobić binarnie
 */
int EV_getKeyboardAction(int key, const EventHandler * EV)
{
	for (int i = 0; i < KEYBOARD_END; i++) {
		if (key == EV->action_map[i]) {
			return i;
		}
	}
	return -1;
}

int EV_getMouseAction(int axis, int value, const EventHandler * EV)
{
	return value * EV->action_map[axis];
}

/**
 * Obsługuje wszystkie zdarzenia.
 * NOTE: Czy ma pobierać zdarzenia aż się nie skończą?
 * NOTE: Czy może tylko określoną liczbę?
 */
int handle_event(int * input_status, const EventHandler * EV)
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				map_keyboard(&event, input_status, EV);
				break;
			case SDL_MOUSEMOTION:
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEWHEEL:
				map_mouse(&event, input_status, EV);
				break;
			case SDL_QUIT:
				return 1;
		}
	}
	return 0;
}

int map_keyboard(const SDL_Event * event, int * input_status, const EventHandler * EV)
{
	int action = EV_getKeyboardAction(event->key.keysym.scancode, EV);
	if (action == -1)
		return 0;
	if (event->key.type == SDL_KEYUP) {
		printf("Release:- ");
		input_status[action] = 0;
	} else if (event->key.type == SDL_KEYDOWN && input_status[action] != 1) {
		printf("Press:- ");
		input_status[action] = 1;
	}
	switch(action) {
		case FORWARD:
			printf("forward\n");
			break;
		case BACK:
			printf("backward\n");
			break;
		case LEFT:
			printf("to the left\n");
			break;
		case RIGHT:
			printf("to the right\n");
			break;
	}
	return 0;
}

int map_mouse(const SDL_Event * event, int * input_status, const EventHandler * EV)
{
	input_status[LOOK_X] = EV_getMouseAction(LOOK_X, event->motion.xrel, EV);
	input_status[LOOK_Y] = EV_getMouseAction(LOOK_Y, event->motion.yrel, EV);
	if (input_status[LOOK_Y] > 0) {
		printf("Looking UP!\n");
	} else if (input_status[LOOK_Y] < 0) {
		printf("Looking down!\n");
	}
	if (input_status[LOOK_X] > 0) {
		printf("Looking right!\n");
	} else if (input_status[LOOK_X] < 0) {
		printf("Looking left!\n");
	}
}
