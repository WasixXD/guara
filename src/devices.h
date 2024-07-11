#ifndef DEVICES_H
#define DEVICES_H

#include <raylib.h>
#include <stdint.h>
#define ARP_REQ 0x0001
#define ARP_SND 0x0002

typedef enum { DISPOSITIVO = 1, SWITCH, ROUTER } TIPOS_DIS;

// https://datatracker.ietf.org/doc/html/rfc6747 - ARP RFC
typedef struct {
	uint8_t ip[4];
	uint8_t mac[6];
} Endereco;

typedef struct {
	uint16_t HT;
	uint16_t PT;
	uint8_t HL;
	uint8_t PL;
	uint16_t OP;
	Endereco *dest;
	Endereco *reme;
} ARP;

struct Cabo {
	struct Dispositivo *left;
	struct Dispositivo *right;
};

struct Dispositivo {
	Vector2 pos;
	TIPOS_DIS tipo;
	Endereco end;
	Endereco **conectados;
	struct Cabo **cabeado;
	int total_cabeados;
	char *nome;
};

struct World {
	int cabos_size;
	int dis_size;
	struct Dispositivo all[100];
	struct Cabo cabos[100];
};

#endif // !DEVICES_H
