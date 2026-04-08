#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int login_admin()
{

    char usuario[20];
    char contrasenya[20];

    printf("Usuario: ");
    scanf("%s", usuario);

    printf("Contrasenya: ");
    scanf("%s", contrasenya);

    // Hay que hacer un metodo de comprobacion
    // del usuario y contraseña

    bool login = true;

    if (login == true)
    {
        printf("Se ha iniciado sesion");
    }
    else
    {
        printf("Usuario y/o contrasenya incorrectas");
    }
    return 0;
}