#include <stdio.h>

void menu_instalaciones(void)
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
        printf("4. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Mostrando ocupacion\n");
            break;
        case 2:
            printf("Alata de instalacion\n");
            break;
        case 3:
            printf("Baja de instalacion\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 4);
}