#include "../include/perfil.h"
#include <stdio.h>
#include <string.h>

void ver_perfil_db(sqlite3 *db, int id_socio, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT user, rol, fecha_nac, fecha_alta "
                      "FROM usuarios WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "PERFIL_RESP;ERROR;Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *user      = (const char *)sqlite3_column_text(stmt, 0);
        const char *rol       = (const char *)sqlite3_column_text(stmt, 1);
        const char *fecha_nac = (const char *)sqlite3_column_text(stmt, 2);
        const char *fecha_alta = (const char *)sqlite3_column_text(stmt, 3);

        sprintf(respuesta, "PERFIL_RESP;OK;%s;%s;%s;%s",
                user ? user : "N/A",
                rol ? rol : "N/A",
                fecha_nac ? fecha_nac : "N/A",
                fecha_alta ? fecha_alta : "N/A");
    } else {
        strcpy(respuesta, "PERFIL_RESP;ERROR;Usuario no encontrado");
    }

    sqlite3_finalize(stmt);
}

void ver_suscripcion_db(sqlite3 *db, int id_socio, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT s.tipo, s.precio "
                      "FROM suscripciones s "
                      "JOIN usuarios u ON u.id_suscrip = s.id_suscrip "
                      "WHERE u.id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "SUSCRIPCION_RESP;ERROR;Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        const char *tipo = (const char *)sqlite3_column_text(stmt, 0);
        double precio    = sqlite3_column_double(stmt, 1);

        sprintf(respuesta, "SUSCRIPCION_RESP;OK;%s;%.2f",
                tipo ? tipo : "N/A", precio);
    } else {
        strcpy(respuesta, "SUSCRIPCION_RESP;ERROR;No tienes suscripcion asignada");
    }

    sqlite3_finalize(stmt);
}

void editar_perfil_db(sqlite3 *db, int id_socio, char *nuevo_usuario, char *nueva_pass, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE usuarios SET user = ?, password = ? WHERE id = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "PERFIL_RESP;ERROR;Error al actualizar el perfil");
        return;
    }

    sqlite3_bind_text(stmt, 1, nuevo_usuario, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, nueva_pass, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, id_socio);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE && sqlite3_changes(db) > 0) {
        strcpy(respuesta, "PERFIL_RESP;OK;Perfil actualizado correctamente");
    } else {
        strcpy(respuesta, "PERFIL_RESP;ERROR;No se pudo actualizar el perfil");
    }
}