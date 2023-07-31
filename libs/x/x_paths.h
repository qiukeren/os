#ifndef _X_PATHS_H
#define _X_PATHS_H

#define VT_MASTER "/dev/tty0"          /* Virtual console master */
#define CONSOLE "/dev/console"         /* Logical system console */
#define SECURETTY "/etc/securetty"     /* List of root terminals */
#define SDALLOW "/etc/shutdown.allow"  /* Users allowed to shutdown */
#define INITTAB "/etc/inittab"         /* Location of inittab */
#define INITTABD "/etc/inittab.d"      /* Location of inittab.d directory */
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


#define X_PM_PACKAGELIST_DIR DEBUG_ROOT . "/etc/xpm.packages.d/"
#define X_PM_PACKAGEMANAGER DEBUG_ROOT . "/etc/xpm.ini"


#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void x_mkdir(char* file_path, mode_t mode);
void x_touch(const char* filename);

#endif