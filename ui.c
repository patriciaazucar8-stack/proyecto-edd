#include "ui.h"
#include <stdio.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

void pantallaInicio() {
    // Cabecera simple y robusta para evitar problemas de renderizado
    const int ancho = 60;
    const char *titulo = "POKEWAR";
    int padding = (ancho - (int)strlen(titulo)) / 2;
    if (padding < 0) padding = 0;

    // Marco superior
    printf("\n%s", AMARILLO);
    for (int i = 0; i < ancho; ++i) putchar('=');
    printf("%s\n", RESET);

    // Línea vacía con color
    printf("%s", CIAN);
    for (int i = 0; i < padding; ++i) putchar(' ');
    printf("%s%s%s\n", AMARILLO, titulo, RESET);

    // Subtítulo
    printf("%s\n", CIAN);
    printf("      Un juego de batallas elementales - Fuego  Agua  Planta\n");
    printf("%s\n", RESET);

    // Marco inferior
    printf("%s", AMARILLO);
    for (int i = 0; i < ancho; ++i) putchar('=');
    printf("%s\n\n", RESET);

    printf(" Presiona ENTER para continuar...");
    getchar();
}

int menuPrincipal() {
    int opcion;
    printf("\n%s================== MENU PRINCIPAL ==================%s\n", MAGENTA, RESET);
    printf("%s 1)%s Jugar\n", AZUL, RESET);
    printf("%s 2)%s Ver Historial\n", CIAN, RESET);
    printf("%s 3)%s Salir\n", ROJO, RESET);
    printf("%s====================================================%s\n", MAGENTA, RESET);
    printf("Elige una opcion: ");

    if (scanf("%d", &opcion) != 1) {
        while (getchar() != '\n');
        return 0;
    }
    // limpiar newline pendiente
    getchar();
    return opcion;
}

int menuSeleccion() {
    int opcion;
    printf("\n%s================= SELECCIONA TU POKEMON =================%s\n\n", AZUL, RESET);

    printf("  %s[1]%s Lapras      (Agua)\n", AMARILLO, RESET);
    printf("  %s[2]%s Vaporeon    (Agua)\n", AMARILLO, RESET);
    printf("  %s[3]%s Piplup      (Agua)\n\n", AMARILLO, RESET);

    printf("  %s[4]%s Charizard   (Fuego)\n", AMARILLO, RESET);
    printf("  %s[5]%s Flareon     (Fuego)\n", AMARILLO, RESET);
    printf("  %s[6]%s Chimchar    (Fuego)\n\n", AMARILLO, RESET);

    printf("  %s[7]%s Bulbasaur   (Planta)\n", AMARILLO, RESET);
    printf("  %s[8]%s Leafeon     (Planta)\n", AMARILLO, RESET);
    printf("  %s[9]%s Turtwig     (Planta)\n\n", AMARILLO, RESET);

    printf("Ingresa el numero (1-9): ");
    if (scanf("%d", &opcion) != 1) {
        while (getchar() != '\n');
        opcion = 1;
    }
    while(opcion < 1 || opcion > 9) {
        printf("Opcion invalida. Intenta nuevamente (1-9): ");
        if (scanf("%d", &opcion) != 1) {
            while (getchar() != '\n');
            opcion = 1;
        }
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

const char* colorDelTipo(const char tipo[]) {
    if(strcmp(tipo, "agua") == 0) return CIAN;
    if(strcmp(tipo, "fuego") == 0) return ROJO;
    return VERDE; // planta -> verde
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
    printf("%s %s aparece!%s\n\n", color, nombre, RESET);
}

void pantallaVS(const char* nombre1, const char* nombre2) {
    printf("\n\n");
    printf("         %s%s%s  %sVS%s  %s%s%s\n\n", VERDE, nombre1, RESET, AMARILLO, RESET, ROJO, nombre2, RESET);
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

// Mostrar la barra completa (con salto de línea)
void mostrarBarraHP(int hp, int hpMax) {
    if(hp < 0) hp = 0;
    int anchoBarra = 30;
    float proporcion = (float)hp / (float)hpMax;
    int bloques = (int)(proporcion * anchoBarra + 0.0001f);

    const char* color;
    if(proporcion > 0.5f) color = VERDE;
    else if(proporcion > 0.25f) color = AMARILLO;
    else color = ROJO;

    // Usar caracteres ASCII para compatibilidad en Windows
    printf("%s[", color);
    for(int i = 0; i < anchoBarra; i++) {
        if(i < bloques) printf("=");
        else printf("-");
    }
    printf("] %3d/%d%s\n", hp, hpMax, RESET);
}

// Mostrar la barra en la misma línea sin salto de línea (para animar)
void mostrarBarraHP_inline(int hp, int hpMax) {
    if(hp < 0) hp = 0;
    int anchoBarra = 30;
    float proporcion = (float)hp / (float)hpMax;
    int bloques = (int)(proporcion * anchoBarra + 0.0001f);

    const char* color;
    if(proporcion > 0.5f) color = VERDE;
    else if(proporcion > 0.25f) color = AMARILLO;
    else color = ROJO;

    printf("%s[", color);
    for(int i = 0; i < anchoBarra; i++) {
        if(i < bloques) printf("=");
        else printf("-");
    }
    printf("] %3d/%d%s", hp, hpMax, RESET);
    fflush(stdout);
}

void animarHP(int* hp, int hpMax, int dano) {
    int objetivo = *hp - dano;
    if(objetivo < 0) objetivo = 0;

    // Mostrar la barra inicial en la misma línea
    mostrarBarraHP_inline(*hp, hpMax);

    // Reducir en pasos para animación más suave sin llenar la pantalla
    int paso = (dano > 20) ? 2 : 1;
    while(*hp > objetivo) {
        if(*hp - paso < objetivo) {
            *hp = objetivo;
        } else {
            *hp -= paso;
        }

        // Volver al inicio de la línea y reimprimir la barra
        printf("\r");
        mostrarBarraHP_inline(*hp, hpMax);
        fflush(stdout);

        #ifdef _WIN32
            Sleep(40);
        #else
            usleep(40000);
        #endif
    }

    // Al finalizar, imprimir salto de línea para que siguientes mensajes no sobrescriban
    printf("\n");
}

void animacionKO(const char* nombre) {
    printf("\n%s esta debilitado...\n", nombre);
    for(int i = 0; i < 3; i++){
        printf(".");
        fflush(stdout);
        #ifdef _WIN32
            Sleep(500);
        #else
            usleep(500000);
        #endif
    }
    printf("\n\n*** %s ha caido ***\n\n", nombre);

    #ifdef _WIN32
        Sleep(900);
    #else
        usleep(900000);
    #endif
}

void pausar() {
    printf("\nPresiona ENTER para continuar...");
    getchar();
}
