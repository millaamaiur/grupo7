#ifndef PERFIL_H
#define PERFIL_H

#include <sqlite3.h>

void ver_perfil_db(sqlite3 *db, int id_socio, char *respuesta);
void ver_suscripcion_db(sqlite3 *db, int id_socio, char *respuesta);
void editar_perfil_db(sqlite3 *db, int id_socio, char *nuevo_usuario, char *nueva_pass, char *respuesta);

#endif // PERFIL_H