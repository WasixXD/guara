#include <stdbool.h>
#include <stdint.h>
#ifndef SIMULATION_H
#include "devices.h"

typedef enum {
	ARP_SEND = 1,
	ICMP_SEND,
} ACTION;

typedef struct {
	ACTION acao;
	struct Cabo *cabo;
} Tarefa;

typedef struct {
	Tarefa **tarefas;
	int size;
} Fila;

ARP prepare_arp_packet(struct Cabo *c, uint16_t operation);

#endif // !SIMULATION_H
