#include "../include/Reserva.h"
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

Reserva::Reserva()
{
    this->id_reserva = -1;
    this->id_soc = -1;
    this->id_instalacion = -1;
    this->nombre_instalacion = copiarCadena("");
    this->fecha = copiarCadena("");
    this->hora_inicio = copiarCadena("");
    this->duracion = 0;
    this->estado = copiarCadena("");
}

Reserva::Reserva(int id_reserva, int id_soc, int id_instalacion, const char* nombre_instalacion, const char* fecha, const char* hora_inicio, int duracion, const char* estado)
{
    this->id_reserva = id_reserva;
    this->id_soc = id_soc;
    this->id_instalacion = id_instalacion;
    this->nombre_instalacion = copiarCadena(nombre_instalacion);
    this->fecha = copiarCadena(fecha);
    this->hora_inicio = copiarCadena(hora_inicio);
    this->duracion = duracion;
    this->estado = copiarCadena(estado);
}

Reserva::Reserva(const Reserva& otra)
{
    this->id_reserva = otra.id_reserva;
    this->id_soc = otra.id_soc;
    this->id_instalacion = otra.id_instalacion;
    this->nombre_instalacion = copiarCadena(otra.nombre_instalacion);
    this->fecha = copiarCadena(otra.fecha);
    this->hora_inicio = copiarCadena(otra.hora_inicio);
    this->duracion = otra.duracion;
    this->estado = copiarCadena(otra.estado);
}

Reserva& Reserva::operator=(const Reserva& otra)
{
    if (this != &otra)
    {
        delete[] this->nombre_instalacion;
        delete[] this->fecha;
        delete[] this->hora_inicio;
        delete[] this->estado;

        this->id_reserva = otra.id_reserva;
        this->id_soc = otra.id_soc;
        this->id_instalacion = otra.id_instalacion;
        this->nombre_instalacion = copiarCadena(otra.nombre_instalacion);
        this->fecha = copiarCadena(otra.fecha);
        this->hora_inicio = copiarCadena(otra.hora_inicio);
        this->duracion = otra.duracion;
        this->estado = copiarCadena(otra.estado);
    }

    return *this;
}

Reserva::~Reserva()
{
    delete[] this->nombre_instalacion;
    delete[] this->fecha;
    delete[] this->hora_inicio;
    delete[] this->estado;
}

int Reserva::getIdReserva() const
{
    return this->id_reserva;
}

int Reserva::getIdSoc() const
{
    return this->id_soc;
}

int Reserva::getIdInstalacion() const
{
    return this->id_instalacion;
}

const char* Reserva::getNombreInstalacion() const
{
    return this->nombre_instalacion;
}

const char* Reserva::getFecha() const
{
    return this->fecha;
}

const char* Reserva::getHoraInicio() const
{
    return this->hora_inicio;
}

int Reserva::getDuracion() const
{
    return this->duracion;
}

const char* Reserva::getEstado() const
{
    return this->estado;
}

void Reserva::setIdReserva(int id_reserva)
{
    this->id_reserva = id_reserva;
}

void Reserva::setIdSoc(int id_soc)
{
    this->id_soc = id_soc;
}

void Reserva::setIdInstalacion(int id_instalacion)
{
    this->id_instalacion = id_instalacion;
}

void Reserva::setNombreInstalacion(const char* nombre_instalacion)
{
    delete[] this->nombre_instalacion;
    this->nombre_instalacion = copiarCadena(nombre_instalacion);
}

void Reserva::setFecha(const char* fecha)
{
    delete[] this->fecha;
    this->fecha = copiarCadena(fecha);
}

void Reserva::setHoraInicio(const char* hora_inicio)
{
    delete[] this->hora_inicio;
    this->hora_inicio = copiarCadena(hora_inicio);
}

void Reserva::setDuracion(int duracion)
{
    this->duracion = duracion;
}

void Reserva::setEstado(const char* estado)
{
    delete[] this->estado;
    this->estado = copiarCadena(estado);
}

bool Reserva::estaActiva() const
{
    return strcmp(this->estado, "activa") == 0;
}

bool Reserva::estaCancelada() const
{
    return strcmp(this->estado, "cancelada") == 0;
}

void Reserva::mostrar() const
{
    cout << "ID reserva: " << this->id_reserva << endl;
    cout << "ID socio: " << this->id_soc << endl;
    cout << "ID instalacion: " << this->id_instalacion << endl;
    cout << "Nombre instalacion: " << this->nombre_instalacion << endl;
    cout << "Fecha: " << this->fecha << endl;
    cout << "Hora inicio: " << this->hora_inicio << endl;
    cout << "Duracion: " << this->duracion << " minutos" << endl;
    cout << "Estado: " << this->estado << endl;
}