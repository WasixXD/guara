#include "raylib.h"
#include "ui.h"
#include "raygui.h"

void draw_tables(Rectangle *items, Rectangle *console) {
  items->height  = (int)GetScreenHeight() / 6;
  console->width = (int)GetScreenWidth() / 4;
  items->width   = GetScreenWidth() - console->width; 
  console->height= GetScreenHeight();

    
  items->y = GetScreenHeight() - items->height; 
  console->x = GetScreenWidth() - console->width;
  
  GuiPanel(*items, "#190#Opções");
  GuiPanel(*console, "#190#Console");


}

