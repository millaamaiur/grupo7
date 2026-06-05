#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include "cliente_socket.h"

class MenuCliente
{
private:
    ClienteSocket* socket;
    int id_socio;

    void menuGestionReservas();
    void menuServiciosCentro();
    void menuPerfilConfiguracion();

    void consultarDisponibilidad();
    void realizarReserva();
    void mostrarReservas();
    void cancelarReserva();

    void menuActividades();
    void menuTaquilla();
    void accesoPiscina();

    void consultarActividades();
    void registrarseActividad();

    void consultarTaquilla();
    void alquilarTaquilla();

    void datosPersonales();
    void estadoSuscripcion();

public:
    MenuCliente();
    MenuCliente(ClienteSocket* socket, int id_socio);

    void mostrarMenuSocio();
};

#endif