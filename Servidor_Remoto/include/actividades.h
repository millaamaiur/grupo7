#ifndef ACTIVIDADES_H
#define ACTIVIDADES_H

#include <sqlite3.h>

void consultar_actividades_db(sqlite3 *db, char *resultado);

void registrarse_actividad_db(sqlite3 *db, int id_socio, int id_actividad, char *respuesta);

#endif