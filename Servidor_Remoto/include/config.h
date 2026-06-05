#ifndef CONFIG_H
#define CONFIG_H
#define CONFIG_PATH "ficherosTexto/confic.txt"

typedef struct {
    char admin_user[128];
    char admin_pass[128];
    char db_path[256];
    char log_path[256];
    int puerto;
} Config;

Config load_config(const char *path);

#endif