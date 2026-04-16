#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include "reserva.h"
#include "base_datos.h"
#include <stdlib.h>


void menu_cancelacion_reservas(sqlite3* db, int id_socio_actual, int es_admin)
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
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcion)
        {
        case 1:
        {
            int id_reserva;
            printf("ID de la reserva a cancelar: ");
            scanf("%d", &id_reserva);
            cancelar_reserva(db, id_reserva, id_socio_actual);
        }
        break;

        case 2:
            if (es_admin)
            {
                listar_reservas_activas(db);
            }
            else
            {
                printf("Solo el administrador puede ver todas las reservas\n");
            }
            break;

        case 3:
            listar_reservas_por_socio(db, id_socio_actual);
            break;

        case 4:
        {
            int id_instalacion;
            printf("ID de la instalacion: ");
            scanf("%d", &id_instalacion);
            listar_reservas_por_instalacion(db, id_instalacion);
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

int verificar_disponibilidad(sqlite3 *db, int id_instalacion, char *fecha, char *hora)
{

    sqlite3_stmt *stmt;

    const char *sql = "SELECT COUNT(*) FROM reservas WHERE id_instalacion = ? AND fecha = ? AND hora_inicio = ? AND estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }
    sqlite3_bind_int(stmt, 1, id_instalacion);
    sqlite3_bind_text(stmt, 2, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, hora, -1, SQLITE_STATIC);

    int cantidad = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        cantidad = sqlite3_column_int(stmt, 0);
        //                                  ^
        //                            columna 0 = el COUNT(*)
    }

    sqlite3_finalize(stmt);

    return (cantidad == 0); // 1 = disponible, 0 = ocupado
}

int crear_reserva(sqlite3 *db, int id_socio, int id_instalacion, char *fecha, char *hora, int duracion)
{
    if (verificar_disponibilidad(db, id_instalacion, fecha, hora) == 0)
    {
        return 0;
    }

    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO reservas (id_soc, id_instalacion, fecha, hora_inicio, duracion, estado, fecha_reserva) "
                      "VALUES (?, ?, ?, ?, ?, 'activa', date('now'))";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    // 2. Bind de parámetros
    sqlite3_bind_int(stmt, 1, id_socio);
    sqlite3_bind_int(stmt, 2, id_instalacion);
    sqlite3_bind_text(stmt, 3, fecha, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, hora, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, duracion);

    // 3. Ejecutar
    int resultado = sqlite3_step(stmt);

    // 4. Limpiar siempre, tanto si va bien como si no
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE)
    {
        printf("Reserva creada correctamente\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se creo la reserva\n");
        return 0;
    }
}

int cancelar_reserva(sqlite3 *db, int id_reserva, int id_socio)
{
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE reservas SET estado = 'cancelada' WHERE id_reserva = ? and id_soc = ? AND estado = 'activa'";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    // 2. Bind de parámetros
    sqlite3_bind_int(stmt, 1, id_reserva);
    sqlite3_bind_int(stmt, 2, id_socio);

    // 3. Ejecutar
    int resultado = sqlite3_step(stmt);

    // 4. Limpiar siempre, tanto si va bien como si no
    sqlite3_finalize(stmt);

    if (sqlite3_changes(db) > 0)
    {
        printf("Reserva cancelada correctamente\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se encontro la reserva\n");
        return 0;
    }
}

int cancelar_reserva_admin(sqlite3 *db, int id_reserva, char *motivo)
{
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE reservas SET estado = 'cancelada', motivo_cancelacion = ? WHERE id_reserva = ? AND estado = 'activa'";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }
    sqlite3_bind_text(stmt, 1, motivo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, id_reserva);

    // 3. Ejecutar
    int resultado = sqlite3_step(stmt);

    // 4. Limpiar siempre, tanto si va bien como si no
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE)
    {
        printf("Reserva cancelada por: %s\n", motivo);
        return 1;
    }
    else
    {
        printf("ERROR: No se encontro la reserva\n");
        return 0;
    }
}

void listar_reservas_activas(sqlite3 *db)
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT r.id_reserva, s.user, i.nombre, r.fecha, r.hora_inicio "
                      "FROM reservas r "
                      "JOIN usuarios s ON r.id_soc = s.id "
                      "JOIN instalaciones i ON r.id_instalacion = i.id_instalacion "
                      "WHERE r.estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return;
    }

    printf("\n=== RESERVAS ACTIVAS ===\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id          = sqlite3_column_int(stmt, 0);
        const char *user        = (const char *)sqlite3_column_text(stmt, 1);
        const char *instalacion = (const char *)sqlite3_column_text(stmt, 2);
        const char *fecha       = (const char *)sqlite3_column_text(stmt, 3);
        const char *hora        = (const char *)sqlite3_column_text(stmt, 4);

        printf("ID: %d | Socio: %s | Instalacion: %s | Fecha: %s | Hora: %s\n",
               id, user, instalacion, fecha, hora);
    }

    sqlite3_finalize(stmt);
}

void listar_reservas_por_socio(sqlite3 *db, int id_socio)
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT r.id_reserva, i.nombre, r.fecha, r.hora_inicio "
                      "FROM reservas r "
                      "JOIN instalaciones i ON r.id_instalacion = i.id_instalacion "
                      "WHERE r.id_soc = ? AND r.estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_socio);

    printf("\n=== MIS RESERVAS ===\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id                  = sqlite3_column_int(stmt, 0);
        const char *instalacion = (const char *)sqlite3_column_text(stmt, 1);
        const char *fecha       = (const char *)sqlite3_column_text(stmt, 2);
        const char *hora        = (const char *)sqlite3_column_text(stmt, 3);

        printf("ID: %d | Instalacion: %s | Fecha: %s | Hora: %s\n",
               id, instalacion, fecha, hora);
    }

    sqlite3_finalize(stmt);
}

void listar_reservas_por_instalacion(sqlite3 *db, int id_instalacion)
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT r.id_reserva, s.user, r.fecha, r.hora_inicio "
                      "FROM reservas r "
                      "JOIN usuarios s ON r.id_soc = s.id "
                      "WHERE r.id_instalacion = ? AND r.estado = 'activa'";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return;
    }

    sqlite3_bind_int(stmt, 1, id_instalacion);

    printf("\n=== RESERVAS DE LA INSTALACION ===\n");

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id          = sqlite3_column_int(stmt, 0);
        const char *user  = (const char *)sqlite3_column_text(stmt, 1);
        const char *fecha = (const char *)sqlite3_column_text(stmt, 2);
        const char *hora  = (const char *)sqlite3_column_text(stmt, 3);

        printf("ID: %d | Socio: %s | Fecha: %s | Hora: %s\n",
               id, user, fecha, hora);
    }

    sqlite3_finalize(stmt);
}