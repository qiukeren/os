#include <stdio.h>
#include "sqlite3.h"
#include "zlib.h"

int main() {
    printf("sqlite:%s\n", SQLITE_VERSION);
    printf("zlib:%s\n", ZLIB_VERSION);
}