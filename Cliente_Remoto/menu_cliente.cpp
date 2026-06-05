#include <iostream>
#include "menu_cliente.h"

using namespace std;

MenuCliente::MenuCliente()
{
    this->socket = nullptr;
    this->id_socio = -1;
}

MenuCliente::MenuCliente(ClienteSocket* socket, int id_socio)
{
    this->socket = socket;
    this->id_socio = id_socio;
}

void MenuCliente::mostrarMenuSocio()
{
    int opcion;

    do
    {
        cout << "\n===== MENU SOCIO =====" << endl;
        cout << "1. Gestion de reservas" << endl;
        cout << "2. Servicios del centro" << endl;
        cout << "3. Perfil y configuracion" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuGestionReservas();
            break;
        case 2:
            menuServiciosCentro();
            break;
        case 3:
            menuPerfilConfiguracion();
            break;
        case 4:
            cout << "Cerrando sesion del socio..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 4);
}

//SUBMENU DE ACTIVIDADES
void MenuCliente::menuActividades()
{
    int opcion;

    do
    {
        cout << "\n===== ACTIVIDADES =====" << endl;
        cout << "1. Consultar actividades disponibles" << endl;
        cout << "2. Registrarse en una actividad" << endl;
        cout << "3. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            consultarActividades();
            break;

        case 2:
            registrarseActividad();
            break;

        case 3:
            cout << "Volviendo a servicios del centro..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 3);
}

void MenuCliente::consultarActividades()
{
    cout << "\n--- CONSULTAR ACTIVIDADES ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    socket->enviarMensaje("LISTAR_ACTIVIDADES\n");

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

void MenuCliente::registrarseActividad()
{
    int id_actividad;

    cout << "\n--- REGISTRARSE EN ACTIVIDAD ---" << endl;
    cout << "Introduce el ID de la actividad: ";
    cin >> id_actividad;

    if (socket == nullptr)
    {
        cout << "[Pendiente] No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "INSCRIBIR_ACTIVIDAD|" +
                     to_string(id_socio) + "|" +
                     to_string(id_actividad) + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}


//SUBMENU DE TAQUILLAS
void MenuCliente::menuTaquilla()
{
    int opcion;

    do
    {
        cout << "\n===== GESTION DE TAQUILLA =====" << endl;
        cout << "1. Consultar taquilla" << endl;
        cout << "2. Alquilar taquilla" << endl;
        cout << "3. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            consultarTaquilla();
            break;

        case 2:
            alquilarTaquilla();
            break;

        case 3:
            cout << "Volviendo a servicios del centro..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 3);
}

void MenuCliente::consultarTaquilla()
{
    cout << "\n--- CONSULTAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "[Pendiente] No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CONSULTAR_TAQUILLA|" + to_string(id_socio) + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

void MenuCliente::alquilarTaquilla()
{
    cout << "\n--- ALQUILAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "[Pendiente] No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ALQUILAR_TAQUILLA|" + to_string(id_socio) + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

//SUBMENU DE PISCINA
void MenuCliente::accesoPiscina()
{
    cout << "\n--- ACCESO PISCINA ---" << endl;

    if (socket == nullptr)
    {
        cout << "[Pendiente] No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ENTRAR_PISCINA|" + to_string(id_socio) + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}