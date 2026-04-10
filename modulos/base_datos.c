#include <stdio.h>
#include "base_datos.h"

sqlite3* db_open() {
    sqlite3 *db;
    int result = sqlite3_open("test.sqlite", &db);

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