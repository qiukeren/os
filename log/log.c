#include "log.h"
#include <stdio.h>

FILE* logger_fp;

void LOG_INIT(char* __filename) {
    logger_fp = fopen(__filename, "a");
}
