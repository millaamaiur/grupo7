#ifndef INSTALACION_H_
#define INSTALACION_H_
#include "instalacion.h"
#include <sqlite3.h>

void menu_instalaciones(sqlite3 *db);

void ver_ocupacion_instalaciones(sqlite3 *db);
int alta_instalacion(sqlite3 *db, char* nombre, char* tipo, int aforo_maximo, double precio_hora, char* estado);
void baja_instalacion(sqlite3 *db, int id_instalacion);
void modificar_instalacion(void);
void bloquear_mantenimiento(void);
void consultar_instalaciones(void);

#endif