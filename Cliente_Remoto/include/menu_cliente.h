#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

#include <string>
#include "cliente_socket.h"

using namespace std;

class MenuCliente
{
private:
    ClienteSocket* socket;
    string id_socio;

    // Cache
    string cache_perfil;
    bool cache_perfil_valida;

    string cache_suscripcion;
    bool cache_suscripcion_valida;

    string cache_actividades;
    bool cache_actividades_valida;

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
    MenuCliente(ClienteSocket* socket, string id_socio);

    void mostrarMenuSocio();
};

#endif