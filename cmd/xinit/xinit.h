#ifndef _XINIT_H
#define _XINIT_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include <utmp.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

extern struct utmp utproto;

extern char* istrdup(const char* s);
extern void* imalloc(size_t size);

extern int isInittabLineEmpty(char* line);

extern void scanInittabLine(char* id,
                     char* rlevel,
                     char* action,
                     char* process,
                     char* line);

extern void read_inittab2(void);

/* Actions to be taken by init */
#define RESPAWN 1
#define WAIT 2
#define ONCE 3
#define BOOT 4
#define BOOTWAIT 5
#define POWERFAIL 6
#define POWERWAIT 7
#define POWEROKWAIT 8
#define CTRLALTDEL 9
#define OFF 10
#define ONDEMAND 11
#define INITDEFAULT 12
#define SYSINIT 13
#define POWERFAILNOW 14
#define KBREQUEST 15

#define _RESPAWN "respawn"
#define WAIT 2
#define ONCE 3
#define BOOT 4
#define BOOTWAIT 5
#define POWERFAIL 6
#define POWERWAIT 7
#define POWEROKWAIT 8
#define CTRLALTDEL 9
#define OFF 10
#define ONDEMAND 11
#define INITDEFAULT 12
#define _SYSINIT "sysinit"
#define POWERFAILNOW 14
#define KBREQUEST 15

/* Macro to see if this is a special action */
#define ISPOWER(i)                                                 \
    ((i) == POWERWAIT || (i) == POWERFAIL || (i) == POWEROKWAIT || \
     (i) == POWERFAILNOW || (i) == CTRLALTDEL)


// static struct actions {
//     char* name;
//     int act;
// } actions[] = {
//     {"respawn", RESPAWN},
//     {"wait", WAIT},
//     {"once", ONCE},
//     {"boot", BOOT},
//     {"bootwait", BOOTWAIT},
//     {"powerfail", POWERFAIL},
//     {"powerfailnow", POWERFAILNOW},
//     {"powerwait", POWERWAIT},
//     {"powerokwait", POWEROKWAIT},
//     {"ctrlaltdel", CTRLALTDEL},
//     {"off", OFF},
//     {"ondemand", ONDEMAND},
//     {"initdefault", INITDEFAULT},
//     {"sysinit", SYSINIT},
//     {"kbrequest", KBREQUEST},
//     {NULL, 0},
// };


typedef struct _child1_ {
    int flags;            /* Status of this entry */
    int exstat;           /* Exit status of process */
    int pid;              /* Pid of this process */
    time_t tm;            /* When respawned last */
    int count;            /* Times respawned in the last 2 minutes */
    char id[8];           /* Inittab id (must be unique) */
    char rlevel[12];      /* run levels */
    char action[33];           /* what to do (see list below) */
    char process[128];    /* The command line */
    struct _child1_* prior;  /* New entry (after inittab re-read) */
    struct _child1_* next; /* For the linked list */
} XINIT_ITEM;

static XINIT_ITEM* initList = NULL;


#define VT_MASTER "/dev/tty0"          /* Virtual console master */
#define CONSOLE "/dev/console"         /* Logical system console */
#define SECURETTY "/etc/securetty"     /* List of root terminals */
#define SDALLOW "/etc/shutdown.allow"  /* Users allowed to shutdown */
#define INITTAB "inittab"              /* Location of inittab */
#define INIT "/sbin/init"              /* Location of init itself. */
#define NOLOGIN "/etc/nologin"         /* Stop user logging in. */
#define FASTBOOT "/fastboot"           /* Enable fast boot. */
#define FORCEFSCK "/forcefsck"         /* Force fsck on boot */
#define SDPID "/var/run/shutdown.pid"  /* PID of shutdown program */
#define SHELL "/bin/sh"                /* Default shell */
#define SULOGIN "/sbin/sulogin"        /* Sulogin */
#define INITSCRIPT "/etc/initscript"   /* Initscript. */
#define PWRSTAT_OLD "/etc/powerstatus" /* COMPAT: SIGPWR reason (OK/BAD) */
#define PWRSTAT "/var/run/powerstatus" /* COMPAT: SIGPWR reason (OK/BAD) */
#define RUNLEVEL_LOG                                        \
    "/var/run/runlevel" /* neutral place to store run level \
                         */

#ifdef __cplusplus
}
#endif

#endif
