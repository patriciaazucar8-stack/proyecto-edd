// main.c - POKEWAR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

// ----------------- Colores -----------------
#define RESET   "\x1b[0m"
#define ROJO    "\x1b[31m"
#define AZUL    "\x1b[34m"
#define CIAN    "\x1b[36m"
#define AMARILLO "\x1b[33m"
#define VERDE   "\x1b[32m"

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

// ----------------- Prototipos visuales -----------------
void pantallaInicio();
int menuSeleccion();
void confirmarSeleccion(const char* nombre);
void asignarMovimientos(Pokemon *p);
Movimiento movimientoMasFuerte(Pokemon p);
float obtenerMultiplicador(const char atacante[], const char defensor[]);
const char* colorDelTipo(const char tipo[]);
void aparecerPokemon(const char* nombre, const char* color);
void pantallaVS(const char* nombre1, const char* nombre2);
void animarAtaque(const char* nombre, const char* movimiento, const char* colorElemento);
void mostrarBarraHP(int hp, int hpMax);
void animarHP(int* hp, int hpMax, int dano);
void animacionKO(const char* nombre);
void pausar();
int combate(Pokemon jugador, Pokemon enemigo); // devuelve 1 si jugador gana, 0 si CPU gana

// ----------------- Implementaciones -----------------

void pantallaInicio() {
    printf("\n%s", AMARILLO);
    printf("██████╗  ██████╗ ██╗  ██╗███████╗██╗    ██╗██╗    ██╗ █████╗ ██████╗ \n");
    printf("██╔══██╗██╔═══██╗██║ ██╔╝██╔════╝██║    ██║██║    ██║██╔══██╗██╔══██╗\n");
    printf("██████╔╝██║   ██║█████╔╝ █████╗  ██║ █╗ ██║██║ █╗ ██║███████║██████╔╝\n");
    printf("██╔══██╗██║   ██║██╔═██╗ ██╔══╝  ██║███╗██║██║███╗██║██╔══██║██╔══██╗\n");
    printf("██║  ██║╚██████╔╝██║  ██╗███████╗╚███╔███╔╝╚███╔███╔╝██║  ██║██║  ██║\n");
    printf("╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝ ╚══╝╚══╝  ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝\n");
    printf("%s", RESET);

    printf("\n                  %sP  O  K  E  W  A  R%s\n", CIAN, RESET);
    printf("        Un juego de batallas elementales\n");
    printf("           Fuego  Agua  Hielo\n");
    printf("\n Presiona ENTER para continuar...");
    getchar(); // primer ENTER pendiente (si lo hubiera)
    getchar(); // espera del usuario
}

int menuSeleccion() {
    int opcion;
    printf("\n================= SELECCIONA TU POKÉMON =================\n\n");

    printf("  [1] Lapras      (Agua)\n");
    printf("  [2] Vaporeon    (Agua)\n");
    printf("  [3] Piplup      (Agua)\n\n");

    printf("  [4] Charizard   (Fuego)\n");
    printf("  [5] Flareon     (Fuego)\n");
    printf("  [6] Chimchar    (Fuego)\n\n");

    printf("  [7] Articuno    (Hielo)\n");
    printf("  [8] Glaceon     (Hielo)\n");
    printf("  [9] Seel        (Hielo)\n\n");

    printf("Ingresa el número: ");
    scanf("%d", &opcion);

    while(opcion < 1 || opcion > 9){
        printf("\nOpción inválida. Intenta nuevamente: ");
        scanf("%d", &opcion);
    }

    // limpiar newline pendiente
    getchar();
    return opcion;
}

void confirmarSeleccion(const char* nombre) {
    printf("\nHas elegido: %s\n", nombre);

    #ifdef _WIN32
        Sleep(800);
    #else
        usleep(800000);
    #endif

    printf("Preparando combate");
    for(int i = 0; i < 3; i++) {
        printf(".");
        fflush(stdout);
        #ifdef _WIN32
            Sleep(500);
        #else
            usleep(500000);
        #endif
    }
    printf("\n\n");
}

