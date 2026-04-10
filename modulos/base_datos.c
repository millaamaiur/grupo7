#include <stdio.h>
#include <string.h>
#include "sqlite3.h"



int main(void){
    sqlite3 *db;

    // Abrir base de datos
	int result = sqlite3_open("test.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
		return result;
	}
    printf("Base de datos abierta");

    // Cerrar base de datos
    result = sqlite3_close(db);
    if (result != SQLITE_OK) {
        printf("Error closing database\n");
        printf("%s\n", sqlite3_errmsg(db));
        return result;
    }
    printf("Database closed\n");
        return 0;
}