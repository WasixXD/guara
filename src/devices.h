#ifndef DEVICES_H
#define DEVICES_H

#include <raylib.h>
#include <stdint.h>

typedef enum { DISPOSITIVO, SWITCH, ROUTER } TIPOS_DIS;

typedef struct {
  uint8_t ip[4];
  uint8_t mac[6];
} Endereco;

typedef struct {
  Vector2 pos;
  TIPOS_DIS tipo;
  /*Endereco end;*/
  char *nome;
} Dispositivo;

typedef struct {
  int size;
  Dispositivo all[100];
} World;

#endif // !DEVICES_H
