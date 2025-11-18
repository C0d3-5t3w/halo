#ifndef __ROOT_H
#define __ROOT_H

/*
 * @file root.h
 * @brief root header file
 * 
 * @details None.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include "lib/config/settings.h"
#include "lib/net/http.h"

/* Http */
vd serve_file(in client_fd, ch *filepath);
vd start_server(vd);

/* Settings */
vd SETTINGS(vd);

#ifdef __cplusplus
}
#endif

#endif  /* __ROOT_H */
