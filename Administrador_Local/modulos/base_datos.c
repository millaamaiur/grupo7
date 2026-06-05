#include <stdio.h>
#include "../include/base_datos.h"
#include "../include/config.h"

sqlite3* db_open(const char* db_path) {
    sqlite3 *db = NULL;
    int result = sqlite3_open(db_path, &db);

    if (result != SQLITE_OK) {
        printf("Error al abrir la base de datos\n");
        return NULL;
    }

    printf("Base de datos abierta\n");
    return db;
}

void db_close(sqlite3* db) {
    int result = sqlite3_close(db);

    if (result != SQLITE_OK) {
        printf("Error al cerrar la base de datos\n");
        printf("%s\n", sqlite3_errmsg(db));
    } else {
        printf("Base de datos cerrada\n");
    }
}

// Ejecutar SQL sin retorno de datos (INSERT, UPDATE, DELETE)
int db_execute(sqlite3 *db, const char *sql)
{
    char *error = NULL;
    int result = sqlite3_exec(db, sql, NULL, NULL, &error);

    if (result != SQLITE_OK) {
        printf("Error SQL: %s\n", error);
        sqlite3_free(error);
        return 0;
    }

    return 1;
}