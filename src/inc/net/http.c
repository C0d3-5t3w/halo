#include "../../lib/net/http.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

vd serve_file(in client_fd, ch *filepath) {
    in fd = open(filepath, O_RDONLY);
    if (fd < 0) {
        ch *response = "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
        write(client_fd, response, strlen(response));
        return;
    }
    
    ch buffer[4096];
    ch *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    
    if (strstr(filepath, ".css")) {
        header = "HTTP/1.1 200 OK\r\nContent-Type: text/css\r\n\r\n";
    } else if (strstr(filepath, ".js")) {
        header = "HTTP/1.1 200 OK\r\nContent-Type: application/javascript\r\n\r\n";
    }
    
    write(client_fd, header, strlen(header));
    
    in bytes;
    while ((bytes = read(fd, buffer, sizeof(buffer))) > 0) {
        write(client_fd, buffer, bytes);
    }
    
    close(fd);
}

vd start_server(vd) {
    in server_fd, client_fd;
    struct sockaddr_in address;
    in addrlen = sizeof(address);
    ch buffer[4096] = {0};
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    
    in opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(DEFAULT_PORT);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    printf("Server successfully running on http://%s:%d\n", DEFAULT_ADDRESS, DEFAULT_PORT);

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Accept failed");
            continue;
        }
        
        read(client_fd, buffer, 4096);
        
        /* Extract URL path from GET request */
        ch url_path[MAX_PATH_LEN] = {0};
        ch *get_start = strstr(buffer, "GET ");
        if (get_start) {
            get_start += 4; /* Skip "GET " */
            ch *path_end = strchr(get_start, ' ');
            if (path_end) {
                in path_len = path_end - get_start;
                if (path_len < MAX_PATH_LEN) {
                    strncpy(url_path, get_start, path_len);
                    url_path[path_len] = '\0';
                }
            }
        }
        
        /* Look up file path from config */
        ch *filepath = get_file_for_path(url_path);
        if (!filepath) {
            /* Default to home page for root */
            if (strcmp(url_path, "/") == 0) {
                filepath = get_file_for_path("/");
            }
        }
        
        if (filepath) {
            serve_file(client_fd, filepath);
        } else {
            ch *response = "HTTP/1.1 404 Not Found\r\n\r\n<h1>404 Not Found</h1>";
            write(client_fd, response, strlen(response));
        }
        
        close(client_fd);
    }
    
    close(server_fd);
}
