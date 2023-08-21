#ifndef _X_PACKAGE_H
#define _X_PACKAGE_H 1

#include <stdint.h>

#define XOS_PACKAGE_TYPE_MAGIC uint32_t(0x275BCD15)
#define XOS_PACKAGE_TYPE_META uint32_t(0x00000001)
#define XOS_PACKAGE_TYPE_FILE uint32_t(0x00000002)
#define XOS_PACKAGE_TYPE_INSTANT_SCRIPT uint32_t(0x00000003)

struct XPM_SIZE_HEADER {
    uint32_t type;
    uint64_t size;
};

struct XPM_META_CONTENT_VERSION {
    uint32_t majorVersion;
    uint32_t minorVersion;
    uint32_t revision;
};

struct XPM_META_CONTENT {
    XPM_META_CONTENT_VERSION version;

    uint32_t nameLen;
    char[] name;
    uint32_t descSize;
    char[] desc;
};

struct XPM_FILE_CONTENT_STAT {
    //	//total 4 * 3 = 12 Byte
    uint32_t Stat;  // uint32
    uint32_t Uid;
    uint32_t Gid;

    uint64_t AtimSec;
    uint64_t AtimNsec;
    uint64_t MtimSec;
    uint64_t MtimNsec;
    uint64_t CtimSec;
    uint64_t CtimNsec;
};

struct XPM_FILE_CONTENT {
    XPM_FILE_CONTENT_STAT FileMeta;
    char[33] md5;

    uint32_t nameLen;
    char[] name;
    uint64_t size;
    char[] content;
};

#endif