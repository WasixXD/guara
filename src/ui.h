#ifndef UI_H
#define UI_H

#include <raylib.h>

#include "devices.h"
#define WIDTH 1080
#define HEIGHT 740

typedef enum {
	PUT_DEVICE = 1,
	PUT_SWITCH,
	PUT_ROUTER,
	PUT_CABLE,
	MOVE_DEVICE,
	NONE,
} EVENTS;

void draw_tables(Rectangle *items, Rectangle *console);

void draw_buttons(Rectangle *items, Rectangle *console);

void draw_devices(struct World *world);

void handle_events(EVENTS ev, struct World *world);

EVENTS check_events(struct World *world);

void draw_cables(struct World *world);

#endif
