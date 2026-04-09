#include "../include/usuario.h"
#include <string.h>

LoginResult login(char *user, char *password)
{
    if (strcmp(user, "admin") == 0 && strcmp(password, "1234") == 0)
    {
        return LOGIN_ADMIN;
    }
    else if (strcmp(user, "socio") == 0 & strcmp(password, "1234") == 0)
    {
        return LOGIN_SOCIO;
    }
    else
    {
        return LOGIN_ERROR;
    }
}

void menu_usuarios(void)
{

    // Variable de opcion
    int opcion;

    do
    {

        // Mostrar confirmacion
        printf("Has entrado en la gestion de Usuario\n");

        // Mostrar menu
        printf("\n===== MENU DE GESTION DE USUARIOS =====\n");
        printf("1. Dar de alta a nuevos socios\n");
        printf("2. Dar de baja a socios\n");
        printf("3. modificar la suscripcion de un socio\n");
        printf("4. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            printf("Alta de usuario\n");
            break;
        case 2:
            printf("Baja de usuario\n");
            break;
        case 3:
            printf("Modificar suscripcion\n");
        case 4:
            printf("Volviendo al menu de administrador\n");
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 4);
}