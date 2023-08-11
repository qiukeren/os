/* Public domain. */

#include "coe.h"
#include <fcntl.h>

int coe(int fd) {
    return fcntl(fd, F_SETFD, 1);
}
