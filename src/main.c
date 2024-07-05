#include "raylib.h"
#include "ui.h"
#include "devices.h"
#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"


int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE); 
  /*SetConfigFlags(FLAG_FULLSCREEN_MODE); */
  InitWindow(WIDTH, HEIGHT, "Guará - Simulador de Redes");
  Rectangle items;
  Rectangle console;
  Rectangle device_button;

  bool putDevice = false;
  Dispositivo *all[3]; 
  // TODO: Implementar uma maneira melhor de desenhar os dispositivos
  int debug = 0;
  while(!WindowShouldClose()) {
    if(IsKeyPressed(KEY_ESCAPE)) break;
    BeginDrawing();
    ClearBackground((Color){0x18, 0x18, 0x18, 0});

    draw_tables(&items, &console);

    device_button.width = 75;
    device_button.height = 40;
    device_button.x = items.x / 2;
    device_button.y = items.y + device_button.height;
    if(GuiButton(device_button, "Dispositivo")) {
      putDevice = true;         
    }


    if(putDevice) {
      Vector2 mousePos = GetMousePosition();
      if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        putDevice = false;
        Dispositivo new_device = {mousePos, DISPOSITIVO, "Dispositivo1"};
        all[0] = &new_device;
        debug++;
      }
    }
    if(debug != 0) {

      draw_device(all[0]);
    }
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
