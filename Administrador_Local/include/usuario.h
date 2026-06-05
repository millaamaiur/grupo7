#ifndef USUARIO_H_
#define USUARIO_H_

#include "sqlite3.h"

typedef struct
{
    int id;
    char* user;
    char* password;
    char* rol;
    char* fecha_nac;
    char* fecha_alta;
    int id_suscrip;
}  Usuario;

void menu_usuarios(sqlite3 *db);
int dar_alta_usuario(sqlite3 *db, Usuario u);
int dar_baja_usuario(sqlite3 *db, Usuario u);
void mostrar_suscripciones(sqlite3 *db);
int modificar_suscripcion_usuario(sqlite3 *db, Usuario u);

#endif