#include <iostream>
#include "menu_cliente.h"
#include <string>

using namespace std;

MenuCliente::MenuCliente()
{
    this->socket = nullptr;
    this->id_socio = "";
}

MenuCliente::MenuCliente(ClienteSocket *socket, string id_socio)
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
        cout << "1.- Gestion de reservas" << endl;
        cout << "2.- Servicios del centro" << endl;
        cout << "3.- Perfil y configuracion" << endl;
        cout << "4.- Salir" << endl;
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

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//// CASO 1: GESTION DE RESERVAS ////

// MENU DE RESERVAS
void MenuCliente::menuGestionReservas()
{
    int opcion;

    do
    {
        cout << "\n===== GESTION DE RESERVAS =====" << endl;
        cout << "1. Consultar disponibilidad" << endl;
        cout << "2. Realizar reserva" << endl;
        cout << "3. Mostrar reservas" << endl;
        cout << "4. Cancelar reserva" << endl;
        cout << "5. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            consultarDisponibilidad();
            break;
        case 2:
            realizarReserva();
            break;
        case 3:
            mostrarReservas();
            break;
        case 4:
            cancelarReserva();
            break;
        case 5:
            cout << "Volviendo al menu principal..." << endl;
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 5);
}

void MenuCliente::consultarDisponibilidad()
{
    int id_instalacion;
    string fecha, hora;

    cout << "\n--- CONSULTAR DISPONIBILIDAD ---" << endl;
    cout << "ID instalacion: ";
    cin >> id_instalacion;
    cout << "Fecha (YYYY-MM-DD): ";
    cin >> fecha;
    cout << "Hora inicio (HH:MM): ";
    cin >> hora;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CONSULTAR_DISPONIBILIDAD;" +
                     to_string(id_instalacion) + ";" +
                     fecha + ";" +
                     hora + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}
