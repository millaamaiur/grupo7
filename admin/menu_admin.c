#include <stdio.h>
#include "menu_admin.h"
#include "usuario.h"
#include "instalacion.h"
#include "reserva.h"

void menu_admin(void)

{
    // Variable de opcion
    int opcion;

    do
    {
        // Menu del admin
        printf("\n===== MENU ADMINISTRADOR =====\n");
        printf("1. Gestion de Usuarios\n");
        printf("2. Gestion de las instalaciones\n");
        printf("3. Cancelacion de las reservas\n");
        printf("4. salir\n");
        printf("Selecciona una opcion: ");

        // guardar la opcion
        scanf("%d", &opcion);

        // Redirigir segun la opcion
        switch (opcion)
        {
        case 1:
            menu_usuarios();
            break;
        case 2:
            menu_instalaciones();
            break;
        case 3:
            menu_cancelacion_reservas();
            break;
        case 4:
            printf("Saliendo del menu de administrador\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

        /* code */
    } while (opcion != 4);
}