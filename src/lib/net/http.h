#ifndef __HTTP_H
#define __HTTP_H

/*
 * @file http.h
 * @brief net/http header file
 * 
 * @details None.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "../config/settings.h"

/* Functions */

vd serve_file(in client_fd, ch *filepath);
vd start_server(vd);

#ifdef __cplusplus
}
#endif

#endif  /* __HTTP_H */
