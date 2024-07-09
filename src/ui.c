#include "ui.h"
#include "devices.h"
#include "raygui.h"
#include "raylib.h"

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

bool putDevice = false;

void draw_tables(Rectangle *items, Rectangle *console) {
  items->height = (int)(GetScreenHeight() / 6);
  console->width = (int)(GetScreenWidth() / 4);
  items->width = GetScreenWidth() - console->width;
  console->height = GetScreenHeight();

  items->y = GetScreenHeight() - items->height;
  console->x = GetScreenWidth() - console->width;

  GuiPanel(*items, "#190#Opções");
  GuiPanel(*console, "#190#Console");
}

void draw_devices(World *world) {
  for (int i = 0; i <= world->size; i++) {
    Dispositivo current_dis = world->all[i];
    if (current_dis.tipo == DISPOSITIVO) {
      int radius = 20;
      DrawCircleV(current_dis.pos, radius, RED);
      DrawText(current_dis.nome,
               current_dis.pos.x - strlen(current_dis.nome) - radius,
               current_dis.pos.y, 15, WHITE);
    }
  }
}

void draw_buttons(Rectangle *items, Rectangle *console) {
  Rectangle device_button;
  device_button.width = 75;
  device_button.height = 40;
  device_button.x = items->x / 2;
  device_button.y = items->y + device_button.height;

  if (GuiButton(device_button, "Dispositivo")) {
    putDevice = true;
  }
}

EVENTS check_events() {
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && putDevice) {
    return PUT_DEVICE;
  }

  return NONE;
}

void handle_events(EVENTS ev, World *world) {
  switch (ev) {
  case PUT_DEVICE: {
    TraceLog(LOG_INFO, "asdf");
    Vector2 mouse_pos = GetMousePosition();
    Dispositivo new_device = {mouse_pos, DISPOSITIVO};
    new_device.nome = "Dispositivo";
    world->all[world->size] = new_device;

    world->size++;
    putDevice = false;
  } break;

  default:
    break;
  }
}
