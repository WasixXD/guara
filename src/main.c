#include <malloc.h>
#include <stdbool.h>

#include "devices.h"
#include "raylib.h"
#include "ui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  InitWindow(WIDTH, HEIGHT, "Guará - Simulador de Redes");

  Rectangle items;
  Rectangle console;
  Rectangle device_button;

  World world;
  world.size = 0;

  while (!WindowShouldClose()) {
    if (IsKeyPressed(KEY_ESCAPE))
      break;
    BeginDrawing();
    ClearBackground((Color){0x18, 0x18, 0x18, 0});

    draw_tables(&items, &console);
    draw_buttons(&items, &console);
    EVENTS ev = check_events();
    handle_events(ev, &world);

    draw_devices(&world);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
