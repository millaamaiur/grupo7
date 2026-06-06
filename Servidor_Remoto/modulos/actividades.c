#include "../include/actividades.h"

# include <stdio.h>
# include <string.h>

void consultar_actividades_db(sqlite3 *db, char *resultado){
    sqlite3_stmt *stmt;
    const char *sql = "SELECT id_actividad, nombre, dia_semana, hora_inicio, duracion FROM actividades";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(resultado, "ACTIVIDADES_RESP;ERROR;Error al consultar la base de datos");
        return;
    }

    strcpy(resultado, "ACTIVIDADES_RESP;OK");

    // Recorrer las filas
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id_actividad = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        int id_instalacion = sqlite3_column_int(stmt, 2);
        int dia_semana = sqlite3_column_int(stmt, 3);
        const unsigned char *hora_inicio = sqlite3_column_text(stmt, 4);
        int duracion = sqlite3_column_int(stmt, 5);

        char fila[256];
        sprintf(fila, ";[%d,%s,%d,%d,%s,%d min]", id_actividad, nombre, id_instalacion, dia_semana, hora_inicio, duracion);
        
        strcat(resultado, fila);
    }

    sqlite3_finalize(stmt);
}

void registrarse_actividad_db(sqlite3 *db, int id_socio, int id_actividad, char *respuesta) {
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO participantes_actividades (id_soc, id_actividad, fecha_apunte) "
                      "VALUES (?, ?, DATETIME('now', 'localtime'))";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        strcpy(respuesta, "ACTIVIDAD_RESP;ERROR;Error al preparar la inscripcion");
        return;
    }

    if (sqlite3_bind_int(stmt, 1, id_socio) != SQLITE_OK) {
        strcpy(respuesta, "ACTIVIDAD_RESP;ERROR;Error interno");
        sqlite3_finalize(stmt);
        return;
    }
    if (sqlite3_bind_int(stmt, 2, id_actividad) != SQLITE_OK) {
        strcpy(respuesta, "ACTIVIDAD_RESP;ERROR;Error interno");
        sqlite3_finalize(stmt);
        return;
    }

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        strcpy(respuesta, "ACTIVIDAD_RESP;OK;Inscripcion realizada correctamente");
    } else {
        strcpy(respuesta, "ACTIVIDAD_RESP;ERROR;No se pudo realizar la inscripcion");
    }
}