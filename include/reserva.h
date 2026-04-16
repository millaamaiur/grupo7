#ifndef RESERVA_H
#define RESERVA_H

#include <sqlite3.h>


void menu_cancelacion_reservas(sqlite3* db,int id_socio_actual, int es_admin);

int verificar_disponibilidad(sqlite3 *db, int id_instalacion, char *fecha, char *hora);
int crear_reserva(sqlite3 *db, int id_socio, int id_instalacion, char *fecha, char *hora, int duracion);
int cancelar_reserva(sqlite3 *db, int id_reserva, int id_socio);
int cancelar_reserva_admin(sqlite3 *db, int id_reserva, char *motivo);
void listar_reservas_activas(sqlite3 *db);
void listar_reservas_por_socio(sqlite3 *db, int id_socio);
void listar_reservas_por_instalacion(sqlite3 *db, int id_instalacion);

#endif