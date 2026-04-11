#include <stdio.h>
#include "menu_admin.h"
#include "base_datos.h"
#include "funciones_base_datos.h"

int main(void)
{

    sqlite3 *db;
    db = db_open();

    if (db == NULL) {
        printf("Error al abrir la base de datos\n");
        return -1;
    }

    char usuario[50];
    char password[50];

    printf("=====================================\n");
    printf("   SISTEMA DE GESTION DEPORTIVA\n");
    printf("=====================================\n");

    /*He hecho esto como prueba pero mas adelante habrá que hacer dependiendo de
    si la persona que hace login es admin o cliente mostrarle otro menu distinto*/

    printf("Usuario: ");
    scanf("%49s", usuario);

    printf("Password: ");
    scanf("%49s", password);

    // Guardar usuario y contraseña
    LoginResult resultado = login_db(db, usuario, password);

    // Redirigir segun -> socio/admin/Error
    switch (resultado)
    {
    case LOGIN_ADMIN:
        printf("\n---Se ha iniciado sesion como administrador---\n");
        menu_admin();
        break;
    case LOGIN_SOCIO:
        printf("\n---Se ha iniciado sesion como usuario---\n");
        break;
    case LOGIN_ERROR:
        printf("\n---Usuario y/o contraseña incorrectas---\n");
        break;
    default:
        printf("\n---Se ha producido un error---\n");
        break;
    }


    db_close(db);
    
    return 0;
}