#include <stdio.h>

int main(void){

    printf("=====================================\n");
    printf("   SISTEMA DE GESTION DEPORTIVA\n");
    printf("=====================================\n");

    

    /*He hecho esto como prueba pero mas adelante habrá que hacer dependiendo de
    si la persona que hace login es admin o cliente mostrarle otro menu distinto*/
    char usuario[50];
    char password[50];

    printf("Usuario: ");
    scanf("%s", usuario);

    printf("Password: ");
    scanf("%s", password);

    printf("\nHas introducido:\n");
    printf("Usuario: %s\n", usuario);
    printf("Password: %s\n", password);

    return 0;
}