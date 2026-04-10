#ifndef BASE_DATOS_H
#define BASE_DATOS_H

#include "sqlite3.h"

sqlite3* db_open();
void db_close(sqlite3* db);

#endif