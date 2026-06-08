#ifndef INSTALACION_H_
#define INSTALACION_H_

#include <sqlite3.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int id_instalacion;
    char *nombre;
    char *tipo;
    int aforo_maximo;
    double precio_hora;
    char *estado;
} Instalacion;

void menu_instalaciones(sqlite3 *db);
void ver_ocupacion_instalaciones(sqlite3 *db);
int alta_instalacion(sqlite3 *db, Instalacion i);
int baja_instalacion(sqlite3 *db, int id_instalacion);
int modificar_instalacion(sqlite3 *db, Instalacion i);
int bloquear_mantenimiento(sqlite3 *db, int id_instalacion);
void consultar_instalaciones(sqlite3 *db);

#endif