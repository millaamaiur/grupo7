#include <iostream>
#include "menu_cliente.h"

using namespace std;

MenuCliente::MenuCliente()
{
    this->socket = nullptr;
    this->id_socio = "";
}

MenuCliente::MenuCliente(ClienteSocket* socket, string id_socio)
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
    string idActividad;

    cout << "\n--- REGISTRARSE EN ACTIVIDAD ---" << endl;
    cout << "Introduce el ID de la actividad: ";
    cin >> idActividad;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "INSCRIBIR_ACTIVIDAD;" + id_socio + ";" + idActividad + "\n";

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
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CONSULTAR_TAQUILLA;" + id_socio + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

void MenuCliente::alquilarTaquilla()
{
    cout << "\n--- ALQUILAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ALQUILAR_TAQUILLA;" + id_socio + "\n";

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
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ENTRAR_PISCINA;" + id_socio + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

//Perfil y configuracion
void MenuCliente::menuPerfilConfiguracion()
{
    int opcion;
    do
    {
        cout << "\n===== 3. PERFIL Y CONFIGURACION =====" << endl;
        cout << "1. Consultar mis datos personales" << endl;
        cout << "2. Editar mis datos personales (Usuario/Contrasena)" << endl;
        cout << "3. Consultar el estado de mi suscripcion" << endl;
        cout << "4. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Limpieza de filtro por si el usuario introduce letras por error
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Por favor, introduce un numero valido." << endl;
            continue;
        }

        switch (opcion)
        {
        case 1:
            datosPersonales(); 
            break;
            
        case 2:
            {
                if (socket == nullptr) {
                    cout << "Error: Sin conexion con el servidor." << endl;
                    break;
                }
                
                string nuevo_usuario, nueva_pass;
                cout << "\n--- EDITAR CREDENCIALES DE ACCESO ---" << endl;
                cout << "Introduce el nuevo nombre de usuario: ";
                cin >> nuevo_usuario;
                cout << "Introduce la nueva contrasena (minimo 6 caracteres): ";
                cin >> nueva_pass;

                // Empaquetamos la petición con pipes de forma idéntica a tus otros submétodos
                string comando_editar = "EDITAR_PERFIL|" + to_string(id_socio) + "|" + nuevo_usuario + "|" + nueva_pass + "\n";
                socket->enviarMensaje(comando_editar);
                
                string respuesta_edit = socket->recibirMensaje();
                cout << respuesta_edit << endl;
            }
            break;
            
        case 3:
            estadoSuscripcion();
            break;
            
        case 4:
            cout << "Volviendo al menu principal..." << endl;
            break;
            
        default:
            cout << "Opcion no valida." << endl;
            break;
        }
    } while (opcion != 4);
}

void MenuCliente::datosPersonales()
{
    cout << "\n--- CONSULTAR DATOS PERSONALES ---" << endl;

    if (socket == nullptr) {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando_ver = "VER_PERFIL|" + to_string(id_socio) + "\n";
    socket->enviarMensaje(comando_ver);
    
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::estadoSuscripcion()
{
    cout << "\n--- CONSULTAR ESTADO DE LA SUSCRIPCION ---" << endl;

    if (socket == nullptr) {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "VER_SUSCRIPCION|" + to_string(id_socio) + "\n";
    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}