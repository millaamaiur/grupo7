#ifndef INSTALACION_H_
#define INSTALACION_H_
#include "instalacion.h"
#include <sqlite3.h>

void menu_instalaciones(sqlite3 *db);

void ver_ocupacion_instalaciones(sqlite3 *db);
void alta_instalacion(void);
void baja_instalacion(void);
void modificar_instalacion(void);
void bloquear_mantenimiento(void);
void consultar_instalaciones(void);

#endif