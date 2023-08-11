#include <gtest/gtest.h>
#include <utmp.h>
#include "init.h"
#include "x.h"

/*
 *	Sleep a number of milliseconds.
 *
 *	This only works correctly because Linux select updates
 *	the elapsed time in the struct timeval passed to select!
 */
static void do_msleep(int msec) {
    struct timeval tv;

    tv.tv_sec = msec / 1000;
    tv.tv_usec = (msec % 1000) * 1000;

    while (select(0, NULL, NULL, NULL, &tv) < 0 && errno == EINTR)
        ;
}

/*
 *	Non-failing allocation routines (init cannot fail).
 */
static void* imalloc(size_t size) {
    void* m;

    while ((m = malloc(size)) == NULL) {
        do_msleep(5000);
    }
    memset(m, 0, size);
    return m;
}

static char* istrdup(const char* s) {
    void* m;
    int l;

    l = strlen(s) + 1;
    m = imalloc(l);
    memcpy(m, s, l);
    return (char*)m;
}

TEST(test_init, commandEqual) {
    char* cmd = "ls > /dev/null 2>&1";
    char* cmd2 = istrdup(cmd);
    ASSERT_STREQ(cmd, cmd2);
}

static int isInittabLineEmpty(char* line) {
    return strlen(line) == 0 || line[0] == '#' || line[0] == '\n';
}

static void scanInittabLine(char* id,
                            char* rlevel,
                            char* action,
                            char* process,
                            char* line) {
    id = strsep(&line, ":");
    rlevel = strsep(&line, ":");
    action = strsep(&line, ":");
    process = strsep(&line, "\n");
}

struct utmp utproto;

static void read_inittab2(void) {
    FILE* fp;
    int bufferLength = 256;
    char buffer[bufferLength];
    char* line;
    char err[255];

    fp = fopen("init/inittab", "r");
    if (fp == NULL) {
        printf("%s", "No inittab file found");
    }

    while (fgets(buffer, bufferLength, fp)) {
        line = buffer;
        // printf("%d\n", strlen(line));
        if (isInittabLineEmpty(line)) {
            continue;
        } else {
            char *id, *rlevel, *action, *process;
            id = strsep(&line, ":");
            rlevel = strsep(&line, ":");
            action = strsep(&line, ":");
            process = strsep(&line, "\n");

            /*
             *	Check if syntax is OK. Be very verbose here, to
             *	avoid newbie postings on comp.os.linux.setup :)
             */
            err[0] = 0;
            if (!id || !*id) {
                strcpy(err, "missing id field");
            }
            if (!rlevel) {
                strcpy(err, "missing runlevel field");
            }
            if (!process) {
                strcpy(err, "missing process field");
            }
            if (!action || !*action) {
                strcpy(err, "missing action field");
            }
            if (id && strlen(id) > sizeof(utproto.ut_id)) {
                sprintf(err, "id field too long (max %d characters)",
                        (int)sizeof(utproto.ut_id));
            }
            if (rlevel && strlen(rlevel) > 11) {
                strcpy(err, "rlevel field too long (max 11 characters)");
            }
            if (process && strlen(process) > 127) {
                strcpy(err, "process field too long (max 127 characters)");
            }
            if (action && strlen(action) > 32) {
                strcpy(err, "action field too long");
            }
            ASSERT_TRUE(err[0] != 0);
            if (err[0] != 0) {
                continue;
            }
        }
    }

    // while ((read = getline(&line, &len, fp)) != -1) {
    //     // printf("ORIGIN %s", line);
    //     printf("%d\n",strlen(line));
    //     if (isInittabLineEmpty(line)) {
    //         continue;
    //     } else {
    //         char *id, *rlevel, *action, *process; /* Fields of a line */
    //         id = strsep(&line, ":");
    //         rlevel = strsep(&line, ":");
    //         action = strsep(&line, ":");
    //         process = strsep(&line, "\n");
    //         printf("REPEAT %s:%s:%s:%s\n", id, rlevel, action, process);
    //     }
    // }

    if (fp != NULL) {
        fclose(fp);
    }
}

TEST(test_init, readInittab2) {
    read_inittab2();
}