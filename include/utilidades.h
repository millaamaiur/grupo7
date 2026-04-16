#ifndef UTILIDADES_H
#define UTILIDADES_H

#define SHA256_HASH_SIZE 65  // 64 caracteres hex + null terminator

// Convierte una contrasena a su hash SHA-256 en hexadecimal
// El resultado se guarda en 'output' (debe tener al menos SHA256_HASH_SIZE bytes)
void hash_password(const char *password, char *output);

// Verifica si una contrasena coincide con un hash almacenado
int verificar_password(const char *password, const char *hash almacenado);

#endif
