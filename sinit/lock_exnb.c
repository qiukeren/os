/* Public domain. */

#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include "hasflock.h"
#include "lock.h"

#ifdef HASFLOCK

int lock_exnb(int fd) {
    return flock(fd, LOCK_EX | LOCK_NB);
}

#else
int lock_exnb(int fd) {
    return lockf(fd, 2, 0);
}
#endif
