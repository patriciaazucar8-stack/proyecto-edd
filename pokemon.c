#include "pokemon.h"
#include <string.h>
#include <stdlib.h>

// ----------------- Pools de movimientos (10 por tipo) -----------------
Movimiento aguaPool[10] = {
    {"Aqua Pulse", 25, "Un chorro de agua sale disparado a gran presión."},
    {"Bubble Beam", 22, "Ráfagas de burbujas golpean al enemigo."},
    {"Water Strike", 20, "Un golpe húmedo y rápido alcanza al rival."},
    {"Tidal Push", 28, "Una ola corta surge y empuja con fuerza."},
    {"Rain Shot", 18, "Gotas veloces se disparan como proyectiles."},
    {"Splash Jet", 24, "Un chorro repentino envuelve al enemigo."},
    {"Aqua Bite", 26, "Una mordida cubierta en agua impacta con fuerza."},
    {"Hydro Swipe", 23, "Un corte fluido se desliza hacia adelante."},
    {"Deep Current", 30, "Una corriente profunda arrastra al oponente."},
    {"Wave Claw", 27, "Garras envueltas en agua cortan el aire."}
};

Movimiento fuegoPool[10] = {
    {"Flamethrower", 25, "Una llamarada ardiente envuelve al enemigo."},
    {"Fire Burst", 22, "Una explosión corta de fuego estalla al frente."},
    {"Ember Strike", 20, "Brazas encendidas se proyectan violentamente."},
    {"Blaze Impact", 28, "El calor se concentra en un golpe devastador."},
    {"Burning Dash", 18, "El usuario embiste envuelto en fuego."},
    {"Flare Claw", 26, "Garras envueltas en calor rasgan al enemigo."},
    {"Heat Spiral", 24, "Columnas de aire caliente giran hacia el rival."},
    {"Inferno Shot", 30, "Una bola de fuego intensa se dispara a distancia."},
    {"Scorch Bite", 27, "Una mordida ardiente deja marcas incandescentes."},
    {"Ash Storm", 23, "Cenizas abrasadoras caen como una lluvia caliente."}
};

Movimiento hieloPool[10] = {
    {"Ice Shard", 25, "Trozos de hielo afilado vuelan hacia el objetivo."},
    {"Frost Bite", 22, "Un toque helado inmoviliza brevemente al oponente."},
    {"Crystal Spike", 20, "Cristales fríos se forman y son lanzados."},
    {"Glacier Slam", 28, "Un golpe pesado con frío profundo."},
    {"Snow Burst", 18, "Copos densos golpean en ráfagas rápidas."},
    {"Chill Swipe", 23, "Garras heladas cortan con precisión."},
    {"Winter Wave", 24, "Una ola gélida recorre el campo de batalla."},
    {"Polar Beam", 30, "Un rayo congelante atraviesa la distancia."},
    {"Frozen Dash", 26, "Una embestida cubierta de hielo impacta con fuerza."},
    {"Shiver Storm", 27, "Un viento glacial sacude el ambiente."}
};

// ----------------- Lista de pokémon base -----------------
Pokemon lapras = {"Lapras", "agua", {{0}}};
Pokemon vaporeon = {"Vaporeon", "agua", {{0}}};
Pokemon piplup = {"Piplup", "agua", {{0}}};

Pokemon charizard = {"Charizard", "fuego", {{0}}};
Pokemon flareon = {"Flareon", "fuego", {{0}}};
Pokemon chimchar = {"Chimchar", "fuego", {{0}}};

Pokemon articuno = {"Articuno", "hielo", {{0}}};
Pokemon glaceon = {"Glaceon", "hielo", {{0}}};
Pokemon seel = {"Seel", "hielo", {{0}}};

// Asigna 4 movimientos aleatorios SIN REPETIR
void asignarMovimientos(Pokemon *p) {
    Movimiento *pool;
    int cantidad = 10;

    if(strcmp(p->tipo, "agua") == 0) pool = aguaPool;
    else if(strcmp(p->tipo, "fuego") == 0) pool = fuegoPool;
    else pool = hieloPool;

    // Array para rastrear índices ya usados
    int usados[10] = {0}; // 0 = no usado, 1 = usado
    
    for(int i = 0; i < 4; i++) {
        int r;
        // Buscar un índice no usado
        do {
            r = rand() % cantidad;
        } while(usados[r] == 1);
        
        usados[r] = 1; // marcar como usado
        p->movimientos[i] = pool[r];
    }
}

Movimiento movimientoMasFuerte(Pokemon p) {
    Movimiento mayor = p.movimientos[0];
    for(int i = 1; i < 4; i++) {
        if(p.movimientos[i].poder > mayor.poder)
            mayor = p.movimientos[i];
    }
    return mayor;
}

float obtenerMultiplicador(const char atacante[], const char defensor[]) {
    if(strcmp(atacante, "agua") == 0 && strcmp(defensor, "fuego") == 0) return 1.5f;
    if(strcmp(atacante, "fuego") == 0 && strcmp(defensor, "hielo") == 0) return 1.5f;
    if(strcmp(atacante, "hielo") == 0 && strcmp(defensor, "agua") == 0) return 1.5f;

    if(strcmp(atacante, "agua") == 0 && strcmp(defensor, "hielo") == 0) return 0.5f;
    if(strcmp(atacante, "fuego") == 0 && strcmp(defensor, "agua") == 0) return 0.5f;
    if(strcmp(atacante, "hielo") == 0 && strcmp(defensor, "fuego") == 0) return 0.5f;

    return 1.0f;
}

// Obtiene un Pokémon aleatorio de cualquier tipo
Pokemon obtenerPokemonAleatorio() {
    Pokemon listaPokemon[9] = {
        lapras, vaporeon, piplup,
        charizard, flareon, chimchar,
        articuno, glaceon, seel
    };
    
    int indice = rand() % 9;
    return listaPokemon[indice];
}
