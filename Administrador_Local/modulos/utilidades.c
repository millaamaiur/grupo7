#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/utilidades.h"

void escribir_log(const char* tipo, const char* mensaje) {
    FILE *archivo = fopen("ficherosTexto/log.txt", "a");
    if (archivo == NULL) {
        fprintf(stderr, "Error al abrir el archivo de log\n");
        return;
    }

    time_t ahora;
    struct tm *tm_info = localtime(&ahora);
    char cadena_tiempo[26];
    strftime(cadena_tiempo, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(archivo, "[%s] [%s] %s\n", cadena_tiempo, tipo, mensaje);
    fclose(archivo);
}