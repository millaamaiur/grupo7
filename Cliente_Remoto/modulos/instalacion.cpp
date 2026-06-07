#include "../include/Instalacion.h"
#include <iostream>
#include <cstring>

using namespace std;

//Funcion auxiliar de ayuda
static char* copiarCadena(const char* texto)
{
    if (texto == nullptr)
    {
        char* copia = new char[1];
        copia[0] = '\0';
        return copia;
    }

    char* copia = new char[strlen(texto) + 1];
    strcpy(copia, texto);
    return copia;
}

Instalacion::Instalacion()
{
    this->id_instalacion = -1;
    this->nombre = copiarCadena("");
    this->tipo = copiarCadena("");
    this->aforo_maximo = 0;
    this->precio_hora = 0.0;
    this->estado = copiarCadena("");
}

Instalacion::Instalacion(int id_instalacion, const char* nombre, const char* tipo, int aforo_maximo, double precio_hora, const char* estado)
{
    this->id_instalacion = id_instalacion;
    this->nombre = copiarCadena(nombre);
    this->tipo = copiarCadena(tipo);
    this->aforo_maximo = aforo_maximo;
    this->precio_hora = precio_hora;
    this->estado = copiarCadena(estado);
}

Instalacion::Instalacion(const Instalacion& otra)
{
    this->id_instalacion = otra.id_instalacion;
    this->nombre = copiarCadena(otra.nombre);
    this->tipo = copiarCadena(otra.tipo);
    this->aforo_maximo = otra.aforo_maximo;
    this->precio_hora = otra.precio_hora;
    this->estado = copiarCadena(otra.estado);
}

Instalacion& Instalacion::operator=(const Instalacion& otra)
{
    if (this != &otra)
    {
        delete[] this->nombre;
        delete[] this->tipo;
        delete[] this->estado;

        this->id_instalacion = otra.id_instalacion;
        this->nombre = copiarCadena(otra.nombre);
        this->tipo = copiarCadena(otra.tipo);
        this->aforo_maximo = otra.aforo_maximo;
        this->precio_hora = otra.precio_hora;
        this->estado = copiarCadena(otra.estado);
    }

    return *this;
}

Instalacion::~Instalacion()
{
    delete[] this->nombre;
    delete[] this->tipo;
    delete[] this->estado;
}

int Instalacion::getIdInstalacion() const
{
    return this->id_instalacion;
}

const char* Instalacion::getNombre() const
{
    return this->nombre;
}

const char* Instalacion::getTipo() const
{
    return this->tipo;
}

int Instalacion::getAforoMaximo() const
{
    return this->aforo_maximo;
}

double Instalacion::getPrecioHora() const
{
    return this->precio_hora;
}

const char* Instalacion::getEstado() const
{
    return this->estado;
}

void Instalacion::setIdInstalacion(int id_instalacion)
{
    this->id_instalacion = id_instalacion;
}

void Instalacion::setNombre(const char* nombre)
{
    delete[] this->nombre;
    this->nombre = copiarCadena(nombre);
}

void Instalacion::setTipo(const char* tipo)
{
    delete[] this->tipo;
    this->tipo = copiarCadena(tipo);
}

void Instalacion::setAforoMaximo(int aforo_maximo)
{
    this->aforo_maximo = aforo_maximo;
}

void Instalacion::setPrecioHora(double precio_hora)
{
    this->precio_hora = precio_hora;
}

void Instalacion::setEstado(const char* estado)
{
    delete[] this->estado;
    this->estado = copiarCadena(estado);
}

bool Instalacion::estaActiva() const
{
    return strcmp(this->estado, "activa") == 0;
}

bool Instalacion::estaEnMantenimiento() const
{
    return strcmp(this->estado, "mantenimiento") == 0;
}

void Instalacion::mostrar() const
{
    cout << "ID instalacion: " << this->id_instalacion << endl;
    cout << "Nombre: " << this->nombre << endl;
    cout << "Tipo: " << this->tipo << endl;
    cout << "Aforo maximo: " << this->aforo_maximo << endl;
    cout << "Precio por hora: " << this->precio_hora << endl;
    cout << "Estado: " << this->estado << endl;
}