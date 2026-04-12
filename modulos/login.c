#include "../include/login.h"
#include <stddef.h>
#include <stdio.h>    
#include <string.h>

LoginResult login_db(sqlite3 *db, char *user, char *password)
{
    sqlite3_stmt *stmt;
    const char *sql = "SELECT rol FROM usuarios WHERE user = ? AND password = ?";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return LOGIN_ERROR;
    }

    // 2. Bind de parámetros
    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

    // 3. Ejecutar
    int step = sqlite3_step(stmt);

    if (step == SQLITE_ROW) {
        // 4. Leer el rol
        const unsigned char *rol = sqlite3_column_text(stmt, 0);

        LoginResult result;

        if (strcmp((const char *)rol, "admin") == 0) {
            result = LOGIN_ADMIN;
        } 
        else if (strcmp((const char *)rol, "socio") == 0) {
            result = LOGIN_SOCIO;
        } 
        else {
            result = LOGIN_ERROR;
        }

        sqlite3_finalize(stmt);
        return result;
    }

    // No hay usuario
    sqlite3_finalize(stmt);
    return LOGIN_ERROR;
}