#ifndef MENU_CLIENTE_H
#define MENU_CLIENTE_H

class MenuCliente
{
private:

    //Opcion 1
    void consultarDisponibilidad();
    void realizarReserva();
    void mostrarReservas();
    void cancelarReserva();

    //Opcion 2
    void menuActividades();
    void menuTaquilla();
    void accesoPiscina();

    //Opcion 3
    void datosPersonales();
    void estadoSuscripcion();

    //Opcion 4 -> Salir

    void consultarActividades();
    void registrarseActividad();

    void consultarTaquilla();
    void alquilarTaquilla();

    void menuGestionReservas();
    void menuServiciosCentro();
    void menuPerfilConfiguracion();

public:
    MenuCliente();

    void mostrarMenuSocio();
};

#endif