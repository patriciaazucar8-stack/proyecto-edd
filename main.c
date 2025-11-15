// main.c - Adaptado para mostrar historial ordenado y filtrar por jugador
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pokemon.h"
#include "ui.h"
#include "combate.h"
#include "player.h"
#include "historial.h"

int main(void) {
    srand((unsigned int)time(NULL));

    pantallaInicio();

    Historial hist;
    historial_init(&hist, 16);

    int running = 1;
    while (running) {
        int opcion = menuPrincipal();
        switch (opcion) {
            case 1: { // Jugar
                char nombre1[64];
                char nombre2[64];

                printf("\nIngrese nombre del Jugador 1: ");
                if (fgets(nombre1, sizeof(nombre1), stdin)) {
                    nombre1[strcspn(nombre1, "\n")] = '\0';
                }

                printf("Ingrese nombre del Jugador 2 (o 'CPU' para jugar contra la máquina): ");
                if (fgets(nombre2, sizeof(nombre2), stdin)) {
                    nombre2[strcspn(nombre2, "\n")] = '\0';
                }

                // Selección de Pokémon para jugador 1
                printf("\nJugador %s, ", nombre1);
                int e1 = menuSeleccion();
                Pokemon p1;
                switch (e1) {
                    case 1: p1 = lapras; break;
                    case 2: p1 = vaporeon; break;
                    case 3: p1 = piplup; break;
                    case 4: p1 = charizard; break;
                    case 5: p1 = flareon; break;
                    case 6: p1 = chimchar; break;
                    case 7: p1 = bulbasaur; break;
                    case 8: p1 = leafeon; break;
                    case 9: p1 = turtwig; break;
                    default: p1 = lapras; break;
                }
                confirmarSeleccion(p1.nombre);
                asignarMovimientos(&p1);

                // Selección de Pokémon para jugador 2 (si CPU, elegir aleatorio)
                Pokemon p2;
                if (strcmp(nombre2, "CPU") == 0 || strcmp(nombre2, "cpu") == 0 || strlen(nombre2) == 0) {
                    p2 = obtenerPokemonAleatorio();
                    asignarMovimientos(&p2);
                    printf("\nEl rival será CPU con %s (Tipo %s)\n", p2.nombre, p2.tipo);
                } else {
                    printf("\nJugador %s, ", nombre2);
                    int e2 = menuSeleccion();
                    switch (e2) {
                        case 1: p2 = lapras; break;
                        case 2: p2 = vaporeon; break;
                        case 3: p2 = piplup; break;
                        case 4: p2 = charizard; break;
                        case 5: p2 = flareon; break;
                        case 6: p2 = chimchar; break;
                        case 7: p2 = bulbasaur; break;
                        case 8: p2 = leafeon; break;
                        case 9: p2 = turtwig; break;
                        default: p2 = lapras; break;
                    }
                    asignarMovimientos(&p2);
                }

                // Inicializar jugadores
                Jugador jugadores[2];
                inicializarJugador(&jugadores[0], nombre1, &p1, 0);
                int esCPU = (strcmp(nombre2, "CPU") == 0 || strcmp(nombre2, "cpu") == 0 || strlen(nombre2) == 0);
                inicializarJugador(&jugadores[1], nombre2, &p2, esCPU);

                // Apariciones y VS
                aparecerPokemon(jugadores[0].pokemon.nombre, VERDE);
                aparecerPokemon(jugadores[1].pokemon.nombre, ROJO);
                pantallaVS(jugadores[0].pokemon.nombre, jugadores[1].pokemon.nombre);

                int ganador = combate(jugadores, &hist);
                (void)ganador;

                pausar();
            } break;

            case 2: { // Ver Historial (ahora con opción de filtrar)
                printf("\nVer Historial:\n");
                printf("  1) Mostrar todo (ordenado por ID)\n");
                printf("  2) Filtrar por jugador (nombre)\n");
                printf("Elija una opción: ");
                int s = 0;
                if (scanf("%d", &s) != 1) {
                    while(getchar() != '\n');
                    s = 1;
                }
                getchar(); // limpiar newline

                if (s == 2) {
                    char filtro[64];
                    printf("Ingrese nombre (o fragmento) del jugador a filtrar: ");
                    if (fgets(filtro, sizeof(filtro), stdin)) {
                        filtro[strcspn(filtro, "\n")] = '\0';
                    }
                    historial_print(&hist, filtro);
                } else {
                    historial_print(&hist, NULL);
                }
                pausar();
            } break;

            case 3: // Salir
                running = 0;
                break;

            default:
                printf("Opción no válida.\n");
                break;
        }
    }

    historial_free(&hist);
    printf("Gracias por jugar. ¡Hasta luego!\n");
    return 0;
}