#ifndef TAQUILLA_H
#define TAQUILLA_H

#include <sqlite3.h>

void consultar_taquilla_db(sqlite3 *db, int id_socio, char *respuesta);
void alquilar_taquilla_db(sqlite3 *db, int id_socio, char *respuesta);

#endif // TAQUILLA_H