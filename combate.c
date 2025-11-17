#include "combate.h"
#include "ui.h"
#include "pokemon.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Cola circular simple para índices 0/1 (turnos)
typedef struct {
    int items[2];
    int head;
    int tail;
    int size;
} ColaTurnos;

static void cola_init(ColaTurnos *q, int a, int b) {
    q->items[0] = a;
    q->items[1] = b;
    q->head = 0;
    q->tail = 0; 
    q->size = 2;
}

static int cola_pop(ColaTurnos *q) {
    int val = q->items[q->head];
    q->head = (q->head + 1) % q->size;
    return val;
}

static void cola_push_back(ColaTurnos *q, int val) {
    int idx = (q->head + q->size - 1) % q->size;
    q->items[idx] = val; 
}

// Registra en historial si se tiene
static void registrar_partida_si(Historial *h, Jugador *a, Jugador *b, const char *res) {
    if (!h) return;
    historial_insert(h, a->nombre, a->pokemon.nombre, b->nombre, b->pokemon.nombre, res);
}

// Ejecuta el combate: alterna turnos en la cola
int combate(Jugador jugadores[2], Historial *hist) {
    int HP[2] = {200, 200};
    ColaTurnos q;
    cola_init(&q, 0, 1);
    int turno = 1;

    while (HP[0] > 0 && HP[1] > 0) {
        printf("\n%s================================================================%s\n", AMARILLO, RESET);
        printf("%s                       TURNO %d                                %s\n", AMARILLO, turno, RESET);
        printf("%s================================================================%s\n\n", AMARILLO, RESET);

        // Mostrar ambos estados
        printf("%s+----------------------------------------------------------+%s\n", VERDE, RESET);
        printf("%s|  JUGADOR 1:%s %s%-15s%s (Tipo: %-6s)              %s|%s\n",
            VERDE, RESET, VERDE, jugadores[0].nombre, RESET, jugadores[0].pokemon.tipo, VERDE, RESET);
        mostrarBarraHP(HP[0], 200);
        printf("%s+----------------------------------------------------------+%s\n", VERDE, RESET);

        printf("\n%s+----------------------------------------------------------+%s\n", ROJO, RESET);
        printf("%s|  JUGADOR 2:%s %s%-15s%s (Tipo: %-6s)              %s|%s\n",
            ROJO, RESET, ROJO, jugadores[1].nombre, RESET, jugadores[1].pokemon.tipo, ROJO, RESET);
        mostrarBarraHP(HP[1], 200);
        printf("%s+----------------------------------------------------------+%s\n", ROJO, RESET);

        // Determinar atacante (pop) y defensor (el otro)
        int atacante = cola_pop(&q);
        int defensor = (atacante == 0) ? 1 : 0;

        Jugador *J_at = &jugadores[atacante];
        Jugador *J_def = &jugadores[defensor];
        
        // Selección de movimiento para atacante
        Movimiento movAt;
        if (J_at->esCPU) {
            Movimiento movCPU;
            if (HP[defensor] < 40) {
                // Rival débil: 60% probabilidad de usar el más fuerte (rematar)
                if ((rand() % 100) < 60) {
                    movCPU = movimientoMasFuerte(J_at->pokemon);
                } else {
                    int indice = rand() % 4; // ataque aleatorio
                    movCPU = J_at -> pokemon.movimientos[indice]; 
                }
            } else {
                // Rival fuerte: 60% probabilidad de usar aleatorio
                if ((rand() % 100) < 60) {
                    int indice = rand() % 4;
                    movCPU = J_at -> pokemon.movimientos[indice];
                } else {
                    movCPU = movimientoMasFuerte(J_at->pokemon);
                }
            }
            movAt = movCPU;
            printf("\nTurno de %s (CPU). Usa %s\n", J_at->nombre, movAt.nombre);
        } else {
            // mostrar opciones y leer elección
            printf("\nTurno de %s. Elige movimiento:\n", J_at->nombre);
            for (int i = 0; i < 4; ++i)
                printf("  [%d] %s (Poder %d)\n", i+1, J_at->pokemon.movimientos[i].nombre, J_at->pokemon.movimientos[i].poder);
            int op = 0;
            printf("> ");
            if (scanf("%d", &op) != 1) {
                while(getchar() != '\n');
                printf("Entrada invalida. Se seleccionara 1 por defecto.\n");
                op = 1;
            }
            while (op < 1 || op > 4) {
                printf("Opcion invalida. Elige 1-4: ");
                scanf("%d", &op);
            }
            getchar(); // limpiar newline
            movAt = J_at->pokemon.movimientos[op-1];
        }


        float multAt = obtenerMultiplicador(J_at->pokemon.tipo, J_def->pokemon.tipo);
        int dano = (int)(movAt.poder * multAt + 0.5f);

        // Animación ataque
        animarAtaque(J_at->pokemon.nombre, movAt.nombre, colorDelTipo(J_at->pokemon.tipo));
        printf("%s%s%s\n", CIAN, movAt.descripcion, RESET);

        printf("\n %s pierde %d HP!\n", J_def->pokemon.nombre, dano);
        if (defensor == 0) animarHP(&HP[0], 200, dano);
        else animarHP(&HP[1], 200, dano);

        if (multAt == 1.5f) printf("%s Es super eficaz!%s\n", VERDE, RESET);
        else if (multAt == 0.75f) printf("%sNo es muy eficaz...%s\n", AMARILLO, RESET);

        // comprobar KO
        if (HP[defensor] <= 0) {
            animacionKO(J_def->pokemon.nombre);
            printf("%s %s gana el combate!%s\n", VERDE, J_at->nombre, RESET);

            char resultado[128];
            snprintf(resultado, sizeof(resultado), "Ganador: %s (%s)", J_at->nombre, J_at->pokemon.nombre);
            // Insertar en historial
            registrar_partida_si(hist, &jugadores[0], &jugadores[1], resultado);
            return (atacante == 0) ? 1 : 2;
        }

        // Re-encolar para mantener alternancia (para tamaño 2 basta dejar la rotación)
        cola_push_back(&q, atacante);

        turno++;
    }

    // Seguridad
    return 0;
}
