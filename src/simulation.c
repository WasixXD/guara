#include "simulation.h"
#include "devices.h"
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>

ARP prepare_arp_packet(struct Cabo *c, uint16_t operation) {
	ARP new_arp_packet;

	uint16_t hardware_type = 0x0001;
	uint16_t protocol_type = 0x0800;

	uint8_t hardware_length = 0x06;
	uint8_t protocol_length = 0x04;

	new_arp_packet.HT = hardware_type;
	new_arp_packet.PT = protocol_type;
	new_arp_packet.HL = hardware_length;
	new_arp_packet.PL = protocol_length;
	new_arp_packet.OP = operation;

	new_arp_packet.reme = &c->left->end;
	new_arp_packet.dest = &c->right->end;

	return new_arp_packet;
}
