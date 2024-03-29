/* Public domain. */

#include <fcntl.h>
#include <sys/types.h>
#include "open.h"

int open_append(const char* fn) {
    return open(fn, O_WRONLY | O_NDELAY | O_APPEND | O_CREAT, 0600);
}
