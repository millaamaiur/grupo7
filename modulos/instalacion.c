#include <stdio.h>
#include <stdio.h>
#include "instalacion.h"

void menu_instalaciones(sqlite3 *db)
{

    // Variable de opcion
    int opcion;

    do
    {
        // Mostrar confirmacion
        printf("Has entrado en la gestion de las instalaciones\n");

        // Mostrar menu
        printf("\n===== MENU DE GESTION DE LAS INSTALACIONES =====\n");
        printf("1. Ver ocupacion en tiempo real\n");
        printf("2. Alta de instalacion\n");
        printf("3. Baja de instalacion\n");
        printf("4. Modificar instalacion\n");
        printf("5. Bloquear instalacion por mantenimiento\n");
        printf("6. Consultar instalacion\n");
        printf("7. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion)
        {
        case 1:
            ver_ocupacion_instalaciones(db);
            break;
        case 2:
            char nombre[100];
            char tipo[50];
            int aforo_maximo;
            double precio_hora;
            char estado[20];

            printf("Nombre de la instalacion: ");
            scanf("%99s", nombre);

            printf("Tipo (piscina/pista/gimnasio...): ");
            scanf("%49s", tipo);

            printf("Aforo maximo: ");
            scanf("%d", &aforo_maximo);

            printf("Precio por hora: ");
            scanf("%lf", &precio_hora);

            printf("Estado (activa/inactiva): ");
            scanf("%19s", estado);

            alta_instalacion(db, nombre, tipo, aforo_maximo, precio_hora, estado);
            break;

        case 3:
            int id_instalacion;
            printf("Id de la instalacion a dar de baja: ");
            scanf("%d", &id_instalacion);


            baja_instalacion(db, id_instalacion);
            break;
        case 4:
            int id_instalacion;
            char nombre[100];
            char tipo[50];
            int aforo_maximo;
            double precio_hora;
            char estado[20];
            
            printf("Id de la instalación: ");
            scanf("%d", &id_instalacion);

            printf("Nombre de la instalacion: ");
            scanf("%99s", nombre);

            printf("Tipo (piscina/pista/gimnasio...): ");
            scanf("%49s", tipo);

            printf("Aforo maximo: ");
            scanf("%d", &aforo_maximo);

            printf("Precio por hora: ");
            scanf("%lf", &precio_hora);

            printf("Estado (activa/inactiva): ");
            scanf("%19s", estado);

            modificar_instalacion(db, id_instalacion, nombre, tipo, aforo_maximo, precio_hora, estado);
            break;
        case 5:
            int id_instalacion;
            printf("Id de la instalacion a bloquear: ");
            scanf("%d", &id_instalacion);
            bloquear_mantenimiento(db, id_instalacion);
            break;
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

    const char *sql =  "SELECT i.nombre, COUNT(r.id) AS ocupacion "
        "FROM instalaciones i "
        "LEFT JOIN reservas r ON i.id = r.instalacion_id "
        "GROUP BY i.id;";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    printf("\n--- OCUPACION DE INSTALACIONES ---\n");

    while(sqlite3_step(stmt) == SQLITE_ROW){
        const unsigned char *nombre = sqlite3_column_text(stmt, 0);
        int ocupacion = sqlite3_column_int(stmt, 1);

        printf("Instalacion: %s | Ocupacion: %d\n", nombre, ocupacion);
    }

    sqlite3_finalize(stmt);
}

int alta_instalacion(sqlite3 *db, char* nombre, char* tipo, int aforo_maximo, double precio_hora, char* estado)
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
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, aforo_maximo);
    sqlite3_bind_double(stmt, 4, precio_hora);
    sqlite3_bind_text(stmt, 5, estado, -1, SQLITE_STATIC);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        printf("Instalación creada correctamente\n");
        return 1;
    } else {
        printf("ERROR: No se pudo crear la instalación\n");
        return 0;
    }

}

int baja_instalacion(sqlite3 *db, int id_instalacion)
{
    sqlite3_stmt *stmt;

    const char *sql = "UPDATE instalaciones SET estado = 'inactiva' WHERE id_instalacion = ?";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    sqlite3_bind_int(stmt, 1, id_instalacion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        printf("Instalación desactivada correctamente\n");
        return 1;
    } else {
        printf("ERROR: No se pudo desactivar la instalación\n");
        return 0;
    }
}

int modificar_instalacion(sqlite3 *db, int id_instalacion, char* nombre, char* tipo, int aforo_maximo, double precio_hora, char* estado)
{
    sqlite3 *stmt;

    const char sql = "UPDATE instalaciones SET nombre = ?, tipo = ?, aforo_maximo = ?, precio_hora = ?, estado = ? WHERE id_instalacion = ?";

    // 1. Preparar la consulta
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
    {
        printf("Error al preparar la query\n");
        return 0;
    }

    // 2. Bind de parámetros
    sqlite3_bind_text(stmt, 1, nombre, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, tipo, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 3, aforo_maximo);
    sqlite3_bind_double(stmt, 4, precio_hora);
    sqlite3_bind_text(stmt, 5, estado, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 6, id_instalacion);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        printf("Instalación modificada correctamente\n");
        return 1;
    } else {
        printf("ERROR: No se pudo modificar la instalación\n");
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
        if (sqlite3_changes(db) == 0) {
            printf("No existe ninguna instalación con ese ID\n");
            return 0;
        }

        printf("Instalación bloqueada por mantenimiento\n");
        return 1;
    }
    else
    {
        printf("ERROR: No se pudo bloquear la instalación\n");
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

    printf("\n--- LISTADO DE INSTALACIONES ---\n");

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *nombre = sqlite3_column_text(stmt, 1);
        const unsigned char *tipo = sqlite3_column_text(stmt, 2);
        int aforo = sqlite3_column_int(stmt, 3);
        double precio = sqlite3_column_double(stmt, 4);
        const unsigned char *estado = sqlite3_column_text(stmt, 5);

        printf("ID: %d | %s | Tipo: %s | Aforo: %d | Precio: %.2f | Estado: %s\n",
               id, nombre, tipo, aforo, precio, estado);
    }

    sqlite3_finalize(stmt);
}
