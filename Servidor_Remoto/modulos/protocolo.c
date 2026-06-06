#include "../include/protocolo.h"
#include "../include/login.h"
#include "../include/actividades.h"
#include "../include/taquilla.h"
#include "../include/instalacion.h"
#include "../include/perfil.h"
#include "../include/reservas.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void procesar_comando(sqlite3 *db, char *buffer, char *respuesta) {

    // Limpiar posibles \r\n al final
    buffer[strcspn(buffer, "\r\n")] = '\0';

    // Copiar buffer para no modificar el original
    char copia[1024];
    strncpy(copia, buffer, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char *comando = strtok(copia, ";");
    if (comando == NULL) {
        strcpy(respuesta, "ERROR; Comando vacio");
        return;
    }

    // LOGIN;usuario;password
    if (strcmp(comando, "LOGIN") == 0) {
        char *usuario  = strtok(NULL, ";");
        char *password = strtok(NULL, ";");
        if (usuario == NULL || password == NULL) {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        int id = 0;
        LoginResult resultado = login_db(db, usuario, password, &id);
        if (resultado == LOGIN_ADMIN) {
            sprintf(respuesta, "OK_ADMIN;%d", id);
        } else if (resultado == LOGIN_SOCIO) {
            sprintf(respuesta, "OK_SOCIO;%d", id);
        } else {
            strcpy(respuesta, "ERROR; Credenciales incorrectas");
        }
    }

    // LISTAR_ACTIVIDADES
    else if (strcmp(comando, "LISTAR_ACTIVIDADES") == 0) {
        consultar_actividades_db(db, respuesta);
    }

    // INSCRIBIR_ACTIVIDAD;id_socio;id_actividad
    else if (strcmp(comando, "INSCRIBIR_ACTIVIDAD") == 0) {
        char *s_id_socio     = strtok(NULL, ";");
        char *s_id_actividad = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_actividad == NULL) {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        int id_socio     = atoi(s_id_socio);
        int id_actividad = atoi(s_id_actividad);
        registrarse_actividad_db(db, id_socio, id_actividad, respuesta);
    }

    // CONSULTAR_TAQUILLA;id_socio
    else if (strcmp(comando, "CONSULTAR_TAQUILLA") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        consultar_taquilla_db(db, atoi(s_id), respuesta);
    }

    // ALQUILAR_TAQUILLA;id_socio
    else if (strcmp(comando, "ALQUILAR_TAQUILLA") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        alquilar_taquilla_db(db, atoi(s_id), respuesta);
    }

    // ENTRAR_PISCINA;id_socio
    else if (strcmp(comando, "ENTRAR_PISCINA") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        entrar_piscina_db(db, atoi(s_id), respuesta);
    }

    // VER_PERFIL;id_socio
    else if (strcmp(comando, "VER_PERFIL") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        ver_perfil_db(db, atoi(s_id), respuesta);
    }

    // VER_SUSCRIPCION;id_socio
    else if (strcmp(comando, "VER_SUSCRIPCION") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        ver_suscripcion_db(db, atoi(s_id), respuesta);
    }

    // EDITAR_PERFIL;id_socio;nuevo_usuario;nueva_pass
    else if (strcmp(comando, "EDITAR_PERFIL") == 0) {
        char *s_id          = strtok(NULL, ";");
        char *nuevo_usuario = strtok(NULL, ";");
        char *nueva_pass    = strtok(NULL, ";");
        if (s_id == NULL || nuevo_usuario == NULL || nueva_pass == NULL) {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        editar_perfil_db(db, atoi(s_id), nuevo_usuario, nueva_pass, respuesta);
    }

    // MIS_RESERVAS;id_socio
    else if (strcmp(comando, "MIS_RESERVAS") == 0) {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL) { strcpy(respuesta, "ERROR; Faltan parametros"); return; }
        mis_reservas_db(db, atoi(s_id), respuesta);
    }

    // RESERVAR;id_socio;id_instalacion;fecha;hora_inicio;duracion
    else if (strcmp(comando, "RESERVAR") == 0) {
        char *s_id_socio      = strtok(NULL, ";");
        char *s_id_instalacion = strtok(NULL, ";");
        char *fecha           = strtok(NULL, ";");
        char *hora_inicio     = strtok(NULL, ";");
        char *s_duracion      = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_instalacion == NULL || fecha == NULL ||
            hora_inicio == NULL || s_duracion == NULL) {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        crear_reserva_db(db, atoi(s_id_socio), atoi(s_id_instalacion),
                         fecha, hora_inicio, atoi(s_duracion), respuesta);
    }

    // CANCELAR_RESERVA;id_socio;id_reserva
    else if (strcmp(comando, "CANCELAR_RESERVA") == 0) {
        char *s_id_socio   = strtok(NULL, ";");
        char *s_id_reserva = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_reserva == NULL) {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        cancelar_reserva_db(db, atoi(s_id_socio), atoi(s_id_reserva), respuesta);
    }

    else {
        strcpy(respuesta, "ERROR; Comando desconocido");
    }
}