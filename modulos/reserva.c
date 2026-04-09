#include <stdio.h>
#include "reserva.h"

void menu_cancelacion_reservas(void) {
    int opcion;

    do {
        printf("\n--- CANCELACION DE RESERVAS ---\n");
        printf("1. Cancelar reserva por mantenimiento\n");
        printf("2. Consultar reservas activas\n");
        printf("3. Volver\n");
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Cancelando reserva\n");
                break;
            case 2:
                printf("Consultando reservas activas\n");
                break;
            case 3:
                printf("Volviendo\n");
                break;
            default:
                printf("Opcion no valida\n");
                break;
        }

    } while (opcion != 3);
}