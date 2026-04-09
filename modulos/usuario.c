#include "../include/usuario.h"


LoginResult login(char* user, char* password){
    if(strcmp(user, "admin") == 0 & strcmp(password, "1234") == 0){
        return LOGIN_ADMIN;
    }
    else if(strcmp(user, "socio") == 0 & strcmp(password, "1234") == 0){
        return LOGIN_SOCIO;
    }
    else{
        return LOGIN_ERROR
    }


}