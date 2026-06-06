#ifndef INSTALACION_H
#define INSTALACION_H

#include <sqlite3.h>

void entrar_piscina_db(sqlite3 *db, int id_socio, char *respuesta);
void listar_instalaciones_db(sqlite3 *db, char *respuesta);

#endif // INSTALACIONES_H