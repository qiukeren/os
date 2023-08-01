#include "x_command.h"

bool x_command_check(char* command) {
    int status = system(command);
    return status == 0;
}