#include "config.h"
#include <stdio.h>
#include <string.h>

Config load_config(const char *path) {
    Config config = {0};
    FILE *f = fopen(path, "r");
    if (!f) {
        perror("Error abriendo config");
        return config;
    }

    char line[512];
    while (fgets(line, sizeof(line), f)) {
        if (line[0] == '#' || line[0] == '\n') continue;

        char key[128], value[256];
        if (sscanf(line, "%127[^=]= %255s", key, value) != 2) continue;

        char *k = key;
        while (*k == ' ') k++;
        char *end = k + strlen(k) - 1;
        while (end > k && *end == ' ') *end-- = '\0';

        if (strcmp(k, "ADMIN_USER") == 0) strncpy(config.admin_user, value, 127);
        else if (strcmp(k, "ADMIN_PASS") == 0) strncpy(config.admin_pass, value, 127);
        else if (strcmp(k, "DB_PATH") == 0) strncpy(config.db_path, value, 255);
        else if (strcmp(k, "LOG_PATH") == 0) strncpy(config.log_path, value, 255);
    }

    fclose(f);
    return config;
}