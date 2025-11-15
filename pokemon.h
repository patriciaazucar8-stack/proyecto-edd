#ifndef POKEMON_H
#define POKEMON_H

// ----------------- Estructuras -----------------
typedef struct {
    char nombre[32];
    int poder;
    char descripcion[120];
} Movimiento;

typedef struct {
    char nombre[32];
    char tipo[10]; // "agua", "fuego", "hielo"
    Movimiento movimientos[4];
} Pokemon;

// ----------------- Pools de movimientos -----------------
extern Movimiento aguaPool[10];
extern Movimiento fuegoPool[10];
extern Movimiento hieloPool[10];

// ----------------- Pokémon base -----------------
extern Pokemon lapras;
extern Pokemon vaporeon;
extern Pokemon piplup;
extern Pokemon charizard;
extern Pokemon flareon;
extern Pokemon chimchar;
extern Pokemon articuno;
extern Pokemon glaceon;
extern Pokemon seel;

// ----------------- Funciones -----------------
void asignarMovimientos(Pokemon *p);
Movimiento movimientoMasFuerte(Pokemon p);
float obtenerMultiplicador(const char atacante[], const char defensor[]);
Pokemon obtenerPokemonAleatorio();

#endif
