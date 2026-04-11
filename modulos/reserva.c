#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "reserva.h"
#include "base_datos.h"
#include <stdlib.h>

extern sqlite3 *db;

// ============================================================
// CALLBACKS — definidos a nivel global, fuera de toda función
// ============================================================

static int callback_verificar(void *datos_usuario, int num_columnas, char **valores, char **nombres_columnas)
{
    int *contador = (int*)datos_usuario;
    *contador = atoi(valores[0]);
    return 0;
}

static int callback_reservas_activas(void *data, int argc, char **argv, char **azColName)
{
    printf("ID: %s | Socio: %s | Instalacion: %s | Fecha: %s | Hora: %s\n",
           argv[0], argv[1], argv[2], argv[3], argv[4]);
    return 0;
}

static int callback_reservas_socio(void *data, int argc, char **argv, char **azColName)
{
    printf("ID: %s | Instalacion: %s | Fecha: %s | Hora: %s\n",
           argv[0], argv[1], argv[2], argv[3]);
    return 0;
}

static int callback_reservas_instalacion(void *data, int argc, char **argv, char **azColName)
{
    printf("ID: %s | Socio: %s | Fecha: %s | Hora: %s\n",
           argv[0], argv[1], argv[2], argv[3]);
    return 0;
}



void menu_cancelacion_reservas(int id_socio_actual, int es_admin)
{
    int opcion;

    do
    {
        printf("\n--- GESTION DE RESERVAS ---\n");
        printf("1. Cancelar reserva\n");
        printf("2. Consultar reservas activas\n");
        printf("3. Consultar mis reservas\n");
        printf("4. Consultar reservas por instalacion\n");
        printf("5. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion)
        {
        case 1:
            {
                int id_reserva;
                printf("ID de la reserva a cancelar: ");
                scanf("%d", &id_reserva);
                cancelar_reserva(id_reserva, id_socio_actual);
            }
            break;

        case 2:
            if (es_admin) {
                listar_reservas_activas();
            } else {
                printf("Solo el administrador puede ver todas las reservas\n");
            }
            break;

        case 3:
            listar_reservas_por_socio(id_socio_actual);
            break;

        case 4:
            {
                int id_instalacion;
                printf("ID de la instalacion: ");
                scanf("%d", &id_instalacion);
                listar_reservas_por_instalacion(id_instalacion);
            }
            break;

        case 5:
            printf("Volviendo al menu principal\n");
            break;

        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 5);
}



int verificar_disponibilidad(int id_instalacion, char *fecha, char *hora)
{
    char sql[500];
    sprintf(sql, "SELECT COUNT(*) FROM reservas "
                 "WHERE id_instalacion = %d AND fecha = '%s' AND hora_inicio = '%s' AND estado = 'activa'",
                 id_instalacion, fecha, hora);

    int cantidad = 0;
    char *error = NULL;

    sqlite3_exec(db, sql, callback_verificar, &cantidad, &error);

    return (cantidad == 0);
}

int crear_reserva(int id_socio, int id_instalacion, char *fecha, char *hora, int duracion)
{
    if (verificar_disponibilidad(id_instalacion, fecha, hora) == 0) {
        return 0;
    }

    char sql[1000];
    sprintf(sql, "INSERT INTO reservas (id_soc, id_instalacion, fecha, hora_inicio, duracion, estado, fecha_reserva) "
                 "VALUES (%d, %d, '%s', '%s', %d, 'activa', date('now'))",
                 id_socio, id_instalacion, fecha, hora, duracion);

    return db_execute(db, sql);
}

int cancelar_reserva(int id_reserva, int id_socio)
{
    char sql[500];
    sprintf(sql, "UPDATE reservas SET estado = 'cancelada' "
                 "WHERE id_reserva = %d AND id_soc = %d AND estado = 'activa'",
                 id_reserva, id_socio);

    int resultado = db_execute(db, sql);

    if (resultado) {
        printf("Reserva cancelada correctamente\n");
        return 1;
    } else {
        printf("ERROR: No se encontro la reserva\n");
        return 0;
    }
}

int cancelar_reserva_admin(int id_reserva, char *motivo)
{
    char sql[500];
    sprintf(sql, "UPDATE reservas SET estado = 'cancelada', motivo_cancelacion = '%s' "
                 "WHERE id_reserva = %d AND estado = 'activa'",
                 motivo, id_reserva);

    int resultado = db_execute(db, sql);

    if (resultado) {
        printf("Reserva cancelada por: %s\n", motivo);
        return 1;
    } else {
        printf("ERROR: No se encontro la reserva\n");
        return 0;
    }
}

void listar_reservas_activas(void)
{
   char sql[] = "SELECT r.id_reserva, s.user, i.nombre, r.fecha, r.hora_inicio "
             "FROM reservas r "
             "JOIN usuarios s ON r.id_soc = s.id "
             "JOIN instalaciones i ON r.id_instalacion = i.id_instalacion "
             "WHERE r.estado = 'activa'";

    printf("\n=== RESERVAS ACTIVAS ===\n");

    char *error = NULL;
    int rc = sqlite3_exec(db, sql, callback_reservas_activas, NULL, &error);
    if (rc != SQLITE_OK) {
        printf("Error SQL: %s\n", error);
        sqlite3_free(error);
    } else {
        printf("Consulta ejecutada OK\n");
    }
}

void listar_reservas_por_socio(int id_socio)
{
    char sql[500];
    sprintf(sql, "SELECT r.id_reserva, i.nombre, r.fecha, r.hora_inicio "
                 "FROM reservas r "
                 "JOIN instalaciones i ON r.id_instalacion = i.id_instalacion "
                 "WHERE r.id_soc = %d AND r.estado = 'activa'", id_socio);

    printf("\n=== MIS RESERVAS ===\n");

    char *error = NULL;
    sqlite3_exec(db, sql, callback_reservas_socio, NULL, &error);
}

void listar_reservas_por_instalacion(int id_instalacion)
{
    char sql[500];
    sprintf(sql, "SELECT r.id_reserva, s.nombre, r.fecha, r.hora_inicio "
                 "FROM reservas r "
                 "JOIN usuarios s ON r.id_soc = s.id_soc "
                 "WHERE r.id_instalacion = %d AND r.estado = 'activa'", id_instalacion);

    printf("\n=== RESERVAS DE LA INSTALACION ===\n");

    char *error = NULL;
    sqlite3_exec(db, sql, callback_reservas_instalacion, NULL, &error);
}