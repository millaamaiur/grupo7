#include "../include/login.h"
#include <stddef.h>
#include <stdio.h>    
#include <string.h>

LoginResult login_db(sqlite3 *db, char *user, char *password, int *id_usuario)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id, rol FROM usuarios WHERE user = ? AND password = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return LOGIN_ERROR;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    

    int step = sqlite3_step(stmt);

    if (step == SQLITE_ROW) {
        
        *id_usuario = sqlite3_column_int(stmt, 0);

        const unsigned char *rol = sqlite3_column_text(stmt, 1);

        LoginResult result;

        if (rol == NULL) {
            result = LOGIN_ERROR;
        } else if (strcmp((const char *)rol, "admin") == 0) {
            result = LOGIN_ADMIN;
        } else if (strcmp((const char *)rol, "socio") == 0) {
            result = LOGIN_SOCIO;
        } else {
            result = LOGIN_ERROR;
        }

        sqlite3_finalize(stmt);
        return result;
    }

    sqlite3_finalize(stmt);
    return LOGIN_ERROR;
}