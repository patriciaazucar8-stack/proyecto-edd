/* historial.c
 * Implementación del historial usando buckets con encadenamiento.
 */

#include "historial.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// helper: hash por int (id)
static int hash_int(int x, int buckets) {
    if (x < 0) x = -x;
    return x % buckets;
}

void historial_init(Historial *h, int buckets) {
    if (!h) return;
    h->bucket_count = (buckets > 0) ? buckets : 16;
    h->buckets = (Partida**)calloc(h->bucket_count, sizeof(Partida*));
    h->next_id = 1;
}

void historial_insert(Historial *h,
                      const char *jugador1, const char *pokemon1,
                      const char *jugador2, const char *pokemon2,
                      const char *resultado) {
    if (!h) return;
    Partida *p = (Partida*)malloc(sizeof(Partida));
    if (!p) return;
    p->id = h->next_id++;
    strncpy(p->jugador1, jugador1 ? jugador1 : "", sizeof(p->jugador1)-1); p->jugador1[sizeof(p->jugador1)-1] = '\0';
    strncpy(p->pokemon1, pokemon1 ? pokemon1 : "", sizeof(p->pokemon1)-1); p->pokemon1[sizeof(p->pokemon1)-1] = '\0';
    strncpy(p->jugador2, jugador2 ? jugador2 : "", sizeof(p->jugador2)-1); p->jugador2[sizeof(p->jugador2)-1] = '\0';
    strncpy(p->pokemon2, pokemon2 ? pokemon2 : "", sizeof(p->pokemon2)-1); p->pokemon2[sizeof(p->pokemon2)-1] = '\0';
    strncpy(p->resultado, resultado ? resultado : "", sizeof(p->resultado)-1); p->resultado[sizeof(p->resultado)-1] = '\0';
    p->next = NULL;

    int idx = hash_int(p->id, h->bucket_count);
    // Insertar al inicio del bucket (encadenamiento)
    p->next = h->buckets[idx];
    h->buckets[idx] = p;
}

// helper: case-insensitive substring check
static int contains_case_insensitive(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    if (*needle == '\0') return 1;
    size_t hlen = strlen(haystack);
    size_t nlen = strlen(needle);
    if (nlen > hlen) return 0;

    char *nlow = (char*)malloc(nlen + 1);
    if (!nlow) return 0;
    for (size_t i = 0; i < nlen; ++i) nlow[i] = (char)tolower((unsigned char)needle[i]);
    nlow[nlen] = '\0';

    int found = 0;
    for (size_t i = 0; i + nlen <= hlen; ++i) {
        size_t j;
        for (j = 0; j < nlen; ++j) {
            if (tolower((unsigned char)haystack[i+j]) != nlow[j]) break;
        }
        if (j == nlen) { found = 1; break; }
    }

    free(nlow);
    return found;
}

// comparator para qsort por id ascendente
static int cmp_partida_id(const void *a, const void *b) {
    const Partida * const *pa = (const Partida * const *)a;
    const Partida * const *pb = (const Partida * const *)b;
    return ((*pa)->id) - ((*pb)->id);
}

void historial_print(const Historial *h, const char *filtro) {
    if (!h || !h->buckets) {
        printf("Historial vacio.\n");
        return;
    }

    // 1) contar partidas totales
    int total = 0;
    for (int b = 0; b < h->bucket_count; ++b) {
        Partida *p = h->buckets[b];
        while (p) { total++; p = p->next; }
    }

    if (total == 0) {
        printf("Historial vacio.\n");
        return;
    }

    // 2) recolectar punteros en array
    Partida **arr = (Partida**)malloc(sizeof(Partida*) * total);
    if (!arr) {
        printf("Error de memoria al listar historial.\n");
        return;
    }
    int idx = 0;
    for (int b = 0; b < h->bucket_count; ++b) {
        Partida *p = h->buckets[b];
        while (p) {
            arr[idx++] = p;
            p = p->next;
        }
    }

    // 3) ordenar por id ascendente
    qsort(arr, total, sizeof(Partida*), cmp_partida_id);

    // 4) imprimir filtrando por jugador si corresponde
    int printed = 0;
    printf("\n===== HISTORIAL DE PARTIDAS (ordenado por ID) =====\n\n");
    for (int i = 0; i < total; ++i) {
        Partida *p = arr[i];
        int mostrar = 1;
        if (filtro && filtro[0] != '\0') {
            // mostrar sólo si filtro aparece en jugador1 o jugador2 (case-insensitive)
            if (!contains_case_insensitive(p->jugador1, filtro) &&
                !contains_case_insensitive(p->jugador2, filtro)) {
                mostrar = 0;
            }
        }
        if (mostrar) {
            printf("ID %d: %s (%s)  VS  %s (%s) -> %s\n",
                   p->id, p->jugador1, p->pokemon1, p->jugador2, p->pokemon2, p->resultado);
            printed++;
        }
    }
    if (printed == 0) {
        if (filtro && filtro[0] != '\0')
            printf("No hay partidas para el jugador que contiene: '%s'\n", filtro);
        else
            printf("No hay partidas registradas.\n");
    }
    printf("\n=================================\n");

    free(arr);
}

void historial_free(Historial *h) {
    if (!h || !h->buckets) return;
    for (int b = 0; b < h->bucket_count; ++b) {
        Partida *p = h->buckets[b];
        while (p) {
            Partida *tmp = p;
            p = p->next;
            free(tmp);
        }
    }
    free(h->buckets);
    h->buckets = NULL;
}
