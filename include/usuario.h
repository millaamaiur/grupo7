#ifndef USUARIO_H_
#define USUARIO_H_


typedef enum{
    LOGIN_ERROR,
    LOGIN_ADMIN,
    LOGIN_SOCIO
} LoginResult;

LoginResult login(char* user, char* password);

#endif