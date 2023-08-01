#include <x_mount.h>

void x_init_mount() {
#ifndef __APPLE__
    mount("sys", "/sys", "sysfs", 0, "");
    mount("proc", "/proc", "proc", 0, "");
    mount("dev", "/dev", "devtmpfs", 0, "");
#ifdef _DEBUG
    x_debug_print_file_content("/proc/mounts");
#endif
#endif
}
