#ifndef RESERVAS_H
#define RESERVAS_H

#include <sqlite3.h>

void mis_reservas_db(sqlite3 *db, int id_socio, char *respuesta);
void crear_reserva_db(sqlite3 *db, int id_socio, int id_instalacion, char *fecha, char *hora_inicio, int duracion, char *respuesta);
void cancelar_reserva_db(sqlite3 *db, int id_socio, int id_reserva, char *respuesta);

#endif // RESERVAS_H