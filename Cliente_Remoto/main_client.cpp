#include <iostream>
#include <string>

#include "include/menu_cliente.h"
#include "include/cliente_socket.h"

using namespace std;

int main(void)
{

    // Crear socket del cliente
    // pongo ip y puerto local
    ClienteSocket socket("127.0.0.1", 8080);

    // Conectarse al servidor
    // Usamos metodo de la clase cliente_socket
    if (!socket.conectar())
    {
        cout << "ERROR: No se pudo conectar con el servidor" << endl;
        return 1; // terminar programa
    }

    // Variables del usuario
    string usuario;
    string password;

    // Pedir por pantalla
    cout << "===== LOGIN CLIENTE =====" << endl;

    cout << "Usuario: ";
    cin >> usuario;

    cout << "Password: ";
    cin >> password;

    // Crear el comando
    // esto se envia al server
    string comando = "LOGIN;" + usuario + ";" + password;

    // Enviar comando al server
    socket.enviarMensaje(comando);

    // Prepara variable para la respuesta del server
    string respuesta = socket.recibirMensaje();

    // Comprobar si el server no responde
    if (respuesta.empty())
    {
        cout << "ERROR: El servidor no ha enviado respuesta." << endl;
        socket.cerrarConexion();
        return 1;
    }

    // Mostrar el mensaje que nos envia el server
    // ESTO SE PUEDE QUITAR, PERO PUEDE AYUDAR A VER QUE NOS ENVIA EN CASO DE ERROR
    cout << "Respuesta del servidor: " << respuesta << endl;

    // Si la respuesta es OK_SOCIO
    // pillamos los primero 8 caracteres de la respuesta
    if (respuesta.substr(0, 8) == "OK_SOCIO")
    {
        string idTexto = respuesta.substr(9);

        cout << "Login correcto como socio. ID: " << idTexto << endl;

        MenuCliente menu(&socket, idTexto);
        menu.mostrarMenuSocio();
    }
    else if (respuesta.substr(0, 8) == "OK_ADMIN")
    {
        cout << "Este cliente es solo para socios." << endl;
        cout << "Para acceder como administrador, utilice el programa de administracion local." << endl;
    }
    else if (respuesta.substr(0, 5) == "ERROR")
    {
        cout << "Credenciales incorrectas." << endl;
    }
    else
    {
        cout << "Respuesta desconocida del servidor." << endl;
    }

    socket.cerrarConexion();
    return 0;
}