#include "../../lib/config/settings.h"
#include <stdlib.h>
#include <string.h>

/* Global Variables */
in DEFAULT_PORT = 8080;
ch DEFAULT_ADDRESS[256] = "localhost";

vd SETTINGS(vd) {
    FILE *file = fopen(CONFIG_FILE, "r");
    if (!file) {
        printf("Warning: Could not open config.json, using defaults\n");
        printf("Configured address and port %s:%d\n", DEFAULT_ADDRESS, DEFAULT_PORT);
        return;
    }
    
    ch buffer[1024];
    size_t bytes_read = fread(buffer, 1, sizeof(buffer) - 1, file);
    buffer[bytes_read] = '\0';
    fclose(file);
    
    /* Simple JSON parsing for port */
    ch *port_str = strstr(buffer, "\"port\"");
    if (port_str) {
        port_str = strchr(port_str, ':');
        if (port_str) {
            DEFAULT_PORT = atoi(port_str + 1);
        }
    }
    
    /* Simple JSON parsing for address */
    ch *addr_str = strstr(buffer, "\"address\"");
    if (addr_str) {
        addr_str = strchr(addr_str, ':');
        if (addr_str) {
            addr_str = strchr(addr_str, '\"');
            if (addr_str) {
                addr_str++;
                ch *end = strchr(addr_str, '\"');
                if (end) {
                    size_t len = end - addr_str;
                    if (len < sizeof(DEFAULT_ADDRESS)) {
                        strncpy(DEFAULT_ADDRESS, addr_str, len);
                        DEFAULT_ADDRESS[len] = '\0';
                    }
                }
            }
        }
    }
    
    printf("Configured address and port %s:%d\n", DEFAULT_ADDRESS, DEFAULT_PORT);
}
