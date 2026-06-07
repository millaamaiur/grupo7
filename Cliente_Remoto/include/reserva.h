#ifndef RESERVA_H
#define RESERVA_H

class Reserva
{
private:
    int id_reserva;
    int id_soc;
    int id_instalacion;
    char *nombre_instalacion;
    char *fecha;
    char *hora_inicio;
    int duracion;
    char *estado;

public:
    Reserva();

    Reserva(int id_reserva,
            int id_soc,
            int id_instalacion,
            const char *nombre_instalacion,
            const char *fecha,
            const char *hora_inicio,
            int duracion,
            const char *estado);

    Reserva(const Reserva &otra);

    Reserva &operator=(const Reserva &otra);

    ~Reserva();

    int getIdReserva() const;
    int getIdSoc() const;
    int getIdInstalacion() const;
    const char *getNombreInstalacion() const;
    const char *getFecha() const;
    const char *getHoraInicio() const;
    int getDuracion() const;
    const char *getEstado() const;

    void setIdReserva(int id_reserva);
    void setIdSoc(int id_soc);
    void setIdInstalacion(int id_instalacion);
    void setNombreInstalacion(const char *nombre_instalacion);
    void setFecha(const char *fecha);
    void setHoraInicio(const char *hora_inicio);
    void setDuracion(int duracion);
    void setEstado(const char *estado);

    bool estaActiva() const;
    bool estaCancelada() const;

    void mostrar() const;
};

#endif