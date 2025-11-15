#include "player.h"
#include <string.h>

void inicializarJugador(Jugador *j, const char *nombre, const Pokemon *proto, int esCPU) {
    if (!j) return;
    memset(j, 0, sizeof(Jugador));
    strncpy(j->nombre, nombre ? nombre : "", sizeof(j->nombre)-1);
    j->nombre[sizeof(j->nombre)-1] = '\0';
    if (proto) j->pokemon = *proto;
    j->esCPU = esCPU ? 1 : 0;
}