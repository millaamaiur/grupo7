#include "../include/reservas.h"
#include <stdio.h>
#include <string.h>

void mis_reservas_db(sqlite3 *db, int id_socio, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "SELECT r.id_reserva, i.nombre, r.fecha, r.hora_inicio, r.duracion, r.estado "
                      "FROM reservas r "
                      "JOIN instalaciones i ON r.id_instalacion = i.id_instalacion "
                      "WHERE r.id_soc = ? AND r.estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "RESERVAS_RESP; ERROR; Error al consultar la base de datos");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);

    strcpy(respuesta, "RESERVAS_RESP;OK");

    int hay_reservas = 0;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hay_reservas = 1;
        int id        = sqlite3_column_int(stmt, 0);
        const char *nombre     = (const char *)sqlite3_column_text(stmt, 1);
        const char *fecha      = (const char *)sqlite3_column_text(stmt, 2);
        const char *hora       = (const char *)sqlite3_column_text(stmt, 3);
        int duracion  = sqlite3_column_int(stmt, 4);
        const char *estado     = (const char *)sqlite3_column_text(stmt, 5);

        char fila[256];
        sprintf(fila, ";[%d;%s;%s;%s;%d;%s]",
                id,
                nombre ? nombre : "N/A",
                fecha ? fecha : "N/A",
                hora ? hora : "N/A",
                duracion,
                estado ? estado : "N/A");
        strcat(respuesta, fila);
    }

    if (!hay_reservas) {
        strcpy(respuesta, "RESERVAS_RESP; ERROR; No tienes reservas activas");
    }

    sqlite3_finalize(stmt);
}

void crear_reserva_db(sqlite3 *db, int id_socio, int id_instalacion, char *fecha, char *hora_inicio, int duracion, char *respuesta) {

    // Verificar disponibilidad
    sqlite3_stmt *stmt_check;
    const char *sql_check = "SELECT COUNT(*) FROM reservas "
                            "WHERE id_instalacion = ? AND fecha = ? "
                            "AND hora_inicio = ? AND estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql_check, -1, &stmt_check, NULL) != SQLITE_OK) {
        strcpy(respuesta, "RESERVA_RESP; ERROR; Error al verificar disponibilidad");
        return;
    }

    sqlite3_bind_int(stmt_check, 1, id_instalacion);
    sqlite3_bind_text(stmt_check, 2, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt_check, 3, hora_inicio, -1, SQLITE_STATIC);

    int ocupada = 0;
    if (sqlite3_step(stmt_check) == SQLITE_ROW) {
        ocupada = sqlite3_column_int(stmt_check, 0);
    }
    sqlite3_finalize(stmt_check);

    if (ocupada > 0) {
        strcpy(respuesta, "RESERVA_RESP; ERROR; La instalacion no esta disponible en ese horario");
        return;
    }

    // Crear la reserva
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO reservas (id_soc, id_instalacion, fecha, hora_inicio, duracion, estado, fecha_reserva) "
                      "VALUES (?, ?, ?, ?, ?, 'activa', date('now'))";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "RESERVA_RESP; ERROR; Error al crear la reserva");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);
    sqlite3_bind_int(stmt, 2, id_instalacion);
    sqlite3_bind_text(stmt, 3, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, hora_inicio, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, duracion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        strcpy(respuesta, "RESERVA_RESP; OK; Reserva creada correctamente");
    } else {
        strcpy(respuesta, "RESERVA_RESP; ERROR; No se pudo crear la reserva");
    }
}

void cancelar_reserva_db(sqlite3 *db, int id_socio, int id_reserva, char *respuesta) {
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE reservas SET estado = 'cancelada' "
                      "WHERE id_reserva = ? AND id_soc = ? AND estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "RESERVA_RESP; ERROR; Error al cancelar la reserva");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_reserva);
    sqlite3_bind_int(stmt, 2, id_socio);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (sqlite3_changes(db) > 0) {
        strcpy(respuesta, "RESERVA_RESP; OK; Reserva cancelada correctamente");
    } else {
        strcpy(respuesta, "RESERVA_RESP; ERROR; No se encontro la reserva o no te pertenece");
    }
}