/* Public domain. */

#include <sys/stat.h>
#include <sys/types.h>

void main() {
    mkfifo("temp-trymkffo", 0);
}
