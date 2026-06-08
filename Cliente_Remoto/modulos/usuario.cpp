#include "../include/usuario.h"
#include <iostream>
#include <cstring>

using namespace std;

// Funcion auxiliar de ayuda
static char *copiarCadena(const char *texto)
{
    if (texto == nullptr)
    {
        char *copia = new char[1];
        copia[0] = '\0';
        return copia;
    }

    char *copia = new char[strlen(texto) + 1];
    strcpy(copia, texto);
    return copia;
}

Usuario::Usuario()
{
    this->id = -1;
    this->user = copiarCadena("");
    this->rol = copiarCadena("");
    this->fecha_nac = copiarCadena("");
    this->fecha_alta = copiarCadena("");
    this->id_suscrip = -1;
}

Usuario::Usuario(int id, const char *user, const char *rol, const char *fecha_nac, const char *fecha_alta, int id_suscrip)
{
    this->id = id;
    this->user = copiarCadena(user);
    this->rol = copiarCadena(rol);
    this->fecha_nac = copiarCadena(fecha_nac);
    this->fecha_alta = copiarCadena(fecha_alta);
    this->id_suscrip = id_suscrip;
}

Usuario::Usuario(const Usuario &otro)
{
    this->id = otro.id;
    this->user = copiarCadena(otro.user);
    this->rol = copiarCadena(otro.rol);
    this->fecha_nac = copiarCadena(otro.fecha_nac);
    this->fecha_alta = copiarCadena(otro.fecha_alta);
    this->id_suscrip = otro.id_suscrip;
}

Usuario &Usuario::operator=(const Usuario &otro)
{
    if (this != &otro)
    {
        delete[] this->user;
        delete[] this->rol;
        delete[] this->fecha_nac;
        delete[] this->fecha_alta;

        this->id = otro.id;
        this->user = copiarCadena(otro.user);
        this->rol = copiarCadena(otro.rol);
        this->fecha_nac = copiarCadena(otro.fecha_nac);
        this->fecha_alta = copiarCadena(otro.fecha_alta);
        this->id_suscrip = otro.id_suscrip;
    }

    return *this;
}

Usuario::~Usuario()
{
    delete[] this->user;
    delete[] this->rol;
    delete[] this->fecha_nac;
    delete[] this->fecha_alta;
}

int Usuario::getId() const
{
    return this->id;
}

const char *Usuario::getUser() const
{
    return this->user;
}

const char *Usuario::getRol() const
{
    return this->rol;
}

const char *Usuario::getFechaNac() const
{
    return this->fecha_nac;
}

const char *Usuario::getFechaAlta() const
{
    return this->fecha_alta;
}

int Usuario::getIdSuscrip() const
{
    return this->id_suscrip;
}

void Usuario::setId(int id)
{
    this->id = id;
}

void Usuario::setUser(const char *user)
{
    delete[] this->user;
    this->user = copiarCadena(user);
}

void Usuario::setRol(const char *rol)
{
    delete[] this->rol;
    this->rol = copiarCadena(rol);
}

void Usuario::setFechaNac(const char *fecha_nac)
{
    delete[] this->fecha_nac;
    this->fecha_nac = copiarCadena(fecha_nac);
}

void Usuario::setFechaAlta(const char *fecha_alta)
{
    delete[] this->fecha_alta;
    this->fecha_alta = copiarCadena(fecha_alta);
}

void Usuario::setIdSuscrip(int id_suscrip)
{
    this->id_suscrip = id_suscrip;
}

bool Usuario::esAdmin() const
{
    return strcmp(this->rol, "admin") == 0;
}

bool Usuario::esSocio() const
{
    return strcmp(this->rol, "socio") == 0;
}

void Usuario::mostrar() const
{
    cout << "ID: " << this->id << endl;
    cout << "Usuario: " << this->user << endl;
    cout << "Rol: " << this->rol << endl;
    cout << "Fecha nacimiento: " << this->fecha_nac << endl;
    cout << "Fecha alta: " << this->fecha_alta << endl;
    cout << "ID suscripcion: " << this->id_suscrip << endl;
}