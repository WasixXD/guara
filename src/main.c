#include <malloc.h>
#include <stdbool.h>
#include <stdint.h>

#include "devices.h"
#include "raylib.h"
#include "simulation.h"
#include "ui.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

int main(void) {
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(WIDTH, HEIGHT, "Guará - Simulador de Redes");
	Rectangle items;
	Rectangle console;
	Rectangle device_button;

	struct World world;
	world.dis_size = 0;
	world.cabos_size = 0;

	bool simular = false;

	while (!WindowShouldClose()) {
		if (IsKeyPressed(KEY_ESCAPE))
			break;
		BeginDrawing();
		ClearBackground((Color){0x18, 0x18, 0x18, 0});

		// UI
		draw_tables(&items, &console);
		draw_buttons(&items, &console);
		EVENTS ev = check_events(&world);
		handle_events(ev, &world);

		draw_cables(&world);
		draw_devices(&world);

		if (world.cabos_size > 0) {

			world.all[0].end.ip[0] = 192;
			world.all[0].end.ip[1] = 168;
			world.all[0].end.ip[2] = 10;
			world.all[0].end.ip[3] = 2;
			prepare_arp_packet(&world.cabos[0], ARP_REQ);
		}
		EndDrawing();
	}

	CloseWindow();
	return 0;
}
