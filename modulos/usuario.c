#include "../include/usuario.h"
#include "../include/base_datos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


void menu_usuarios(sqlite3 *db)
{
    int opcion;

    do {
        printf("Has entrado en la gestion de Usuario\n");
        printf("\n===== MENU DE GESTION DE USUARIOS =====\n");
        printf("1. Dar de alta a nuevos socios\n");
        printf("2. Dar de baja a socios\n");
        printf("3. Modificar la suscripcion de un socio\n");
        printf("4. Volver\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        while (getchar() != '\n');

        switch (opcion)
        {
        //Alta de usuario
        case 1:
        {
            // --- Recoger y validar usuario ---
            char usuario[20];
            int valido = 0;
            while (!valido) {
                printf("Inserte nombre de usuario (3-19 caracteres): ");
                if (scanf("%19s", usuario) != 1) {
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                if (strlen(usuario) < 3) {
                    printf("Error: El usuario debe tener al menos 3 caracteres.\n");
                    continue;
                }

                // Comprobar si el usuario ya existe
                sqlite3_stmt *stmt;
                const char *sql_check = "SELECT id FROM usuarios WHERE user = ?";
                if (sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL) != SQLITE_OK) {
                    printf("Error al preparar la consulta.\n");
                    continue;
                }
                sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
                if (sqlite3_step(stmt) == SQLITE_ROW) {
                    printf("Error: El usuario '%s' ya existe.\n", usuario);
                    sqlite3_finalize(stmt);
                    continue;
                }
                sqlite3_finalize(stmt);
                valido = 1;
            }

            // --- Recoger y validar password ---
            char password[20];
            int valido2 = 0;
            while (!valido2) {
                printf("Inserte una contrasena (minimo 6 caracteres): ");
                if (scanf("%19s", password) != 1) {
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                if (strlen(password) < 6) {
                    printf("Error: La contrasena debe tener al menos 6 caracteres.\n");
                    continue;
                }
                valido2 = 1;
            }

            // --- Recoger rol ---
            int rol_opcion;
            char *rol;
            printf("\nSeleccione el rol:\n1. Administrador\n2. Socio\nOpcion: ");
            scanf("%d", &rol_opcion);
            while (getchar() != '\n');
            rol = (rol_opcion == 1) ? "admin" : "socio";

            // --- Recoger y validar fecha de nacimiento ---
            char fecha_nacimiento[11];
            int fecha_valida = 0;
            while (!fecha_valida) {
                printf("Inserte fecha de nacimiento (YYYY-MM-DD): ");
                scanf("%10s", fecha_nacimiento);
                while (getchar() != '\n');

                if (strlen(fecha_nacimiento) != 10 ||
                    fecha_nacimiento[4] != '-' || fecha_nacimiento[7] != '-') {
                    printf("Error: Formato incorrecto. Use YYYY-MM-DD\n");
                    continue;
                }
                fecha_valida = 1;
            }

            // --- Llamar a la función de BD ---
            dar_alta_usuario(db, usuario, password, rol, fecha_nacimiento);
            break;
        }
        //Baja de usuario 
        case 2:
        {
            char usuario[20];
            char password[20];
            int valido = 0;

            // --- Recoger y validar usuario ---
            while (!valido) {
                printf("Inserte nombre de usuario a dar de baja: ");
                if (scanf("%19s", usuario) != 1) {
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                if (strlen(usuario) < 3) {
                    printf("Error: El usuario debe tener al menos 3 caracteres.\n");
                    continue;
                }

                // --- Recoger password ---
                printf("Inserte la contrasena del usuario: ");
                if (scanf("%19s", password) != 1) {
                    while (getchar() != '\n');
                    continue;
                }
                while (getchar() != '\n');

                // --- Comprobar si el usuario y password coinciden ---
                sqlite3_stmt *stmt;
                const char *sql_check = "SELECT id FROM usuarios WHERE user = ? AND password = ?";

                if (sqlite3_prepare_v2(db, sql_check, -1, &stmt, NULL) != SQLITE_OK) {
                    printf("Error al preparar la consulta.\n");
                    continue;
                }

                sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
                sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);

                if (sqlite3_step(stmt) != SQLITE_ROW) {
                    printf("Error: Usuario o contrasena incorrectos.\n");
                    sqlite3_finalize(stmt);
                    continue;
                }

                sqlite3_finalize(stmt);
                valido = 1;
            }

            // --- Confirmacion antes de borrar ---
            char confirmacion;
            printf("¿Seguro que desea dar de baja al usuario '%s'? (s/n): ", usuario);
            scanf(" %c", &confirmacion);
            while (getchar() != '\n');

            if (confirmacion == 's' || confirmacion == 'S') {
                dar_baja_usuario(db, usuario);
            } else {
                printf("Operacion cancelada.\n");
            }

            break;
        }
        case 3:
            printf("Modificar suscripcion\n");
            break;
        case 4:
            printf("Volviendo al menu de administrador\n");
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }

    } while (opcion != 4);
}

int dar_alta_usuario(sqlite3 *db, char *user, char *password, char *rol, char *fecha_nac)
{
    sqlite3_stmt *stmt;
    const char *sql = "INSERT INTO usuarios (user, password, rol, fecha_nac) "
                      "VALUES (?, ?, ?, ?)";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return 0;
    }

    sqlite3_bind_text(stmt, 1, user,      -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password,  -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, rol,       -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, fecha_nac, -1, SQLITE_STATIC);

    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado == SQLITE_DONE) {
        printf("Usuario creado correctamente\n");
        return 1;
    } else {
        printf("ERROR: No se pudo crear el usuario\n");
        return 0;
    }
}

int dar_baja_usuario(sqlite3 *db, char *user)
{
    sqlite3_stmt *stmt;
    const char *sql = "DELETE FROM usuarios WHERE user = ?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        printf("Error al preparar la query\n");
        return 0;
    }

    sqlite3_bind_text(stmt, 1, user, -1, SQLITE_STATIC);
    
    int resultado = sqlite3_step(stmt);
    sqlite3_finalize(stmt);

    if (resultado != SQLITE_DONE) {
        printf("ERROR: No se pudo eliminar el usuario\n");
        return 0;
    } 

    //Comprobar si se ha borrado
    if(sqlite3_changes(db) > 0) {
        printf("Usuario eliminado correctamente\n");
    } else { 
        printf("No se encontro el usuario para eliminar\n");
    }
}
