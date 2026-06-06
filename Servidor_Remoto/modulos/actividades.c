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
        int dia_semana = sqlite3_column_int(stmt, 2);
        const unsigned char *hora_inicio = sqlite3_column_text(stmt, 3);
        int duracion = sqlite3_column_int(stmt, 4);

        char fila[256];
        sprintf(fila, ";[%d,%s,%d,%s,%d min]", id_actividad, nombre, dia_semana, hora_inicio, duracion);
        
        strcat(resultado, fila);
    }

    sqlite3_finalize(stmt);
}

void registrarse_actividad_db(sqlite3 *db, int id_socio, int id_actividad){
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO participantes_actividades (id_soc, id_actividad, fecha_apunte) VALUES (?, ?, DATETIME('now', 'localtime'))";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query de inscripcion\n");
        return 0; 
    }

    if (sqlite3_bind_int(stmt, 1, id_socio) != SQLITE_OK) {
        printf("Error al bindear id_soc\n");
        sqlite3_finalize(stmt);
        return 0;
    }
    if (sqlite3_bind_int(stmt, 2, id_actividad) != SQLITE_OK) {
        printf("Error al bindear id_actividad\n");
        sqlite3_finalize(stmt);
        return 0;
    }

    int resultado = sqlite3_step(stmt);
    
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        return 1; 
    }
    
    printf("Error: No se pudo ejecutar la inscripcion en la BD (Código: %d)\n", resultado);
    return 0;
}