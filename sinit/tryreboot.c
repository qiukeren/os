#include <sys/reboot.h>
#include <unistd.h>

int main(void) {
    return (reboot(0));
}