void MenuCliente::realizarReserva()
{
    int id_instalacion;
    int duracion;
    string fecha, hora;

    cout << "\n--- REALIZAR RESERVA ---" << endl;
    cout << "ID instalacion: ";
    cin >> id_instalacion;
    cout << "Fecha (YYYY-MM-DD): ";
    cin >> fecha;
    cout << "Hora inicio (HH:MM): ";
    cin >> hora;
    cout << "Duracion en minutos: ";
    cin >> duracion;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "REALIZAR_RESERVA;" +
                     id_socio + ";" +
                     to_string(id_instalacion) + "|" +
                     fecha + ";" +
                     hora + ";" +
                     to_string(duracion) + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::mostrarReservas()
{
    cout << "\n--- MIS RESERVAS ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "MOSTRAR_RESERVAS;" + id_socio + "\n";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::cancelarReserva()
{
    int id_reserva;

    cout << "\n--- CANCELAR RESERVA ---" << endl;
    cout << "Introduce el ID de la reserva: ";
    cin >> id_reserva;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CANCELAR_RESERVA;" +
                     id_socio + ";" +
                     to_string(id_reserva) + "\n";

    socket->enviarMensaje(comando);

    
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
<<<<<<< HEAD

}
=======
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//// CASO 2: SERVICIOS DEL CENTRO ////

// MENU DE SERVICIOS DEL CENTRO
void MenuCliente::menuServiciosCentro()
{
    int opcion;

    do
    {
        cout << "\n===== SERVICIOS DEL CENTRO =====" << endl;
        cout << "1. Actividades" << endl;
        cout << "2. Taquilla" << endl;
        cout << "3. Acceso piscina" << endl;
        cout << "4. Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            menuActividades();
            break;

        case 2:
            menuTaquilla();
            break;

        case 3:
            accesoPiscina();
            break;

        case 4:
            cout << "Volviendo al menu de socio..." << endl;
            break;

        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 4);
}

// submenu de actividades
void MenuCliente::menuActividades()
{
    int opcion;

    do
    {
        cout << "\n===== ACTIVIDADES =====" << endl;
        cout << "1.- Consultar actividades disponibles" << endl;
        cout << "2.- Registrarse en una actividad" << endl;
        cout << "3.- Volver" << endl;
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

// opcion -> consultar actividades
void MenuCliente::consultarActividades()
{
    cout << "\n--- CONSULTAR ACTIVIDADES ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    socket->enviarMensaje("LISTAR_ACTIVIDADES");

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

// opcion -> registrarse actividad
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

    string comando = "INSCRIBIR_ACTIVIDAD; " + id_socio + "; " + idActividad + "";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////

// submenu de taquillas
void MenuCliente::menuTaquilla()
{
    int opcion;

    do
    {
        cout << "\n===== GESTION DE TAQUILLA =====" << endl;
        cout << "1.- Consultar taquilla" << endl;
        cout << "2.- Alquilar taquilla" << endl;
        cout << "3.- Volver" << endl;
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

// opcion -> consultar taquillla
void MenuCliente::consultarTaquilla()
{
    cout << "\n--- CONSULTAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CONSULTAR_TAQUILLA; " + id_socio + "";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

// opcion -> alquilar taquilla
void MenuCliente::alquilarTaquilla()
{
    cout << "\n--- ALQUILAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ALQUILAR_TAQUILLA; " + id_socio + "";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////

// SUBMENU DE PISCINA
void MenuCliente::accesoPiscina()
{
    cout << "\n--- ACCESO PISCINA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ENTRAR_PISCINA; " + id_socio + "";

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    cout << respuesta << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//// CASO 3: PERFIL DE CONFIGURACION ////

// MENU DE PERFIL Y CONFIGURACION
void MenuCliente::menuPerfilConfiguracion()
{
    int opcion;
    do
    {
        cout << "\n===== 3. PERFIL Y CONFIGURACION =====" << endl;
        cout << "1.- Consultar mis datos personales" << endl;
        cout << "2.- Editar mis datos personales (Usuario/Contrasena)" << endl;
        cout << "3.- Consultar el estado de mi suscripcion" << endl;
        cout << "4.- Volver" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // Limpieza de filtro por si el usuario introduce letras por error
        if (cin.fail())
        {
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

<<<<<<< HEAD
        case 2:
        {
            if (socket == nullptr)
            {
                cout << "Error: Sin conexion con el servidor." << endl;
                break;
=======
                // Empaquetamos la petición con pipes de forma idéntica a tus otros submétodos
                string comando_editar = "EDITAR_PERFIL; " + to_string(id_socio) + "; " + nuevo_usuario + "; " + nueva_pass + "";
                socket->enviarMensaje(comando_editar);
                
                string respuesta_edit = socket->recibirMensaje();
                cout << respuesta_edit << endl;
>>>>>>> cambiodiseño2
            }

            string nuevo_usuario, nueva_pass;
            cout << "\n--- EDITAR CREDENCIALES DE ACCESO ---" << endl;
            cout << "Introduce el nuevo nombre de usuario: ";
            cin >> nuevo_usuario;
            cout << "Introduce la nueva contrasena (minimo 6 caracteres): ";
            cin >> nueva_pass;

            // Empaquetamos la petición con pipes de forma idéntica a tus otros submétodos
            string comando_editar = "EDITAR_PERFIL;" + id_socio + ";" + nuevo_usuario + ";" + nueva_pass + "\n";
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

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

<<<<<<< HEAD
    string comando_ver = "VER_PERFIL;" + id_socio + "\n";
=======
    string comando_ver = "VER_PERFIL; " + to_string(id_socio) + "";
>>>>>>> cambiodiseño2
    socket->enviarMensaje(comando_ver);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::estadoSuscripcion()
{
    cout << "\n--- CONSULTAR ESTADO DE LA SUSCRIPCION ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

<<<<<<< HEAD
    string comando = "VER_SUSCRIPCION;" + id_socio + "\n";
=======
    string comando = "VER_SUSCRIPCION; " + to_string(id_socio) + "";
>>>>>>> cambiodiseño2
    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}
>>>>>>> origin/main
