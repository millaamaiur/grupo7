#include <stdio.h>
#include <string.h>
#include "taquilla.h"



void menu_taquillas(int id_socio_actual, int es_admin)
{
    int opcion;

    do
    {
        printf("\n=== GESTION DE TAQUILLAS ===\n");
        printf("1. Ver taquillas libres\n");
        printf("2. Alquilar una taquilla\n");
        printf("3. Ver mi taquilla\n");
        printf("4. Liberar mi taquilla\n");
        
        if (es_admin) {
            printf("5. Ver todas las taquillas (Admin)\n");
            printf("6. Salir\n");
        } else {
            printf("5. Salir\n");
        }
        
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        // Limpiar lo que recibe el teclado en el scanf
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (opcion)
        {
        case 1:
            //ver_taquillas_libres();
            break;
            
        case 2:
            {
                int id_taquilla;
                printf("ID de la taquilla a alquilar: ");
                scanf("%d", &id_taquilla);
                //alquilar_taquilla(id_socio_actual, id_taquilla);
            }
            break;
            
        case 3:
            //ver_mi_taquilla(id_socio_actual);
            break;
            
        case 4:
            //liberar_mi_taquilla(id_socio_actual);
            break;
            
        case 5:
            if (es_admin) {
                //ver_todas_taquillas();
            } else {
                printf("Volviendo al menu principal\n");
            }
            break;
            
        case 6:
            if (es_admin) {
                printf("Volviendo al menu principal\n");
            }
            break;
            
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while ((es_admin && opcion != 6) || (!es_admin && opcion != 5));
}

