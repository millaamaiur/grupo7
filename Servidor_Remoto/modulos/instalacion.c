#include "../include/instalacion.h"
#include <stdio.h>
#include <string.h>

void entrar_piscina_db(sqlite3 *db, int id_socio, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT i.aforo_maximo, COUNT(r.id_reserva) "
                      "FROM instalaciones i "
                      "LEFT JOIN reservas r ON i.id_instalacion = r.id_instalacion "
                      "AND r.estado = 'activa' AND r.fecha = date('now') "
                      "WHERE i.tipo = 'piscina' "
                      "GROUP BY i.id_instalacion LIMIT 1";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "PISCINA_RESP; ERROR; Error al consultar la base de datos");
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int aforo_maximo = sqlite3_column_int(stmt, 0);
        int ocupacion = sqlite3_column_int(stmt, 1);
        sqlite3_finalize(stmt);

        if (ocupacion < aforo_maximo) {
            sprintf(respuesta, "PISCINA_RESP; OK; Acceso permitido. Ocupacion: %d/%d",
                    ocupacion + 1, aforo_maximo);
        } else {
            sprintf(respuesta, "PISCINA_RESP; ERROR; Aforo completo. Ocupacion: %d/%d",
                    ocupacion, aforo_maximo);
        }
    } else {
        sqlite3_finalize(stmt);
        strcpy(respuesta, "PISCINA_RESP; ERROR; No se encontro la piscina");
    }
}

void listar_instalaciones_db(sqlite3 *db, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT id_instalacion, nombre, tipo, aforo_maximo, precio_hora, estado "
                      "FROM instalaciones WHERE estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "INSTALACIONES_RESP; ERROR; Error al consultar la base de datos");
        return;
    }

    strcpy(respuesta, "INSTALACIONES_RESP; OK");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *nombre = (const char *)sqlite3_column_text(stmt, 1);
        const char *tipo = (const char *)sqlite3_column_text(stmt, 2);
        int aforo = sqlite3_column_int(stmt, 3);
        double precio = sqlite3_column_double(stmt, 4);
        const char *estado = (const char *)sqlite3_column_text(stmt, 5);

        char fila[256];
        sprintf(fila, ";[%d;%s;%s;%d;%.2f;%s]", id, nombre, tipo, aforo, precio, estado);
        strcat(respuesta, fila);
    }

    sqlite3_finalize(stmt);
}

void consultar_disponibilidad_db(sqlite3 *db, int id_instalacion, char *fecha, char *hora_inicio, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT COUNT(*) FROM reservas "
                      "WHERE id_instalacion = ? AND fecha = ? "
                      "AND hora_inicio = ? AND estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "DISPONIBILIDAD_RESP; ERROR; Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_instalacion);
    sqlite3_bind_text(stmt, 2, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hora_inicio, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int ocupada = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        if (ocupada > 0) {
            strcpy(respuesta, "DISPONIBILIDAD_RESP; ERROR; Instalacion no disponible en ese horario");
        } else {
            strcpy(respuesta, "DISPONIBILIDAD_RESP; OK; Instalacion disponible");
        }
    } else {
        sqlite3_finalize(stmt);
        strcpy(respuesta, "DISPONIBILIDAD_RESP; ERROR; Error al consultar");
    }
}