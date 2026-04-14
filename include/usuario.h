#ifndef USUARIO_H_
#define USUARIO_H_

#include "sqlite3.h"
void menu_usuarios(sqlite3 *db);
int dar_alta_usuario(sqlite3 *db, char *user, char *password, char *rol, char *fecha_nac);
int dar_baja_usuario(sqlite3 *db, char *usuario);

#endif