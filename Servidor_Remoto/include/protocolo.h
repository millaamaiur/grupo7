#ifndef PROTOCOLO_H
#define PROTOCOLO_H

#include <sqlite3.h>

void procesar_comando(sqlite3 *db, char *buffer, char *respuesta);

#endif // PROTOCOLO_H