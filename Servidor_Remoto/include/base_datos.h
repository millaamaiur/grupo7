#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include "sqlite3.h"

sqlite3* db_open(const char* db_path);
void db_close(sqlite3* db);
int db_execute(sqlite3 *db, const char *sql);

#endif