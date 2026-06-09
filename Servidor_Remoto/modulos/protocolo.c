#include "../include/protocolo.h"
#include "../include/login.h"
#include "../include/actividades.h"
#include "../include/taquilla.h"
#include "../include/instalacion.h"
#include "../include/perfil.h"
#include "../include/reservas.h"
#include "../include/log.h"
#include "../include/config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void procesar_comando(sqlite3 *db, char *buffer, char *respuesta, const char *ruta_log)
{

    // Limpiar posibles \r\n al final
    buffer[strcspn(buffer, "\r\n")] = '\0';

    // Copiar buffer para no modificar el original
    char copia[1024];
    strncpy(copia, buffer, sizeof(copia) - 1);
    copia[sizeof(copia) - 1] = '\0';

    char *comando = strtok(copia, ";");
    if (comando == NULL)
    {
        guardar_log(ruta_log, "WARN", "Se recibio un intento de comando vacio.");
        strcpy(respuesta, "ERROR; Comando vacio");
        return;
    }

    // LOGIN;usuario;password
    if (strcmp(comando, "LOGIN") == 0)
    {
        char *usuario = strtok(NULL, ";");
        char *password = strtok(NULL, ";");
        if (usuario == NULL || password == NULL)
        {
            guardar_log(ruta_log, "WARN", "Intento de LOGIN fallido: faltan parametros.");
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        int id = 0;
        LoginResult resultado = login_db(db, usuario, password, &id);
        if (resultado == LOGIN_ADMIN)
        {
            char log_msg[128];
            sprintf(log_msg, "LOGIN EXITOSO: Administrador ID %d autenticado.", id);
            guardar_log(ruta_log, "INFO", log_msg);
            sprintf(respuesta, "OK_ADMIN;%d", id);
        }
        else if (resultado == LOGIN_SOCIO)
        {
            char log_msg[128];
            sprintf(log_msg, "LOGIN EXITOSO: Socio ID %d autenticado.", id);
            guardar_log(ruta_log, "INFO", log_msg);
            sprintf(respuesta, "OK_SOCIO;%d", id);
        }
        else
        {
            char log_msg[128];
            sprintf(log_msg, "Intento de LOGIN denegado para usuario: '%s'.", usuario);
            guardar_log(ruta_log, "WARN", log_msg);
            strcpy(respuesta, "ERROR; Credenciales incorrectas");
        }
    }

    // LISTAR_ACTIVIDADES
    else if (strcmp(comando, "LISTAR_ACTIVIDADES") == 0)
    {
        consultar_actividades_db(db, respuesta);
    }

    // LISTAR_INSTALACIONES
    else if (strcmp(comando, "LISTAR_INSTALACIONES") == 0)
    {
        listar_instalaciones_db(db, respuesta);
    }

    // INSCRIBIR_ACTIVIDAD;id_socio;id_actividad
    else if (strcmp(comando, "INSCRIBIR_ACTIVIDAD") == 0)
    {
        char *s_id_socio = strtok(NULL, ";");
        char *s_id_actividad = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_actividad == NULL)
        {
            guardar_log(ruta_log, "WARN", "Fallo al inscribir actividad: faltan parametros.");
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        int id_socio = atoi(s_id_socio);
        int id_actividad = atoi(s_id_actividad);
        registrarse_actividad_db(db, id_socio, id_actividad, respuesta);
    }

    // CONSULTAR_TAQUILLA;id_socio
    else if (strcmp(comando, "CONSULTAR_TAQUILLA") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        consultar_taquilla_db(db, atoi(s_id), respuesta);
    }

    // ALQUILAR_TAQUILLA;id_socio
    else if (strcmp(comando, "ALQUILAR_TAQUILLA") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        alquilar_taquilla_db(db, atoi(s_id), respuesta);
    }

    // ENTRAR_PISCINA;id_socio
    else if (strcmp(comando, "ENTRAR_PISCINA") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        entrar_piscina_db(db, atoi(s_id), respuesta);
    }

    // VER_PERFIL;id_socio
    else if (strcmp(comando, "VER_PERFIL") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        ver_perfil_db(db, atoi(s_id), respuesta);
    }

    // VER_SUSCRIPCION;id_socio
    else if (strcmp(comando, "VER_SUSCRIPCION") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        ver_suscripcion_db(db, atoi(s_id), respuesta);
    }

    // EDITAR_PERFIL;id_socio;nuevo_usuario;nueva_pass
    else if (strcmp(comando, "EDITAR_PERFIL") == 0)
    {
        char *s_id = strtok(NULL, ";");
        char *nuevo_usuario = strtok(NULL, ";");
        char *nueva_pass = strtok(NULL, ";");
        if (s_id == NULL || nuevo_usuario == NULL || nueva_pass == NULL)
        {
            guardar_log(ruta_log, "WARN", "Editar perfil: faltan parametros.");
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        editar_perfil_db(db, atoi(s_id), nuevo_usuario, nueva_pass, respuesta);
    }

    // MIS_RESERVAS;id_socio
    else if (strcmp(comando, "MIS_RESERVAS") == 0)
    {
        char *s_id = strtok(NULL, ";");
        if (s_id == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        mis_reservas_db(db, atoi(s_id), respuesta);
    }

    // RESERVAR;id_socio;id_instalacion;fecha;hora_inicio;duracion
    else if (strcmp(comando, "RESERVAR") == 0)
    {
        char *s_id_socio = strtok(NULL, ";");
        char *s_id_instalacion = strtok(NULL, ";");
        char *fecha = strtok(NULL, ";");
        char *hora_inicio = strtok(NULL, ";");
        char *s_duracion = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_instalacion == NULL || fecha == NULL ||
            hora_inicio == NULL || s_duracion == NULL)
        {
            guardar_log(ruta_log, "WARN", "Crear reserva: faltan parametros.");
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        crear_reserva_db(db, atoi(s_id_socio), atoi(s_id_instalacion),
                         fecha, hora_inicio, atoi(s_duracion), respuesta);
    }

    // CANCELAR_RESERVA;id_socio;id_reserva
    else if (strcmp(comando, "CANCELAR_RESERVA") == 0)
    {
        char *s_id_socio = strtok(NULL, ";");
        char *s_id_reserva = strtok(NULL, ";");
        if (s_id_socio == NULL || s_id_reserva == NULL)
        {
            guardar_log(ruta_log, "WARN", "Cancelar reserva: faltan parametros.");
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        cancelar_reserva_db(db, atoi(s_id_socio), atoi(s_id_reserva), respuesta);
    }

    // CONSULTAR_DISPONIBILIDAD;id_instalacion;fecha;hora_inicio
    else if (strcmp(comando, "CONSULTAR_DISPONIBILIDAD") == 0)
    {
        char *s_id = strtok(NULL, ";");
        char *fecha = strtok(NULL, ";");
        char *hora_inicio = strtok(NULL, ";");
        if (s_id == NULL || fecha == NULL || hora_inicio == NULL)
        {
            strcpy(respuesta, "ERROR; Faltan parametros");
            return;
        }
        consultar_disponibilidad_db(db, atoi(s_id), fecha, hora_inicio, respuesta);
    }

    else
    {
        char error_log[256];
        sprintf(error_log, "ALERTA: Comando desconocido intentado por red: '%s'", comando);
        guardar_log(ruta_log, "WARN", error_log);
        strcpy(respuesta, "ERROR; Comando desconocido");
    }
}