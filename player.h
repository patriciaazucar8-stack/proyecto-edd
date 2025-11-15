#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

typedef struct {
    char nombre[64];
    Pokemon pokemon;
    int esCPU; // 0 = humano, 1 = cpu
} Jugador;

// Inicializa un jugador con nombre, copia del Pokémon y flag esCPU
void inicializarJugador(Jugador *j, const char *nombre, const Pokemon *p, int esCPU);

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include "pokemon.h"

// Representa a un jugador (nombre y Pokémon seleccionado)
typedef struct {
    char nombre[64];
    Pokemon pokemon;
    int esCPU; // 0 = humano, 1 = CPU
} Jugador;

// Crea/Inicializa un jugador a partir de nombre y prototipo de Pokémon
void inicializarJugador(Jugador *j, const char *nombre, const Pokemon *proto, int esCPU);

#endif