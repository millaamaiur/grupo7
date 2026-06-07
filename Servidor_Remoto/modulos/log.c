#include "../include/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void guardar_log(const char *ruta_log, const char *tipo, const char *mensaje) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char timestamp[26];
    strftime(timestamp, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    // Pintar en consola
    printf("[%s] [%s] %s\n", timestamp, tipo, mensaje);

    // Usar la ruta de la configuración
    FILE *fichero = fopen(ruta_log, "a"); 
    if (fichero != NULL) {
        fprintf(fichero, "[%s] [%s] %s\n", timestamp, tipo, mensaje);
        fclose(fichero);
    }
}