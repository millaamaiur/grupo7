#include <stdio.h>
#include "include/menu_admin.h"
#include "include/config.h"
#include "include/base_datos.h"
#include "include/login.h"
#include "include/horario.h"
#include "include/instalacion.h"
#include "include/reserva.h"
#include "sqlite3.h"
#include "include/taquilla.h"
#include "include/usuario.h"
#include "include/utilidades.h"

int main(void)
{
    sqlite3 *db;
    Config cfg = load_config(CONFIG_PATH);
    db = db_open(cfg.db_path);

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