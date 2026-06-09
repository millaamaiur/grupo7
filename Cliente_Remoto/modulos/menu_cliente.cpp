#include <iostream>
#include "../include/menu_cliente.h"
#include <string>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;

MenuCliente::MenuCliente()
{
    this->socket = nullptr;
    this->id_socio = "";
    this->cache_perfil_valida = false;
    this->cache_suscripcion_valida = false;
    this->cache_actividades_valida = false;
}

MenuCliente::MenuCliente(ClienteSocket *socket, string id_socio)
{
    this->socket = socket;
    this->id_socio = id_socio;
    this->cache_perfil_valida = false;
    this->cache_suscripcion_valida = false;
    this->cache_actividades_valida = false;
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
            system("cls");
            menuGestionReservas();
            break;
        case 2:
            system("cls");
            menuServiciosCentro();
            break;
        case 3:
            system("cls");
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

#include <sstream>
#include <vector>
#include <iomanip>

void MenuCliente::consultarDisponibilidad()
{
    cout << "\n=====================================================\n";
    cout << "           INSTALACIONES DISPONIBLES\n";
    cout << "=====================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor.\n";
        return;
    }

    socket->enviarMensaje("LISTAR_INSTALACIONES");

    string respuesta = socket->recibirMensaje();

    if (respuesta.find("INSTALACIONES_RESP") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    cout << "+----+----------------------+------------+\n";
    cout << "| ID | Instalacion          | Estado     |\n";
    cout << "+----+----------------------+------------+\n";

    size_t pos = respuesta.find(";OK;");
    string datos = respuesta.substr(pos + 4);

    while (true)
    {
        size_t inicio = datos.find('[');
        size_t fin = datos.find(']');

        if (inicio == string::npos || fin == string::npos)
            break;

        string instalacion = datos.substr(inicio + 1, fin - inicio - 1);

        vector<string> campos;
        string campo;
        stringstream ss(instalacion);

        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        if (campos.size() >= 3)
        {
            cout << "| "
                 << setw(2)  << left << campos[0] << " | "
                 << setw(20) << left << campos[1] << " | "
                 << setw(10) << left << campos[2] << " |\n";
        }

        datos = datos.substr(fin + 1);
    }

    cout << "+----+----------------------+------------+\n";
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

    string comando = "RESERVAR;" +
                     id_socio + ";" +
                     to_string(id_instalacion) + ";" +
                     fecha + ";" +
                     hora + ";" +
                     to_string(duracion);

    socket->enviarMensaje(comando);
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::mostrarReservas()
{
    cout << "\n=============================================================\n";
    cout << "                     MIS RESERVAS\n";
    cout << "=============================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor.\n";
        return;
    }

    string comando = "MIS_RESERVAS;" + id_socio;

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    if (respuesta.find("RESERVAS_RESP;OK;") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    cout << "+-----+----------------------+------------+--------+----------+----------+\n";
    cout << "| ID  | Instalacion          | Fecha      | Hora   | Duracion | Estado   |\n";
    cout << "+-----+----------------------+------------+--------+----------+----------+\n";

    size_t pos = respuesta.find(";OK;");
    string datos = respuesta.substr(pos + 4);

    size_t inicio = 0;

    while ((inicio = datos.find('[')) != string::npos)
    {
        size_t fin = datos.find(']');

        if (fin == string::npos)
            break;

        string reserva = datos.substr(inicio + 1, fin - inicio - 1);

        vector<string> campos;
        string campo;
        stringstream ss(reserva);

        while (getline(ss, campo, ';'))
        {
            campos.push_back(campo);
        }

        if (campos.size() >= 6)
        {
            cout << "| "
                 << setw(3)  << left << campos[0] << " | "
                 << setw(20) << left << campos[1] << " | "
                 << setw(10) << left << campos[2] << " | "
                 << setw(6)  << left << campos[3] << " | "
                 << setw(8)  << left << campos[4] << " | "
                 << setw(8)  << left << campos[5] << " |\n";
        }

        datos = datos.substr(fin + 1);
    }

    cout << "+-----+----------------------+------------+--------+----------+----------+\n";
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
                     to_string(id_reserva);

    socket->enviarMensaje(comando);
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//// CASO 2: SERVICIOS DEL CENTRO ////

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

void MenuCliente::consultarActividades()
{
    cout << "\n===============================================================\n";
    cout << "                    ACTIVIDADES DISPONIBLES\n";
    cout << "===============================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string respuesta;

    if (cache_actividades_valida)
    {
        respuesta = cache_actividades;
        cout << "[Mostrando datos desde cache]\n\n";
    }
    else
    {
        socket->enviarMensaje("LISTAR_ACTIVIDADES");

        respuesta = socket->recibirMensaje();

        cache_actividades = respuesta;
        cache_actividades_valida = true;
    }

    if (respuesta.find("ACTIVIDADES_RESP") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    cout << "+----+----------------------+-----+------+----------+----------------+\n";
    cout << "| ID | Actividad            | Dia | Hora | Duracion | Participantes  |\n";
    cout << "+----+----------------------+-----+------+----------+----------------+\n";

    size_t pos = respuesta.find(";OK;");

    if (pos == string::npos)
        pos = respuesta.find("; OK;");

    string datos = respuesta.substr(pos + 5);

    while (true)
    {
        size_t inicio = datos.find('[');
        size_t fin = datos.find(']');

        if (inicio == string::npos || fin == string::npos)
            break;

        string actividad = datos.substr(inicio + 1, fin - inicio - 1);

        vector<string> campos;
        string campo;
        stringstream ss(actividad);

        while (getline(ss, campo, ','))
        {
            campos.push_back(campo);
        }

        if (campos.size() >= 6)
        {
            cout << "| "
                 << setw(2)  << left << campos[0] << " | "
                 << setw(20) << left << campos[1] << " | "
                 << setw(3)  << left << campos[2] << " | "
                 << setw(4)  << left << campos[3] << " | "
                 << setw(8)  << left << campos[4] << " | "
                 << setw(14) << left << campos[5] << " |\n";
        }

        datos = datos.substr(fin + 1);
    }

    cout << "+----+----------------------+-----+------+----------+----------------+\n";
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

    string comando = "INSCRIBIR_ACTIVIDAD;" + id_socio + ";" + idActividad;
    socket->enviarMensaje(comando);
    string respuesta = socket->recibirMensaje();

    // Invalidar cache de actividades por si cambio el aforo
    cache_actividades_valida = false;

    cout << respuesta << endl;
}

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

void MenuCliente::consultarTaquilla()
{
    cout << "\n=================================================\n";
    cout << "                 MI TAQUILLA\n";
    cout << "=================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "CONSULTAR_TAQUILLA;" + id_socio;

    socket->enviarMensaje(comando);

    string respuesta = socket->recibirMensaje();

    if (respuesta.find("TAQUILLA_RESP;OK;") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    vector<string> campos;
    string campo;
    stringstream ss(respuesta);

    while (getline(ss, campo, ';'))
    {
        campos.push_back(campo);
    }

    if (campos.size() >= 7)
    {
        cout << "+----------------------+-------------------------+\n";
        cout << "| Campo                | Valor                   |\n";
        cout << "+----------------------+-------------------------+\n";

        cout << "| ID Taquilla          | "
             << setw(23) << left << campos[2] << "|\n";

        cout << "| Ubicacion            | "
             << setw(23) << left << campos[3] << "|\n";

        cout << "| Hora Inicio          | "
             << setw(23) << left << campos[4] << "|\n";

        cout << "| Fecha Inicio         | "
             << setw(23) << left << campos[5] << "|\n";

        cout << "| Estado               | "
             << setw(23) << left << campos[6] << "|\n";

        cout << "+----------------------+-------------------------+\n";
    }
    else
    {
        cout << "No se pudo interpretar la informacion de la taquilla.\n";
    }
}

void MenuCliente::alquilarTaquilla()
{
    cout << "\n--- ALQUILAR TAQUILLA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ALQUILAR_TAQUILLA;" + id_socio;
    socket->enviarMensaje(comando);
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

void MenuCliente::accesoPiscina()
{
    cout << "\n--- ACCESO PISCINA ---" << endl;

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor." << endl;
        return;
    }

    string comando = "ENTRAR_PISCINA;" + id_socio;
    socket->enviarMensaje(comando);
    string respuesta = socket->recibirMensaje();
    cout << respuesta << endl;
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////

//// CASO 3: PERFIL DE CONFIGURACION ////

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

        case 2:
        {
            if (socket == nullptr)
            {
                cout << "Error: Sin conexion con el servidor." << endl;
                break;
            }

            string nuevo_usuario, nueva_pass;
            cout << "\n--- EDITAR CREDENCIALES DE ACCESO ---" << endl;
            cout << "Introduce el nuevo nombre de usuario: ";
            cin >> nuevo_usuario;
            cout << "Introduce la nueva contrasena (minimo 6 caracteres): ";
            cin >> nueva_pass;

            string comando_editar = "EDITAR_PERFIL;" + id_socio + ";" + nuevo_usuario + ";" + nueva_pass;
            socket->enviarMensaje(comando_editar);
            string respuesta_edit = socket->recibirMensaje();
            cout << respuesta_edit << endl;

            // Invalidar cache de perfil porque los datos han cambiado
            cache_perfil_valida = false;
            break;
        }

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
    cout << "\n=================================================\n";
    cout << "              MIS DATOS PERSONALES\n";
    cout << "=================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor.\n";
        return;
    }

    string respuesta;

    if (cache_perfil_valida)
    {
        respuesta = cache_perfil;
    }
    else
    {
        string comando_ver = "VER_PERFIL;" + id_socio;
        socket->enviarMensaje(comando_ver);

        respuesta = socket->recibirMensaje();

        cache_perfil = respuesta;
        cache_perfil_valida = true;
    }

    if (respuesta.find("PERFIL_RESP") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    vector<string> campos;
    string campo;
    stringstream ss(respuesta);

    while (getline(ss, campo, ';'))
    {
        campos.push_back(campo);
    }

    if (campos.size() >= 6)
    {
        cout << "+----------------------+----------------------+\n";
        cout << "| Campo                | Valor                |\n";
        cout << "+----------------------+----------------------+\n";
        cout << "| Usuario              | " << setw(20) << left << campos[2] << " |\n";
        cout << "| Rol                  | " << setw(20) << left << campos[3] << " |\n";
        cout << "| Fecha nacimiento     | " << setw(20) << left << campos[4] << " |\n";
        cout << "| Fecha alta           | " << setw(20) << left << campos[5] << " |\n";
        cout << "+----------------------+----------------------+\n";
    }
}
void MenuCliente::estadoSuscripcion()
{
    cout << "\n=================================================\n";
    cout << "            ESTADO DE MI SUSCRIPCION\n";
    cout << "=================================================\n";

    if (socket == nullptr)
    {
        cout << "No hay conexion con el servidor.\n";
        return;
    }

    string respuesta;

    if (cache_suscripcion_valida)
    {
        respuesta = cache_suscripcion;
    }
    else
    {
        string comando = "VER_SUSCRIPCION;" + id_socio;
        socket->enviarMensaje(comando);

        respuesta = socket->recibirMensaje();

        cache_suscripcion = respuesta;
        cache_suscripcion_valida = true;
    }

    if (respuesta.find("SUSCRIPCION_RESP") == string::npos)
    {
        cout << respuesta << endl;
        return;
    }

    vector<string> campos;
    string campo;
    stringstream ss(respuesta);

    while (getline(ss, campo, ';'))
    {
        campos.push_back(campo);
    }

    if (campos.size() >= 4)
    {
        cout << "+----------------------+----------------------+\n";
        cout << "| Campo                | Valor                |\n";
        cout << "+----------------------+----------------------+\n";
        cout << "| Tipo suscripcion     | " << setw(20) << left << campos[2] << " |\n";
        cout << "| Precio mensual       | " << setw(17) << left << campos[3] << " EUR |\n";
        cout << "+----------------------+----------------------+\n";
    }
}