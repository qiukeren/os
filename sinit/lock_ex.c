/* Public domain. */

#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include "hasflock.h"
#include "lock.h"

#ifdef HASFLOCK

int lock_ex(int fd) {
    return flock(fd, LOCK_EX);
}

#else
int lock_ex(int fd) {
    return lockf(fd, 1, 0);
}
#endif
