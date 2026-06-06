#include "cliente_socket.h"

#include <iostream>
#include <ws2tcpip.h>

ClienteSocket::ClienteSocket(const std::string& ip_servidor, int puerto)
{
    this->ip_servidor = ip_servidor;
    this->puerto = puerto;
    this->socket_cliente = INVALID_SOCKET;
}

bool ClienteSocket::conectar()
{
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cout << "Error al inicializar Winsock." << std::endl;
        return false;
    }

    socket_cliente = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socket_cliente == INVALID_SOCKET)
    {
        std::cout << "Error al crear el socket del cliente." << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in direccion_servidor;
    direccion_servidor.sin_family = AF_INET;
    direccion_servidor.sin_port = htons(puerto);
    
direccion_servidor.sin_addr.s_addr = inet_addr(ip_servidor.c_str());

if (direccion_servidor.sin_addr.s_addr == INADDR_NONE)
    {
        std::cout << "Direccion IP no valida." << std::endl;
        closesocket(socket_cliente);
        WSACleanup();
        return false;
    }

    if (connect(socket_cliente, (sockaddr*)&direccion_servidor, sizeof(direccion_servidor)) == SOCKET_ERROR)
    {
        std::cout << "No se pudo conectar con el servidor." << std::endl;
        closesocket(socket_cliente);
        WSACleanup();
        return false;
    }

    std::cout << "Conexion establecida con el servidor." << std::endl;
    return true;
}

bool ClienteSocket::enviarMensaje(const std::string& mensaje)
{
    int bytes_enviados = send(socket_cliente, mensaje.c_str(), mensaje.length(), 0);

    if (bytes_enviados == SOCKET_ERROR)
    {
        std::cout << "Error al enviar mensaje al servidor." << std::endl;
        return false;
    }

    return true;
}

std::string ClienteSocket::recibirMensaje()
{
    char buffer[1024];

    int bytes_recibidos = recv(socket_cliente, buffer, sizeof(buffer) - 1, 0);

    if (bytes_recibidos <= 0)
    {
        return "";
    }

    buffer[bytes_recibidos] = '\0';
    return std::string(buffer);
}

void ClienteSocket::cerrarConexion()
{
    if (socket_cliente != INVALID_SOCKET)
    {
        closesocket(socket_cliente);
        socket_cliente = INVALID_SOCKET;
    }

    WSACleanup();
}