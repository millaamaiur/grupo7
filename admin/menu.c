#include <stdio.h>
#include <string.h>
#include "menu.h"

#define MAX_USUARIOS 100

typedef struct {
    char nombre[50];
    char password[50];
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int numUsuarios = 0;

int buscarUsuario(char* nombre) {
    for(int i = 0; i < numUsuarios; i++) {
        if(strcmp(usuarios[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

int crearCuenta(char* nombre, char* password) {
    if(buscarUsuario(nombre) != -1) return -1;
    if(numUsuarios >= MAX_USUARIOS) return -2;
    
    strcpy(usuarios[numUsuarios].nombre, nombre);
    strcpy(usuarios[numUsuarios].password, password);
    numUsuarios++;
    return 0;
}

int iniciarSesion(char* nombre, char* password) {
    int pos = buscarUsuario(nombre);
    if(pos != -1 && strcmp(usuarios[pos].password, password) == 0) {
        return 1;
    }
    return 0;
}

void ejecutarMenu(void) {
    int opcion;
    char nombre[50];
    char password[50];
    
    do {
        printf("\n=====================================\n");
        printf("   SISTEMA DE GESTION DEPORTIVA\n");
        printf("=====================================\n");
        printf("1. Iniciar sesion\n");
        printf("2. Crear cuenta\n");
        printf("3. Salir\n");
        printf("=====================================\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion) {
            case 1:
                printf("\n--- INICIAR SESION ---\n");
                printf("Usuario: ");
                scanf("%s", nombre);
                printf("Contrasena: ");
                scanf("%s", password);
                
                if(iniciarSesion(nombre, password)) {
                    printf("\n Sesion iniciada. Bienvenido %s\n", nombre);
                } else {
                    printf("\n Usuario o contraseña incorrectos\n");
                }
                break;
                
            case 2:
                printf("\n--- CREAR CUENTA ---\n");
                printf("Usuario: ");
                scanf("%s", nombre);
                printf("Contraseña: ");
                scanf("%s", password);
                
                int resultado = crearCuenta(nombre, password);
                
                if(resultado == 0) {
                    printf("\n Cuenta creada correctamente\n");
                } else if(resultado == -1) {
                    printf("\n El usuario ya existe\n");
                } else {
                    printf("\n Limite de usuarios alcanzado\n");
                }
                break;
                
            case 3:
                printf("\nSaliendo...\n");
                break;
                
            default:
                printf("\nOpcion no valida\n");
        }
    } while(opcion != 3);
}