#include "../../lib/config/settings.h"
#include <stdlib.h>
#include <string.h>

/* Global Variables */
in DEFAULT_PORT = 8080;
ch DEFAULT_ADDRESS[256] = "localhost";
Route ROUTES[MAX_ROUTES];
in ROUTE_COUNT = 0;

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
    
    /* Parse pages section */
    ch *pages_str = strstr(buffer, "\"pages\"");
    if (pages_str) {
        ch *pages_start = strchr(pages_str, '{');
        if (pages_start) {
            ch *current = pages_start + 1;
            while (*current && *current != '}') {
                /* Find key */
                ch *key_start = strchr(current, '"');
                if (!key_start || key_start >= strchr(pages_start, '}')) break;
                key_start++;
                ch *key_end = strchr(key_start, '"');
                if (!key_end) break;
                
                /* Find value */
                ch *val_start = strchr(key_end, '"');
                if (!val_start) break;
                val_start++;
                ch *val_end = strchr(val_start, '"');
                if (!val_end) break;
                
                /* Build route - pages map to root paths */
                if (ROUTE_COUNT < MAX_ROUTES) {
                    if (strncmp(key_start, "home", key_end - key_start) == 0) {
                        strcpy(ROUTES[ROUTE_COUNT].url_path, "/");
                    } else {
                        snprintf(ROUTES[ROUTE_COUNT].url_path, MAX_PATH_LEN, "/%.*s", (in)(key_end - key_start), key_start);
                    }
                    snprintf(ROUTES[ROUTE_COUNT].file_path, MAX_PATH_LEN, "%.*s", (in)(val_end - val_start), val_start);
                    ROUTE_COUNT++;
                }
                
                current = val_end + 1;
            }
        }
    }
    
    /* Parse CSS assets */
    ch *css_str = strstr(buffer, "\"css\"");
    if (css_str) {
        ch *css_start = strchr(css_str, '{');
        if (css_start) {
            ch *current = css_start + 1;
            while (*current && *current != '}') {
                ch *key_start = strchr(current, '"');
                if (!key_start || key_start >= strchr(css_start, '}')) break;
                key_start++;
                ch *key_end = strchr(key_start, '"');
                if (!key_end) break;
                
                ch *val_start = strchr(key_end, '"');
                if (!val_start) break;
                val_start++;
                ch *val_end = strchr(val_start, '"');
                if (!val_end) break;
                
                if (ROUTE_COUNT < MAX_ROUTES) {
                    snprintf(ROUTES[ROUTE_COUNT].url_path, MAX_PATH_LEN, "/css/%.*s.css", (in)(key_end - key_start), key_start);
                    snprintf(ROUTES[ROUTE_COUNT].file_path, MAX_PATH_LEN, "%.*s", (in)(val_end - val_start), val_start);
                    ROUTE_COUNT++;
                }
                
                current = val_end + 1;
            }
        }
    }
    
    /* Parse JS assets */
    ch *js_str = strstr(buffer, "\"js\"");
    if (js_str) {
        ch *js_start = strchr(js_str, '{');
        if (js_start) {
            ch *current = js_start + 1;
            while (*current && *current != '}') {
                ch *key_start = strchr(current, '"');
                if (!key_start || key_start >= strchr(js_start, '}')) break;
                key_start++;
                ch *key_end = strchr(key_start, '"');
                if (!key_end) break;
                
                ch *val_start = strchr(key_end, '"');
                if (!val_start) break;
                val_start++;
                ch *val_end = strchr(val_start, '"');
                if (!val_end) break;
                
                if (ROUTE_COUNT < MAX_ROUTES) {
                    snprintf(ROUTES[ROUTE_COUNT].url_path, MAX_PATH_LEN, "/js/%.*s.js", (in)(key_end - key_start), key_start);
                    snprintf(ROUTES[ROUTE_COUNT].file_path, MAX_PATH_LEN, "%.*s", (in)(val_end - val_start), val_start);
                    ROUTE_COUNT++;
                }
                
                current = val_end + 1;
            }
        }
    }
    
    /* Parse image assets */
    ch *images_str = strstr(buffer, "\"images\"");
    if (images_str) {
        ch *img_start = strchr(images_str, '{');
        if (img_start) {
            ch *current = img_start + 1;
            while (*current && *current != '}') {
                ch *key_start = strchr(current, '"');
                if (!key_start || key_start >= strchr(img_start, '}')) break;
                key_start++;
                ch *key_end = strchr(key_start, '"');
                if (!key_end) break;
                
                ch *val_start = strchr(key_end, '"');
                if (!val_start) break;
                val_start++;
                ch *val_end = strchr(val_start, '"');
                if (!val_end) break;
                
                if (ROUTE_COUNT < MAX_ROUTES) {
                    /* Extract file extension from the file path */
                    ch *ext = strrchr(val_start, '.');
                    if (ext && ext < val_end) {
                        snprintf(ROUTES[ROUTE_COUNT].url_path, MAX_PATH_LEN, "/images/%.*s%.*s", 
                                (in)(key_end - key_start), key_start,
                                (in)(val_end - ext), ext);
                    } else {
                        snprintf(ROUTES[ROUTE_COUNT].url_path, MAX_PATH_LEN, "/images/%.*s", (in)(key_end - key_start), key_start);
                    }
                    snprintf(ROUTES[ROUTE_COUNT].file_path, MAX_PATH_LEN, "%.*s", (in)(val_end - val_start), val_start);
                    ROUTE_COUNT++;
                }
                
                current = val_end + 1;
            }
        }
    }
    
    printf("Configured address and port %s:%d\n", DEFAULT_ADDRESS, DEFAULT_PORT);
    printf("Loaded %d routes from config\n", ROUTE_COUNT);
}

ch* get_file_for_path(ch *url_path) {
    for (in i = 0; i < ROUTE_COUNT; i++) {
        if (strcmp(ROUTES[i].url_path, url_path) == 0) {
            return ROUTES[i].file_path;
        }
    }
    return NULL;
}
