#include "../include/usuario.h"
#include "../include/base_datos.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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
            char *usuario = malloc(20 * sizeof(char));
            int valido = 0;
            sqlite3 *db = db_open("../database/database.db");
            while (!valido)
            {
                printf("Inserte nombre de usuario (3-19 caracteres): ");
                if (scanf("%19s", usuario) != 1)
                {
                    printf("Error al leer el usuario.\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                // Limpiar el buffer
                while (getchar() != '\n')
                    ;
                // Comprobar longitud (minimo 3 caracteres)
                int longitud = strlen(usuario);
                if (longitud < 3)
                {
                    printf("Error: El usuario debe tener al menos 3 caracteres.\n");
                    continue;
                }
                // Comprobar si el usuario ya existe en la base de datos
                if (db == NULL)
                {
                    printf("Error: No se pudo conectar a la base de datos.\n");
                    continue;
                }

                sqlite3_stmt *stmt;
                const char *sql = "SELECT id FROM usuarios WHERE user = ?";
                if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
                {
                    printf("Error al preparar la consulta.\n");
                    db_close(db);
                    continue;
                }
                sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);

                int step = sqlite3_step(stmt);

                if (step == SQLITE_ROW)
                {
                    printf("Error: El usuario '%s' ya existe en la base de datos.\n", usuario);
                    sqlite3_finalize(stmt);
                    db_close(db);
                    continue;
                }
                sqlite3_finalize(stmt);
                db_close(db);

                valido = 1;
            }

            char *password = malloc(20 * sizeof(char));
            int valido2 = 0;
            while (!valido)
            {
                printf("Inserte una contraseña (minimo 6 caracteres): ");
                if (scanf("%19s", password) != 1)
                {
                    printf("Error al leer la contraseña.\n");
                    while (getchar() != '\n')
                        ;
                    continue;
                }
                // Limpiar el buffer
                while (getchar() != '\n')
                    ;
                // Comprobar longitud (minimo 6 caracteres)
                int longitud = strlen(password);
                if (longitud < 6)
                {
                    printf("Error: La contraseña debe tener al menos 6 caracteres.\n");
                    continue;
                }
                valido2 = 1;
            }
            int rol_opcion;
            char* rol;
            printf("\nSeleccione el rol del usuario:\n");
            printf("1. Administrador\n");
            printf("2. Usuario (socio)\n");
            printf("Opcion: ");
            scanf("%d", &rol_opcion);
            while (getchar() != '\n');

            if (rol_opcion == 1) {
                rol = "admin";
            } else {
                rol = "socio";
            }

            char fecha_nacimiento[11];  // YYYY-MM-DD + null terminator
            int fecha_valida = 0;
            while (!fecha_valida) {
                printf("Inserte fecha de nacimiento (YYYY-MM-DD): ");
                scanf("%10s", fecha_nacimiento);
                while (getchar() != '\n');

                // Comprobar formato basico: debe tener 10 caracteres
                if (strlen(fecha_nacimiento) != 10) {
                    printf("Error: Formato incorrecto. Use YYYY-MM-DD\n");
                    continue;
                }

                // Comprobar que los caracteres esten en la posicion correcta
                if (fecha_nacimiento[4] != '-' || fecha_nacimiento[7] != '-') {
                    printf("Error: Formato incorrecto. Use YYYY-MM-DD\n");
                    continue;
                }

                fecha_valida = 1;
            }

            sqlite3_stmt *stmt;

            const char *sql = "INSERT INTO usuarios (user, password, rol, fecha_nac) "
                                "VALUES (?, ?, ?, ?)";

            // 1. Preparar la consulta
            if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK)
            {
                printf("Error al preparar la query\n");
                return 0;
            }

            // 2. Bind de parámetros
            sqlite3_bind_text(stmt, 1, usuario, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 2, password, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 3, rol, -1, SQLITE_STATIC);
            sqlite3_bind_text(stmt, 4, fecha_nacimiento, -1, SQLITE_STATIC);

            // 3. Ejecutar
            int resultado = sqlite3_step(stmt);

            // 4. Limpiar siempre, tanto si va bien como si no
            sqlite3_finalize(stmt);

            if (resultado == SQLITE_DONE)
            {
                printf("Reserva creada correctamente\n");
                menu_usuarios();
            }
            else
            {
                printf("ERROR: No se creo la reserva\n");
                menu_usuarios;
            }

            free(usuario);
            free(password);
            break;
        case 2:
            printf("Baja de usuario\n");
            break;
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