// Asigna 4 movimientos aleatorios (puede repetirse)
void asignarMovimientos(Pokemon *p) {
    Movimiento *pool;
    int cantidad = 10;

    if(strcmp(p->tipo, "agua") == 0) pool = aguaPool;
    else if(strcmp(p->tipo, "fuego") == 0) pool = fuegoPool;
    else pool = hieloPool;

    for(int i = 0; i < 4; i++) {
        int r = rand() % cantidad;
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

const char* colorDelTipo(const char tipo[]) {
    if(strcmp(tipo, "agua") == 0) return CIAN;
    if(strcmp(tipo, "fuego") == 0) return ROJO;
    return AZUL; // hielo -> azul
}

void aparecerPokemon(const char* nombre, const char* color) {
    printf("\n");
    for(int i = 0; i < 3; i++) {
        printf("%s.%s\n", color, RESET);
        fflush(stdout);
        #ifdef _WIN32
            Sleep(300);
        #else
            usleep(300000);
        #endif
    }
    printf("%s¡%s aparece!%s\n\n", color, nombre, RESET);
}

void pantallaVS(const char* nombre1, const char* nombre2) {
    printf("\n\n");
    printf("           %s%s%s", VERDE, nombre1, RESET);
    printf("        %sVS%s        ", AMARILLO, RESET);
    printf("%s%s%s\n\n", ROJO, nombre2, RESET);

    #ifdef _WIN32
        Sleep(900);
    #else
        usleep(900000);
    #endif
}

void animarAtaque(const char* nombre, const char* movimiento, const char* colorElemento) {
    printf("%s%s%s usa %s%s\n", colorElemento, nombre, RESET, movimiento, RESET);

    for(int i = 0; i < 12; i++) {
        printf("%s>%s", colorElemento, RESET);
        fflush(stdout);
        #ifdef _WIN32
            Sleep(40);
        #else
            usleep(40000);
        #endif
    }
    printf("\n");
}

void mostrarBarraHP(int hp, int hpMax) {
    if(hp < 0) hp = 0;
    int anchoBarra = 20;
    float proporcion = (float)hp / (float)hpMax;
    int bloques = (int)(proporcion * anchoBarra + 0.0001f);

    const char* color;
    if(proporcion > 0.5f) color = VERDE;
    else if(proporcion > 0.25f) color = AMARILLO;
    else color = ROJO;

    printf("%s[", color);
    for(int i = 0; i < anchoBarra; i++) {
        if(i < bloques) printf("█");
        else printf(" ");
    }
    printf("] %d/%d%s\n", hp, hpMax, RESET);
}

// Animación que reduce la barra paso a paso
void animarHP(int* hp, int hpMax, int dano) {
    int objetivo = *hp - dano;
    if(objetivo < 0) objetivo = 0;

    // mostrar la barra actual completa una vez
    mostrarBarraHP(*hp, hpMax);

    // reducimos de a 1 para la animación
    while(*hp > objetivo) {
        (*hp)--;
        mostrarBarraHP(*hp, hpMax);
        fflush(stdout);

        #ifdef _WIN32
            Sleep(20);
        #else
            usleep(20000);
        #endif
    }
}

void animacionKO(const char* nombre) {
    printf("\n%s está debilitado...\n", nombre);
    for(int i = 0; i < 3; i++){
        printf(".");
        fflush(stdout);
        #ifdef _WIN32
            Sleep(500);
        #else
            usleep(500000);
        #endif
    }
    printf("\n\n*** %s ha caído ***\n\n", nombre);

    #ifdef _WIN32
        Sleep(900);
    #else
        usleep(900000);
    #endif
}

void pausar() {
    printf("\nPresiona ENTER para continuar...");
    getchar();
    // si hay pendiente, leer otro
    // en la mayoría de casos con un getchar() alcanza
}

// ----------------- Función de combate -----------------
// Retorna 1 si gana el jugador, 0 si gana la CPU
int combate(Pokemon jugador, Pokemon enemigo) {
    int HP_J = 200, HP_E = 200;
    int turno = 1;

    while(HP_J > 0 && HP_E > 0) {
        printf("\n%s--- TURNO %d ---%s\n", AMARILLO, turno, RESET);

        printf("\n%s (Tipo %s)\n", jugador.nombre, jugador.tipo);
        mostrarBarraHP(HP_J, 200);

        printf("\n%s (Tipo %s)\n", enemigo.nombre, enemigo.tipo);
        mostrarBarraHP(HP_E, 200);

        printf("\nElige un movimiento:\n");
        for(int i = 0; i < 4; i++)
            printf("%d) %s (Poder %d)\n", i+1, jugador.movimientos[i].nombre, jugador.movimientos[i].poder);

        int op = 0;
        printf("> ");
        if(scanf("%d", &op) != 1) {
            // entrada inválida: limpiar buffer y pedir de nuevo
            while(getchar() != '\n');
            printf("Entrada inválida. Se seleccionará el movimiento 1 por defecto.\n");
            op = 1;
        }
        while(op < 1 || op > 4) {
            printf("Opción inválida. Elige 1-4: ");
            scanf("%d", &op);
        }
        // limpiar newline
        getchar();

        Movimiento movJ = jugador.movimientos[op-1];
        Movimiento movE = movimientoMasFuerte(enemigo);

        float multJugador = obtenerMultiplicador(jugador.tipo, enemigo.tipo);
        float multEnemigo = obtenerMultiplicador(enemigo.tipo, jugador.tipo);

        int danoJ = (int)(movJ.poder * multJugador + 0.5f);
        int danoE = (int)(movE.poder * multEnemigo + 0.5f);

        // Animación y descripción del movimiento del jugador
        animarAtaque(jugador.nombre, movJ.nombre, colorDelTipo(jugador.tipo));
        printf("%s%s%s\n", CIAN, movJ.descripcion, RESET);

        // Mensaje de daño y animación de HP enemigo
        printf("\n¡%s pierde %d HP!\n", enemigo.nombre, danoJ);
        animarHP(&HP_E, 200, danoJ);

        // Mensajes de efectividad
        if(multJugador == 1.5f)
            printf("%s¡Es súper eficaz!%s\n", VERDE, RESET);
        else if(multJugador == 0.5f)
            printf("%sNo es muy eficaz...%s\n", AMARILLO, RESET);

        if(HP_E <= 0) {
            animacionKO(enemigo.nombre);
            printf("%s¡GANASTE EL COMBATE!%s\n", VERDE, RESET);
            return 1;
        }

        // Ahora el enemigo ataca (usa su movimiento más fuerte)
        animarAtaque(enemigo.nombre, movE.nombre, colorDelTipo(enemigo.tipo));
        printf("%s%s%s\n", CIAN, movE.descripcion, RESET);

        printf("\n¡%s pierde %d HP!\n", jugador.nombre, danoE);
        animarHP(&HP_J, 200, danoE);

        if(multEnemigo == 1.5f)
            printf("%s¡Es súper eficaz!%s\n", ROJO, RESET);
        else if(multEnemigo == 0.5f)
            printf("%sNo es muy eficaz...%s\n", AMARILLO, RESET);

        if(HP_J <= 0) {
            animacionKO(jugador.nombre);
            printf("%sHAS PERDIDO EL COMBATE...%s\n", ROJO, RESET);
            return 0;
        }

        turno++;
    }

    // por seguridad (no debería llegar aquí)
    if(HP_J <= 0 && HP_E <= 0) {
        printf("Empate técnico.\n");
        return 0;
    } else if(HP_E <= 0) {
        printf("%s¡GANASTE EL COMBATE!%s\n", VERDE, RESET);
        return 1;
    } else {
        printf("%sHAS PERDIDO EL COMBATE...%s\n", ROJO, RESET);
        return 0;
    }
}

// ----------------- main -----------------
int main() {
    srand((unsigned int)time(NULL));

    pantallaInicio();

    int eleccion = menuSeleccion();

    Pokemon jugador;
    // inicializamos variable jugador copiando el prototipo correspondiente
    switch(eleccion){
        case 1: jugador = lapras; break;
        case 2: jugador = vaporeon; break;
        case 3: jugador = piplup; break;
        case 4: jugador = charizard; break;
        case 5: jugador = flareon; break;
        case 6: jugador = chimchar; break;
        case 7: jugador = articuno; break;
        case 8: jugador = glaceon; break;
        case 9: jugador = seel; break;
        default: jugador = lapras; break;
    }

    confirmarSeleccion(jugador.nombre);

    asignarMovimientos(&jugador);

    // ENEMIGO ALEATORIO TOTAL
    Pokemon enemigo;
    int tipoRival = rand() % 3;
    if(tipoRival == 0) {
        enemigo = lapras;
        enemigo = (rand()%3==0)? lapras : ((rand()%2)? vaporeon : piplup); // asegurar nombre aleatorio
        // simpler approach: pick uniformly
        if(rand() % 3 == 0) enemigo = lapras;
        else if(rand() % 3 == 1) enemigo = vaporeon;
        else enemigo = piplup;
    } else if(tipoRival == 1) {
        if(rand() % 3 == 0) enemigo = charizard;
        else if(rand() % 3 == 1) enemigo = flareon;
        else enemigo = chimchar;
    } else {
        if(rand() % 3 == 0) enemigo = articuno;
        else if(rand() % 3 == 1) enemigo = glaceon;
        else enemigo = seel;
    }

    asignarMovimientos(&enemigo);

    printf("\nTu rival será: %s (Tipo %s)\n", enemigo.nombre, enemigo.tipo);

    // Apariciones, VS y combate
    aparecerPokemon(jugador.nombre, VERDE);
    aparecerPokemon(enemigo.nombre, ROJO);
    pantallaVS(jugador.nombre, enemigo.nombre);

    int resultado = combate(jugador, enemigo);
    (void)resultado; // ignorado aquí, combate ya imprime el resultado

    pausar();
    return 0;
}
