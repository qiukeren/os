/* Public domain. */

#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>

main() {
    flock(0, LOCK_EX | LOCK_UN | LOCK_NB);
}
