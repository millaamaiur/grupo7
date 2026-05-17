#ifndef RESERVA_H
#define RESERVA_H


void menu_cancelacion_reservas(int id_socio_actual, int es_admin);


int verificar_disponibilidad(int id_instalacion, char *fecha, char *hora);
int crear_reserva(int id_socio, int id_instalacion, char *fecha, char *hora, int duracion);
int cancelar_reserva(int id_reserva, int id_socio);
int cancelar_reserva_admin(int id_reserva, char *motivo);
void listar_reservas_activas(void);
void listar_reservas_por_socio(int id_socio);
void listar_reservas_por_instalacion(int id_instalacion);

#endif