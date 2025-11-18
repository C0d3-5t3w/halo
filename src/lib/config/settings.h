#ifndef __SETTINGS_H
#define __SETTINGS_H

/*
 * @file settings.h
 * @brief config/settings header file
 * 
 * @details None.
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

/* Types */

typedef int32_t fn;
typedef int in;
typedef void vd;
typedef char ch;

/* Defines */

#define CONFIG_FILE "config.json"
#define MAX_ROUTES 100
#define MAX_PATH_LEN 512

/* Structures */

typedef struct {
    ch url_path[MAX_PATH_LEN];
    ch file_path[MAX_PATH_LEN];
} Route;

/* Global Variables */

extern in DEFAULT_PORT;
extern ch DEFAULT_ADDRESS[256];
extern Route ROUTES[MAX_ROUTES];
extern in ROUTE_COUNT;

/* Functions */

vd SETTINGS(vd);
ch* get_file_for_path(ch *url_path);

#ifdef __cplusplus
}
#endif

#endif  /* __SETTINGS_H */
