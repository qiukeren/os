#include <sys/reboot.h>
#include <unistd.h>

/* sysdep: +std reboot */

int reboot_system(int what) {
    return (reboot(what));
}
