#include <stdio.h>
#include "base_datos.h"


sqlite3 *db = NULL;

sqlite3* db_open() {
    int result = sqlite3_open("database/database.db", &db);

    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return NULL;
    }

    printf("Base de datos abierta\n");
    return db;
}

void db_close(sqlite3* db) {
    int result = sqlite3_close(db);

    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
    } else {
        printf("Database closed\n");
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