#include <iostream>
#include "menu_cliente.h"

using namespace std;

MenuCliente::MenuCliente()
{
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
    cout << "[Pendiente] Se solicitaran las actividades disponibles al servidor." << endl;
}

void MenuCliente::registrarseActividad()
{
    int idActividad;

    cout << "\n--- REGISTRARSE EN ACTIVIDAD ---" << endl;
    cout << "Introduce el ID de la actividad: ";
    cin >> idActividad;

    cout << "[Pendiente] Se enviara al servidor la inscripcion en la actividad "
         << idActividad << "." << endl;
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
    cout << "[Pendiente] Se consultara si el socio tiene una taquilla asignada." << endl;
}

void MenuCliente::alquilarTaquilla()
{
    cout << "\n--- ALQUILAR TAQUILLA ---" << endl;
    cout << "[Pendiente] Se enviara una solicitud de alquiler de taquilla al servidor." << endl;
}

//SUBMENU DE PISCINA
void MenuCliente::accesoPiscina()
{
    cout << "\n--- ACCESO PISCINA ---" << endl;
    cout << "[Pendiente] El servidor comprobara el aforo actual." << endl;
    cout << "[Pendiente] Si hay aforo disponible, se permitira la entrada." << endl;
}