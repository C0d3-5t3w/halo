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

/* Global Variables */

extern in DEFAULT_PORT;
extern ch DEFAULT_ADDRESS[256];

/* Functions */

vd SETTINGS(vd);

#ifdef __cplusplus
}
#endif

#endif  /* __SETTINGS_H */
