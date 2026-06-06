#include <stdio.h>
#include <string.h>
#include "../include/instalacion.h"
#include <stdlib.h>

void menu_instalaciones(sqlite3 *db)
{

    // Variable de opcion
    int opcion;

    do
    {
        
        printf("Has entrado en la gestion de las instalaciones\n");
        
    
        printf("\n===== MENU DE GESTION DE LAS INSTALACIONES =====\n");
        printf("1. Ver ocupacion en tiempo real\n");
        printf("2. Alta de instalacion\n");
        printf("3. Baja de instalacion\n");
        printf("4. Modificar instalacion\n");
        printf("5. Bloquear instalacion por mantenimiento\n");
        printf("6. Consultar instalacion\n");
        printf("7. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;

        switch (opcion)
        {
        case 1:
            ver_ocupacion_instalaciones(db);
            break;
        case 2:
        {
            char buffer[100];
            int aforo_maximo;
            double precio_hora;
            Instalacion i;
            i.id_instalacion = -1;

            printf("Nombre de la instalacion: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.nombre = malloc(strlen(buffer) + 1);
            strcpy(i.nombre, buffer);

            printf("Tipo (piscina/pista/gimnasio...): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.tipo = malloc(strlen(buffer) + 1);
            strcpy(i.tipo, buffer);

            printf("Aforo maximo: ");
            scanf("%d", &aforo_maximo);
            i.aforo_maximo = aforo_maximo;

            printf("Precio por hora: ");
            scanf("%lf", &precio_hora);
            i.precio_hora = precio_hora;
            while (getchar() != '\n');

            printf("Estado (activa/inactiva): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.estado = malloc(strlen(buffer) + 1);
            strcpy(i.estado, buffer);

            alta_instalacion(db, i);

            free(i.nombre);
            free(i.tipo);
            free(i.estado);
            break;
        }

        case 3:
        {
            int id_instalacion;
            printf("Id de la instalacion a dar de baja: ");
            scanf("%d", &id_instalacion);

            baja_instalacion(db, id_instalacion);
            break;
        }
        case 4:
        {
            char buffer[100];
            int aforo_maximo;
            double precio_hora;
            Instalacion i;

            printf("Id de la instalacion: ");
            scanf("%d", &i.id_instalacion);

            int c;
            while ((c = getchar()) != '\n' && c != EOF);

            printf("Nombre de la instalacion: ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.nombre = malloc(strlen(buffer) + 1);
            strcpy(i.nombre, buffer);

            printf("Tipo (piscina/pista/gimnasio...): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.tipo = malloc(strlen(buffer) + 1);
            strcpy(i.tipo, buffer);

            printf("Aforo maximo: ");
            scanf("%d", &aforo_maximo);
            i.aforo_maximo = aforo_maximo;

            printf("Precio por hora: ");
            scanf("%lf", &precio_hora);
            i.precio_hora = precio_hora;

            while ((c = getchar()) != '\n' && c != EOF);

            printf("Estado (activa/inactiva): ");
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            i.estado = malloc(strlen(buffer) + 1);
            strcpy(i.estado, buffer);

            modificar_instalacion(db, i);

            free(i.nombre);
            free(i.tipo);
            free(i.estado);
            break;
        }
        case 5:
        {
            int id_instalacion;
            printf("Id de la instalacion a bloquear: ");
            scanf("%d", &id_instalacion);
            bloquear_mantenimiento(db, id_instalacion);
            break;
        }
        case 6:
            consultar_instalaciones(db);
            break;
        case 7:
            printf("Volviendo al menu del administrador\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 7);
}

void ver_ocupacion_instalaciones(sqlite3 *db)
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT i.nombre, COUNT(r.id_reserva) AS ocupacion "
                      "FROM instalaciones i "
                      "LEFT JOIN reservas r ON i.id_instalacion = r.id_instalacion "
                      "GROUP BY i.id_instalacion, i.nombre;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query: %s\n", sqlite3_errmsg(db));
        return;
    }
    system("cls");
    printf("\n--- OCUPACION DE INSTALACIONES ---\n");

    printf("+----------------------+-----------+\n");
    printf("| %-20s | %-9s |\n", "Instalacion", "Ocupacion");
    printf("+----------------------+-----------+\n");

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        int ocupacion = sqlite3_column_int(stmt, 1);

         printf("| %-20s | %-9d |\n", nombre, ocupacion);
    }
    printf("+----------------------+-----------+\n");
    sqlite3_finalize(stmt);
}

int alta_instalacion(sqlite3 *db, Instalacion i)
{
    sqlite3_stmt *stmt;

    const char *sql = "INSERT INTO instalaciones (nombre, tipo, aforo_maximo, precio_hora, estado) VALUES (?, ?, ?, ?, ?)";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    // 2. Bind de parámetros
    sqlite3_bind_text(stmt, 1, i.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, i.tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, i.aforo_maximo);
    sqlite3_bind_double(stmt, 4, i.precio_hora);
    sqlite3_bind_text(stmt, 5, i.estado, -1, SQLITE_STATIC);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE)
    {
        printf("Instalacion creada correctamente\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se pudo crear la instalacion\n");
        return 0;
    }
}

int baja_instalacion(sqlite3 *db, int id_instalacion)
{
    sqlite3_stmt *stmt;
    const char *sql = "UPDATE instalaciones SET estado = 'inactiva' WHERE id_instalacion = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    sqlite3_bind_int(stmt, 1, id_instalacion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado != SQLITE_DONE)
    {
        printf("ERROR: No se pudo desactivar la instalacion\n");
        return 0;
    }

    // Comprobar si realmente existia el ID
    if (sqlite3_changes(db) > 0)
    {
        printf("Instalacion desactivada correctamente\n");
        return 1;
    }
    else
    {
        printf("ERROR: No existe ninguna instalacion con ese ID\n");
        return 0;
    }
}

int modificar_instalacion(sqlite3 *db, Instalacion i)
{
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE instalaciones SET nombre = ?, tipo = ?, aforo_maximo = ?, precio_hora = ?, estado = ? WHERE id_instalacion = ?";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    // 2. Bind de parámetros
    sqlite3_bind_text(stmt, 1, i.nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, i.tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, i.aforo_maximo);
    sqlite3_bind_double(stmt, 4, i.precio_hora);
    sqlite3_bind_text(stmt, 5, i.estado, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, i.id_instalacion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE)
    {
        printf("Instalacion modificada correctamente\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se pudo modificar la instalacion\n");
        return 0;
    }
}

int bloquear_mantenimiento(sqlite3 *db, int id_instalacion)
{
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE instalaciones SET estado = 'mantenimiento' WHERE id_instalacion = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    sqlite3_bind_int(stmt, 1, id_instalacion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE)
    {
        if (sqlite3_changes(db) == 0)
        {
            printf("No existe ninguna instalacion con ese ID\n");
            return 0;
        }

        printf("Instalacion bloqueada por mantenimiento\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se pudo bloquear la instalacion\n");
        return 0;
    }
}

void consultar_instalaciones(sqlite3 *db)
{
    sqlite3_stmt *stmt;

    const char *sql = "SELECT id_instalacion, nombre, tipo, aforo_maximo, precio_hora, estado FROM instalaciones";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return;
    }
    system("cls");
    printf("\n--- LISTADO DE INSTALACIONES ---\n");
     printf("+------+----------------------+------------------+-------+--------+----------+\n");
    printf("| %-4s | %-20s | %-16s | %-5s | %-6s | %-8s |\n",
           "ID", "Nombre", "Tipo", "Aforo", "Precio", "Estado");
    printf("+------+----------------------+------------------+-------+--------+----------+\n");


    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char *tipo = sqlite3_column_text(stmt, 2);
        int aforo = sqlite3_column_int(stmt, 3);
        double precio = sqlite3_column_double(stmt, 4);
        const unsigned char *estado = sqlite3_column_text(stmt, 5);

 printf("| %-4d | %-20s | %-16s | %-5d | %-6.2f | %-8s |\n",
               id, nombre, tipo, aforo, precio, estado);
    }
        printf("+------+----------------------+------------------+-------+--------+----------+\n");
    sqlite3_finalize(stmt);
}
