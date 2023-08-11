#ifndef _X_REBOOT_H
#define _X_REBOOT_H

#include <linux/reboot.h>
#include <sys/reboot.h>
#include <unistd.h>

void x_poweroff();
void x_reboot();

#endif