#include "ui.h"

#include <malloc.h>
#include <stdbool.h>
#include <string.h>

#include "devices.h"
#include "raygui.h"
#include "raylib.h"

#define DEVICE_RADIUS 20

static bool putDevice = false;

bool putCable = false;
bool firstCable = false;
bool secondCable = false;
static int clicks = 0;
static struct Cabo new_cable;

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

void draw_devices(struct World *world) {
	for (int i = 0; i <= world->dis_size; i++) {
		struct Dispositivo current_dis = world->all[i];

		if (current_dis.tipo == DISPOSITIVO) {
			DrawCircleV(current_dis.pos, DEVICE_RADIUS, RED);
			DrawText(current_dis.nome, current_dis.pos.x - strlen(current_dis.nome) - DEVICE_RADIUS, current_dis.pos.y, 15, WHITE);
		}
	}
}

void draw_cables(struct World *world) {
	for (int i = 0; i < world->cabos_size; i++) {
		struct Cabo current_cabo = world->cabos[i];

		DrawLineEx(current_cabo.left->pos, current_cabo.right->pos, 4, MAGENTA);
	}
}
void draw_buttons(Rectangle *items, Rectangle *console) {
	static int BUTTON_WIDTH = 75;
	static int BUTTON_HEIGHT = 40;
	Rectangle device_button;
	device_button.width = BUTTON_WIDTH;
	device_button.height = BUTTON_HEIGHT;
	device_button.x = items->x / 2;
	device_button.y = items->y + BUTTON_HEIGHT;

	Rectangle simulation_button;
	simulation_button.width = BUTTON_WIDTH;
	simulation_button.height = BUTTON_HEIGHT;
	simulation_button.x = (items->x / 2) + BUTTON_WIDTH;
	simulation_button.y = items->y + BUTTON_HEIGHT;

	if (GuiButton(device_button, "Dispositivo")) {
		putDevice = true;
	}

	if (GuiButton(simulation_button, "Cabo")) {
		putCable = true;
	}
}

EVENTS check_events(struct World *world) {

	// TODO: Não gosto de como isso está sendo feito
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && putDevice) {
		return PUT_DEVICE;
	} else if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && putCable) {
		return PUT_CABLE;
	}

	// Fazendo isso só para testes mas é muito melhor usar uma QuadTree
	for (int i = 0; i < world->dis_size; i++) {

		if (CheckCollisionPointCircle(GetMousePosition(), world->all[i].pos, DEVICE_RADIUS)) {
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

				world->all[i].pos = GetMousePosition();
			}
		}
	}

	return NONE;
}

void handle_events(EVENTS ev, struct World *world) {
	Vector2 mouse_pos = GetMousePosition();
	switch (ev) {
	case PUT_DEVICE: {
		struct Dispositivo new_device = {mouse_pos, DISPOSITIVO};
		new_device.total_cabeados = 0;
		new_device.cabeado = (struct Cabo **)malloc((new_device.total_cabeados + 1) * sizeof(struct Cabo));
		new_device.nome = "Dispositivo";
		world->all[world->dis_size++] = new_device;

		putDevice = false;
		TraceLog(LOG_INFO, "Novo Dispositivo em {x:%f, y:%f}", new_device.pos.x, new_device.pos.y);
	} break;
	case PUT_CABLE: {
		for (int i = 0; i < world->dis_size; i++) {
			if (CheckCollisionPointCircle(mouse_pos, world->all[i].pos, DEVICE_RADIUS)) {
				struct Dispositivo *current_dis = &world->all[i];
				if (!firstCable) {
					firstCable = true;
					new_cable.left = current_dis;
				} else if (!secondCable) {
					secondCable = true;
					new_cable.right = current_dis;
				}

				if (firstCable && secondCable) {
					firstCable = false;
					secondCable = false;
					putCable = false;

					current_dis->cabeado[current_dis->total_cabeados++] = &new_cable;
					struct Cabo next_cable = {.right = current_dis, .left = new_cable.right};
					new_cable.right->cabeado[new_cable.right->total_cabeados] = &next_cable;

					world->cabos[world->cabos_size] = new_cable;
					world->cabos_size++;
					TraceLog(LOG_INFO, "%f %f", new_cable.left->pos.x, new_cable.left->pos.y);
					TraceLog(LOG_INFO, "%f %f", new_cable.right->pos.x, new_cable.right->pos.y);
				}
			}
		}

	} break;
	default:
		break;
	}
}
