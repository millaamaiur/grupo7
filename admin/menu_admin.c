#include <stdio.h>
#include "menu_admin.h"
#include "usuario.h"
#include "instalacion.h"
#include "reserva.h"

void menu_admin(sqlite3 *db, int id_socio_actual)
{
    int opcion;

    do
    {
        printf("\n===== MENU ADMINISTRADOR =====\n");
        printf("1. Gestion de Usuarios\n");
        printf("2. Gestion de las instalaciones\n");
        printf("3. Cancelacion de las reservas\n");
        printf("4. Salir\n");
        printf("Selecciona una opcion: ");

        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            menu_usuarios(db);
            break;
        case 2:
            menu_instalaciones(db);
            break;
        case 3:
            menu_cancelacion_reservas(db, id_socio_actual, 1); 
            break;
        case 4:
            printf("Saliendo del menu de administrador\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 4);
}