#include <stdio.h>
#include "reserva.h"


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
            // Cancelar reserva
            {
                int id_reserva;
                printf("ID de la reserva a cancelar: ");
                scanf("%d", &id_reserva);
                cancelar_reserva(id_reserva, id_socio_actual);
            }
            break;
            
        case 2:
            // Consultar reservas activas (solo admin puede ver todas)
            if (es_admin) {
                listar_reservas_activas();
            } else {
                printf("Solo el administrador puede ver todas las reservas\n");
            }
            break;
            
        case 3:
            // Consultar mis reservas
            listar_reservas_por_socio(id_socio_actual);
            break;
            
        case 4:
            // Consultar reservas por instalacion
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