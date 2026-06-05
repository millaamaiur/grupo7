#ifndef CLIENTE_SOCKET_H
#define CLIENTE_SOCKET_H

#include <string>
#include <winsock2.h>

class ClienteSocket
{
private:
    SOCKET socket_cliente;
    std::string ip_servidor;
    int puerto;

public:
    ClienteSocket(const std::string& ip_servidor, int puerto);

    bool conectar();
    bool enviarMensaje(const std::string& mensaje);
    std::string recibirMensaje();
    void cerrarConexion();
};

#endif