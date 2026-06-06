#include "../include/taquilla.h"
#include <stdio.h>
#include <string.h>

void consultar_taquilla_db(sqlite3 *db, int id_socio, char *respuesta) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id_taquilla, ubicacion, horario_inicio, fecha_inicio, estado "
                      "FROM taquillas WHERE id_soc = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *ubicacion = (const char *)sqlite3_column_text(stmt, 1);
        const char *horario = (const char *)sqlite3_column_text(stmt, 2);
        const char *fecha = (const char *)sqlite3_column_text(stmt, 3);
        const char *estado = (const char *)sqlite3_column_text(stmt, 4);

        sprintf(respuesta, "TAQUILLA_RESP;OK;%d;%s;%s;%s;%s",
                id, ubicacion, horario, fecha, estado);
    } else {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;No tienes taquilla asignada");
    }

    sqlite3_finalize(stmt);
}

void alquilar_taquilla_db(sqlite3 *db, int id_socio, char *respuesta) {

    // Primero comprobar que el socio no tiene ya una taquilla
    sqlite3_stmt *stmt_check;
    const char *sql_check = "SELECT id_taquilla FROM taquillas WHERE id_soc = ?";

    if (sqlite3_prepare_v2(db, sql_check, -1, &stmt_check, NULL) != SQLITE_OK) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt_check, 1, id_socio);

    if (sqlite3_step(stmt_check) == SQLITE_ROW) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;Ya tienes una taquilla asignada");
        sqlite3_finalize(stmt_check);
        return;
    }
    sqlite3_finalize(stmt_check);

    // Buscar taquilla libre
    sqlite3_stmt *stmt_libre;
    const char *sql_libre = "SELECT id_taquilla FROM taquillas WHERE estado = 'libre' LIMIT 1";

    if (sqlite3_prepare_v2(db, sql_libre, -1, &stmt_libre, NULL) != SQLITE_OK) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;Error al buscar taquilla libre");
        return;
    }

    if (sqlite3_step(stmt_libre) != SQLITE_ROW) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;No hay taquillas libres disponibles");
        sqlite3_finalize(stmt_libre);
        return;
    }

    int id_taquilla = sqlite3_column_int(stmt_libre, 0);
    sqlite3_finalize(stmt_libre);

    // Asignar la taquilla al socio
    sqlite3_stmt *stmt_update;
    const char *sql_update = "UPDATE taquillas SET id_soc = ?, estado = 'ocupada', "
                             "fecha_inicio = date('now') WHERE id_taquilla = ?";

    if (sqlite3_prepare_v2(db, sql_update, -1, &stmt_update, NULL) != SQLITE_OK) {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;Error al asignar taquilla");
        return;
    }

    sqlite3_bind_int(stmt_update, 1, id_socio);
    sqlite3_bind_int(stmt_update, 2, id_taquilla);

    int resultado = sqlite3_step(stmt_update);
    sqlite3_finalize(stmt_update);

    if (resultado == SQLITE_DONE) {
        sprintf(respuesta, "TAQUILLA_RESP;OK;Taquilla %d asignada correctamente", id_taquilla);
    } else {
        strcpy(respuesta, "TAQUILLA_RESP;ERROR;No se pudo asignar la taquilla");
    }
}