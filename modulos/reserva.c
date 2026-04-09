#include <stdio.h>
#include "reserva.h"

void menu_cancelacion_reservas(void)
{
    int opcion;

    do
    {
        printf("\n--- CANCELACION DE RESERVAS ---\n");
        printf("1. Cancelar reserva por mantenimiento\n");
        printf("2. Consultar reservas activas\n");
        printf("3, Consultar reservas por usuarios\n");
        printf("4. Consultar reservas por instalacion\n");
        printf("5. Volver\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion)
        {
        case 1:
            cancelar_reserva_mantenimiento();
            break;
        case 2:
            consultar_reservas_activas();
            break;
        case 3:
            consultar_reservas_usuario();
            break;
        case 4:
            consultar_reservas_instalacion();
            break;
        case 5:
            printf("Volviendo\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 5);
}

void cancelar_reserva_mantenimiento(void)
{
    printf("Cancelando reserva\n");
}

void consultar_reservas_activas(void)
{
    printf("Consultando reservas activas\n");
}

void consultar_reservas_usuario(void)
{
    printf("Consultando reservas de usuario\n");
}
void consultar_reservas_instalacion(void)
{
    printf("Consultando reservas de instalaciones\n");
}