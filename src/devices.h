#ifndef DEVICES_H
#define DEVICES_H

#include <raylib.h>
#include <stdint.h>

typedef enum { DISPOSITIVO = 1, SWITCH, ROUTER } TIPOS_DIS;

typedef struct {
	uint8_t ip[4];
	uint8_t mac[6];
} Endereco;

struct Cabo {
	struct Dispositivo *left;
	struct Dispositivo *right;
};

struct Dispositivo {
	Vector2 pos;
	TIPOS_DIS tipo;
	Endereco end;
	Endereco **conectados;
	struct Cabo *cabeado;
	char *nome;
};

struct World {
	int cabos_size;
	int dis_size;
	struct Dispositivo all[100];
	struct Cabo cabos[100];
};

#endif	// !DEVICES_H
