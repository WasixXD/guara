
#include "devices.h"

#include "raylib.h"



void draw_device(Dispositivo *d) {
  int radius = 30;
  int font_size = 15;
  DrawCircleV(d->pos, radius, RED);
  DrawText(d->nome, d->pos.x, d->pos.y, font_size, WHITE);

  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    bool tmp = CheckCollisionPointCircle(GetMousePosition(), d->pos, radius);
    TraceLog(LOG_INFO, "%b", tmp);
  }

}
