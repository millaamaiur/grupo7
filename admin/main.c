#include <stdio.h>
#include "menu_admin.h"
#include "base_datos.h"
#include "login.h"

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

    int id_socio_actual = 0;   

    printf("=====================================\n");
    printf("   SISTEMA DE GESTION DEPORTIVA\n");
    printf("=====================================\n");

    printf("Usuario: ");
    scanf("%49s", usuario);

    printf("Password: ");
    scanf("%49s", password);

    LoginResult resultado = login_db(db, usuario, password, &id_socio_actual);

    switch (resultado)
    {
    case LOGIN_ADMIN:
        printf("\n---Se ha iniciado sesion como administrador---\n");
        menu_admin(db, id_socio_actual);  //  PASAR ID
        break;

    case LOGIN_SOCIO:
        printf("\n---Se ha iniciado sesion como usuario---\n");
        // aquí luego se hará menu_usuario(db, id_socio_actual);
        break;

    case LOGIN_ERROR:
        printf("\n---Usuario y/o contrasena incorrectas---\n");
        break;

    default:
        printf("\n---Se ha producido un error---\n");
        break;
    }

    db_close(db);
    return 0;
}