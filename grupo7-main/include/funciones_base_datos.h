#ifndef FUNCIONES_BASE_DATOS_H_
#define FUNCIONES_BASE_DATOS_H_

#include <sqlite3.h>

typedef enum
{
    LOGIN_ERROR,
    LOGIN_ADMIN,
    LOGIN_SOCIO
} LoginResult;

LoginResult login_db(sqlite3 *db, char *user, char *password);
#endif