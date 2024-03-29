/* Quick Shell's main header file */
/*
 * Compiler Options:
 * -DGNU 	: The user interface uses GNU Readline
 * -DTINY 	: The user interface just uses fgets() (aka doesnt handle line
 *editing) <none>	: The user interface uses linenoise library (see
 *https://github.com/antirez/linenoise) -DNO_COLOR	: Disables color for the
 *prompt (note does not affect readline nor linenoise)
 */

#ifndef _using_ui_h
#define _using_ui_h

/* Standard C Libs */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Custom Libs */
#include "safestring.h"

#include "log.h"

#if defined(linux) || defined(__linux__) || defined(__linux)
/* Standard Linux Libs */
#include "linux.h"
#else
#pragma GCC warning \
    "Operating system is not UNIX based, system calls may not work"
// eventually check if _WIN32, then include libs/windows.h
#include "linux.h"

#endif

#include "hints.h"
#include "linenoise.h"

/* Commands */
#include "c.h"
#include "help.h"

#define MAX_USER_INPUT 1024  // how much data can be typed in the terminal
#define BAD_COMMAND \
    "qsh : Command not found."  // What is returned when the command isnt found
#define MAX_ARGS 4096           // POSIX smallest ammount of command line args
#define VAR_SIZE 255            // standard size of vars in ui.c

#ifdef DEBUGGING
#define DEBUG 1
#else
#define DEBUG 0
#endif

/* Foreground Colors */
#ifndef NO_COLOR
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"
#else
#define RED ""
#define GREEN ""
#define YELLOW ""
#define BLUE ""
#define MAGENTA ""
#define CYAN ""
#define WHITE ""
#define RESET ""
#endif

#define DEFAULT_PROMPT "=> "

static void interp(char[]);  // checks if commands are valid, then runs them
static int find(
    const char[],
    const int,
    char*[]);  // checks if a file exists, puts its location in *location
static int handle_var(char**);

static void run(const char*, char*, char*);

static int call(const char* location, char* program, char* argv[], int argc);

static int isFile(const char* path);  // checks if the path leads to a file
int check_special(const char*);

void stopgap(const char*);  // calls system shell [TEMP]
// int get_hist(char*, size_t);
char* has_home(char[]);

int ui(void);

#endif
