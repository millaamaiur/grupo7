#ifndef USUARIO_H_
#define USUARIO_H_

#include "sqlite3.h"


void menu_usuarios(sqlite3 *db);
int dar_alta_usuario(sqlite3 *db, char *user, char *password, char *rol, char *fecha_nac);
int dar_baja_usuario(sqlite3 *db, char *usuario);
void mostrar_suscripciones(sqlite3 *db);
int modificar_suscripcion_usuario(sqlite3 *db, const char *user, int id_suscrip);

#endif