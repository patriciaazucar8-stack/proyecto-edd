#ifndef UI_H
#define UI_H

#include "pokemon.h"

// ----------------- Colores -----------------
#define RESET   "\x1b[0m"
#define ROJO    "\x1b[31m"
#define AZUL    "\x1b[34m"
#define CIAN    "\x1b[36m"
#define AMARILLO "\x1b[33m"
#define VERDE   "\x1b[32m"
#define MAGENTA "\x1b[35m"

// ----------------- Funciones de UI -----------------
void pantallaInicio();
int menuPrincipal();
int menuSeleccion();
void confirmarSeleccion(const char* nombre);
const char* colorDelTipo(const char tipo[]);
void aparecerPokemon(const char* nombre, const char* color);
void pantallaVS(const char* nombre1, const char* nombre2);
void animarAtaque(const char* nombre, const char* movimiento, const char* colorElemento);
void mostrarBarraHP(int hp, int hpMax);
// Muestra la barra sin añadir salto de línea (útil para animaciones in-place)
void mostrarBarraHP_inline(int hp, int hpMax);
void animarHP(int* hp, int hpMax, int dano);
void animacionKO(const char* nombre);
void pausar();

#endif
