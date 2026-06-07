#ifndef INSTALACION_H
#define INSTALACION_H

class Instalacion
{
private:
    int id_instalacion;
    char *nombre;
    char *tipo;
    int aforo_maximo;
    double precio_hora;
    char *estado;

public:
    Instalacion();

    Instalacion(int id_instalacion,
                const char *nombre,
                const char *tipo,
                int aforo_maximo,
                double precio_hora,
                const char *estado);

    Instalacion(const Instalacion &otra);

    Instalacion &operator=(const Instalacion &otra);

    ~Instalacion();

    int getIdInstalacion() const;
    const char *getNombre() const;
    const char *getTipo() const;
    int getAforoMaximo() const;
    double getPrecioHora() const;
    const char *getEstado() const;

    void setIdInstalacion(int id_instalacion);
    void setNombre(const char *nombre);
    void setTipo(const char *tipo);
    void setAforoMaximo(int aforo_maximo);
    void setPrecioHora(double precio_hora);
    void setEstado(const char *estado);

    bool estaActiva() const;
    bool estaEnMantenimiento() const;

    void mostrar() const;
};

#endif