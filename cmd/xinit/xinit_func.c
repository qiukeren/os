#include "xinit.h"

extern XINIT_ITEM* initList;

void* imalloc(size_t size) {
    void* m;
    m = malloc(size);

    memset(m, 0, size);
    return m;
}

char* istrdup(const char* s) {
    char* m;
    int l;

    l = strlen(s) + 1;
    m = imalloc(l);
    memcpy(m, s, l);
    return m;
}

int isInittabLineEmpty(char* line) {
    return strlen(line) == 0 || line[0] == '#' || line[0] == '\n';
}

void read_inittab2(void) {
    FILE* fp;                   // inittab file
    int bufferLength = 256;     // inittab line buffer size
    char buffer[bufferLength];  // inittab content per line buffer
    char* line;                 // inittab content per line buffer
    char err[255];              // return error

    char *id, *rlevel, *action, *process;

    int f;  // 计数器 但是不知道计数什么

    XINIT_ITEM *ch, *old, *i; /* Pointers to CHILD structure */
    XINIT_ITEM* head = NULL;  /* Head of linked list */

    fp = fopen("inittab", "r");
    if (fp == NULL) {
        printf("%s", "No inittab file found");
    }

    while (fgets(buffer, bufferLength, fp)) {
        line = buffer;
        printf("%d %s", strlen(line), line);
        if (isInittabLineEmpty(line)) {
            continue;
        } else {
            id = strsep(&line, ":");
            rlevel = strsep(&line, ":");
            action = strsep(&line, ":");
            process = strsep(&line, "\n");
            printf("REPEAT %s:%s:%s:%s\n", id, rlevel, action, process);

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
            if (err[0] != 0) {
                printf("ERROR %s:%s:%s:%s %s\n", id, rlevel, action, process,
                       err);
                continue;
            }

            printf("SUCCESS  %s:%s:%s:%s\n", id, rlevel, action, process);

            ch = malloc(sizeof(XINIT_ITEM));

            strncpy(ch->id, id, sizeof(utproto.ut_id) + 1);
            strncpy(ch->action, action, sizeof(ch->action) - 1);
            strncpy(ch->process, process, sizeof(ch->process) - 1);
            strncpy(ch->rlevel, rlevel, sizeof(ch->rlevel) - 1);

            if (!head) {
                head = ch;
            }

            if (!old) {
                old->next = ch;
            }
        }
        if (fp) {
            fclose(fp);
        }
        sigset_t nmask, omask; /* For blocking SIGCHLD. */
        sigemptyset(&nmask);
        sigaddset(&nmask, SIGCHLD);
        sigprocmask(SIG_BLOCK, &nmask, &omask);
        
        sigprocmask(SIG_SETMASK, &omask, NULL);

        initList = head;
    }
}