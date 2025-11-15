#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "player.h"

// TDA Partida
typedef struct Partida {
    int id;
    char jugador1[64];
    char pokemon1[32];
    char jugador2[64];
    char pokemon2[32];
    char resultado[64]; // descripción (ej: "Ganó Paula (Lapras)")
    struct Partida *next; // para encadenamiento en bucket
} Partida;

// Historial con mapa hash por id (encadenamiento simple)
typedef struct {
    Partida **buckets;
    int bucket_count;
    int next_id;
} Historial;

// Inicializa el historial (debe llamar una vez)
void historial_init(Historial *h, int buckets);

// Inserta una partida en el historial
void historial_insert(Historial *h,
                      const char *jugador1, const char *pokemon1,
                      const char *jugador2, const char *pokemon2,
                      const char *resultado);

// Imprime el historial ordenado por id. Si filtro es NULL o cadena vacía, muestra todo.
// Si filtro no es NULL, imprime solo partidas donde jugador1 o jugador2 contienen
// la cadena filtro (búsqueda case-insensitive, substring).
void historial_print(const Historial *h, const char *filtro);

// Libera memoria usada por historial
void historial_free(Historial *h);

#endif