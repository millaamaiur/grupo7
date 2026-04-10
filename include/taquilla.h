#ifndef TAQUILLA_H
#define TAQUILLA_H

void menu_taquillas(int id_socio_actual, int es_admin);

int alquilar_taquilla(int id_socio, int id_taquilla);
int liberar_mi_taquilla(int id_socio);
void ver_taquillas_libres(void);
void ver_mi_taquilla(int id_socio);

void ver_todas_taquillas(void);
int bloquear_taquilla(int id_taquilla);

#endif