#ifndef UI_H
#define UI_H

#include "devices.h"
#include <raylib.h>
#define WIDTH 1080
#define HEIGHT 740

typedef enum {
  PUT_DEVICE = 1,
  PUT_SWITCH,
  PUT_ROUTER,
  PUT_CABLE,
  NONE,
} EVENTS;

void draw_tables(Rectangle *items, Rectangle *console);
void draw_buttons(Rectangle *items, Rectangle *console);
void draw_devices(World *world);
void handle_events(EVENTS ev, World *world);
EVENTS check_events();

#endif
