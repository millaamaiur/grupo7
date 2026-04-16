#ifndef INSTALACION_H_
#define INSTALACION_H_
#include <sqlite3.h>

void menu_instalaciones(sqlite3 *db);

void ver_ocupacion_instalaciones(sqlite3 *db);
int alta_instalacion(sqlite3 *db, char* nombre, char* tipo, int aforo_maximo, double precio_hora, char* estado);
int baja_instalacion(sqlite3 *db, int id_instalacion);
int modificar_instalacion(sqlite3 *db, int id_instalacion, char* nombre, char* tipo, int aforo_maximo, double precio_hora, char* estado);
int bloquear_mantenimiento(sqlite3 *db, int id_instalacion);
void consultar_instalaciones(sqlite3 *db);

#endif