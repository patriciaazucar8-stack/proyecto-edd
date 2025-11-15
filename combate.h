#ifndef COMBATE_H
#define COMBATE_H

#include "player.h"
#include "historial.h"

// Ejecuta el combate usando una cola de turnos.
// Retorna 1 si gana jugador A (jugador[0]), 2 si gana jugador B (jugador[1]).
// Además registra la partida en el historial (si hist != NULL).
int combate(Jugador jugadores[2], Historial *hist);

#endif