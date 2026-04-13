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
            alta_instalacion();
            break;
        case 3:
            baja_instalacion();
            break;
        case 4:
            modificar_instalacion();
            break;
        case 5:
            bloquear_mantenimiento();
            break;
        case 6:
            consultar_instalaciones();
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
        int ocupacion = sqlite3_columnt_int(stmt, 1);

        printf("Instalacion: %s | Ocupacion: %d\n", nombre, ocupacion);
    }

    sqlite3_finalize(stmt);
}

void alta_instalacion(void)
{
    printf("---Alta de instalacion---\n");
}

void baja_instalacion(void)
{
    printf("---Baja de instalacion---\n");
}

void modificar_instalacion(void)
{
    printf("---Opciones para modificar la instalacion---\n");
}

void bloquear_mantenimiento(void)
{
    printf("---Bloquear instalacion por mantenimiento---\n");
}

void consultar_instalaciones(void)
{
    printf("---Consultando instalaciones---\n");
}
