#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#include "include/base_datos.h"
#include "include/config.h"
#include "include/protocolo.h"
#include "include/log.h"

#define BUFFER_SIZE 1024

int main(void)
{
    // 1. Config y base de datos
    Config cfg = load_config("config/servidor.conf");
    sqlite3 *db = db_open(cfg.db_path);
    if (db == NULL) {
        printf("Error al abrir la base de datos\n");
        return -1;
    }

    // 2. Inicializar Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Error al inicializar Winsock\n");
        db_close(db);
        return -1;
    }

    // 3. Crear socket
    SOCKET servidor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servidor == INVALID_SOCKET) {
        printf("Error al crear socket\n");
        WSACleanup();
        db_close(db);
        return -1;
    }

    // 4. Bind
    struct sockaddr_in direccion;
    direccion.sin_family = AF_INET;
    direccion.sin_port = htons(cfg.puerto);
    direccion.sin_addr.s_addr = INADDR_ANY;

    if (bind(servidor, (struct sockaddr*)&direccion, sizeof(direccion)) == SOCKET_ERROR) {
        printf("Error en bind\n");
        closesocket(servidor);
        WSACleanup();
        db_close(db);
        return -1;
    }

    // 5. Listen
    listen(servidor, 5); // Para admitir hasta 5 clientes (prueba)
    printf("Servidor escuchando en puerto %d...\n", cfg.puerto);

    guardar_log(cfg.log_path, "INFO", "Servidor escuchando correctamente.");

    // 6. Loop principal
    while (1) {
        SOCKET cliente = accept(servidor, NULL, NULL);
        if (cliente == INVALID_SOCKET) continue;

        guardar_log(cfg.log_path, "INFO", "Cliente conectado");

        printf("Cliente conectado\n");

        char buffer[BUFFER_SIZE];
        int bytes;
        while ((bytes = recv(cliente, buffer, sizeof(buffer) - 1, 0)) > 0) {
            buffer[bytes] = '\0';

            char log_msg[256];
            sprintf(log_msg, "Peticion recibida: %s", buffer);
            guardar_log(cfg.log_path, "INFO", log_msg);

            char respuesta[BUFFER_SIZE];
            procesar_comando(db, buffer, respuesta, cfg.log_path);
            send(cliente, respuesta, strlen(respuesta), 0);

            memset(buffer, 0, BUFFER_SIZE); // limpiar el buffer
        }

        guardar_log(cfg.log_path, "INFO", "Cliente desconectado");
        closesocket(cliente);
    }

    // 7. Limpieza (en la práctica no se llega aquí)
    closesocket(servidor);
    WSACleanup();
    db_close(db);
    return 0;
}