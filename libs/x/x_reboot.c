#include "x_reboot.h"

void x_poweroff() {
    sync();
    reboot(LINUX_REBOOT_CMD_POWER_OFF);
}

void x_reboot() {
    sync();
    reboot(RB_AUTOBOOT);
}