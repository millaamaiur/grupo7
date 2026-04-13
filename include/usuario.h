#ifndef USUARIO_H_
#define USUARIO_H_

void menu_usuarios(void);
int dar_alta_usuario(sqlite3 *db, char *user, char *password, char *rol, char *fecha_nac);

#endif