#ifndef USUARIO_H
#define USUARIO_H

class Usuario
{
private:
    int id;
    char *user;
    char *rol;
    char *fecha_nac;
    char *fecha_alta;
    int id_suscrip;

public:
    Usuario();

    Usuario(int id,
            const char *user,
            const char *rol,
            const char *fecha_nac,
            const char *fecha_alta,
            int id_suscrip);

    Usuario(const Usuario &otro);

    Usuario &operator=(const Usuario &otro);

    ~Usuario();

    int getId() const;
    const char *getUser() const;
    const char *getRol() const;
    const char *getFechaNac() const;
    const char *getFechaAlta() const;
    int getIdSuscrip() const;

    void setId(int id);
    void setUser(const char *user);
    void setRol(const char *rol);
    void setFechaNac(const char *fecha_nac);
    void setFechaAlta(const char *fecha_alta);
    void setIdSuscrip(int id_suscrip);

    bool esAdmin() const;
    bool esSocio() const;

    void mostrar() const;
};

#endif