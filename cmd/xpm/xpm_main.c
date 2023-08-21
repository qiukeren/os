#include <stdbool.h>
#include <stdlib.h>
#include "xlog.h"
#include "xpm.h"

#define LOG_LEVEL DEBUG_LEVEL

/* NPK partition types */
#define NPK_PART_PKG_INFO 0x01  /* Package information: name, ver, etc. */
#define NPK_PART_PKG_DESC 0x02  /* Package description */
#define NPK_PART_FILES 0x04     /* Files container */
#define NPK_PART_INSTALL 0x07   /* Install script */
#define NPK_PART_UNINSTALL 0x08 /* Uninstall script */
#define NPK_PART_PKG_ARCH 0x10  /* Package architecture (e.g. i386) */
#define NPK_PART_PKG_MAIN 0x12  /* Main package info: name, version, etc. */
#define NPK_PART_SQUASHFS 0x15  /* SquashFS image */
#define NPK_PART_DIGEST 0x17    /* Digest */
#define NPK_PART_RELTYPE 0x18   /* Release type (e.g. stable, bugfix) */

int proc_main(uint8_t* base);

struct map_entry {
    unsigned id;
    char* name;
};

/* List of NPK partition types names */
static const struct map_entry part_types_names[] = {
    {0, "Unknown"},
    {NPK_PART_PKG_INFO, "Package information"},
    {NPK_PART_PKG_DESC, "Package description"},
    {NPK_PART_FILES, "Files container"},
    {NPK_PART_INSTALL, "Install script"},
    {NPK_PART_UNINSTALL, "Uninstall script"},
    {NPK_PART_PKG_ARCH, "Package architecture"},
    {NPK_PART_PKG_MAIN, "Main package information"},
    {NPK_PART_SQUASHFS, "Squash filesystem image"},
    {NPK_PART_DIGEST, "Digest"},
    {NPK_PART_RELTYPE, "Release type"},
    {0, NULL},
};

const char* file = "";
const char* act = "";
int file_size;
uint8_t* base;

/* Main NPK file header */
struct npk_main_hdr {
    uint32_t sign;      /* File magic signature */
    uint32_t remain_sz; /* Remain file size */
} __attribute__((packed));

struct npk_part_hdr {
    uint16_t type; /* Partition type (see above) */
    uint32_t size; /* Partition size */
} __attribute__((packed));

static char* array2str(const uint8_t* array, const unsigned len) {
    static char buf[4 + /* N= */ 24 * 3 + 1] = {
        'h', 'e', 'x', ':'}; /* Output buffer for N hex items */
    char* p = buf + 4;
    unsigned i;

    for (i = 0; i < len; ++i) {
        p += sprintf(p, "%02X ", array[i]);
        if (((buf + sizeof(buf) - p) <= 4) && (len - i) > 2) {
            strcpy(p, "...");
            break;
        }
    }
    if (len == i)
        *(--p) = '\0';

    return buf;
}

static const char* type2name(const struct map_entry* map, const unsigned type) {
    const struct map_entry* e = map;

    while (e->name != NULL) {
        if (e->id == type)
            return e->name;
        ++e;
    }

    return map->name;
}

/* Print main NPK file header */
static void proc_main_print_main_hdr(const struct npk_main_hdr* hdr) {
    printf("\n[Main header]\n");
    printf("Signature : %s\n",
           array2str((uint8_t*)&hdr->sign, sizeof(hdr->sign)));
    printf("Remain siz: %u\n", hdr->remain_sz);
}

/* Print NPK file partition header */
static void proc_main_print_part_hdr(const struct npk_part_hdr* hdr) {
    printf("\n[Partition header]\n");
    printf("Type: %u (%s)\n", hdr->type,
           type2name(part_types_names, hdr->type));
    printf("Size: %u\n", hdr->size);
}

int main(int argc, char* argv[]) {
    x_fs_stats file_stat;

    const struct cflag options[] = {
        CFLAG(string, "file", 'f', &file, "File Name"),
        CFLAG(string, "act", 'a', &file, "Act Name"), CFLAG_HELP, CFLAG_END};

    cflag_apply(options, "[options] --url URL", &argc, &argv);

    if (strlen(file) == 0) {
        LOG_INFO("must specific a file with -f");
        x_sys_exit(1);
    }

    FILE* f = x_fs_fopen(file, X_FS_OPEN_READ);

    if (f == NULL) {
        LOG_INFO("file %s not exist ", file);
        x_fs_error(file);
        x_sys_exit(1);
    }

    int fd = fileno(f);

    if (x_fs_fstat(f, &file_stat) != 0) {
        LOG_DEBUG("stat file %s error %s", file, strerror(errno));
        x_fs_error(file);
        x_sys_exit(1);
    }

    file_size = file_stat.st_size;

    LOG_INFO("file %s size is %d", file, file_size);

    base = mmap(0, file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == base) {
        LOG_ERROR("mmap error %s", file, strerror(errno));
        close(fd);
        return 1;
    }
    proc_main(base);

    if (munmap(base, file_size) == -1) {
        perror("munmap");
        return 1;
    }
}

int proc_main(uint8_t* base) {
    const struct npk_main_hdr* mhdr;
    const struct npk_part_hdr* phdr;
    mhdr = (struct npk_main_hdr*)base;
    uint8_t* ptr = base;

    LOG_DEBUG("mhdr sign host endian (%08X) remain size %d", mhdr->sign,
              mhdr->remain_sz);
    LOG_DEBUG("want magic %08X actual magic %08X", XPM_MAGIC,
              ntohl(mhdr->sign));

    if (ntohl(mhdr->sign) != XPM_MAGIC) {
        LOG_ERROR("Error: Invalid file signature should be %08X.\n", XPM_MAGIC);
        return -EINVAL;
    }
    LOG_INFO("READ FILE %s SUCCESS", file);

    if (mhdr->remain_sz >
        (file_size - sizeof(mhdr->sign) - sizeof(mhdr->remain_sz)))
        fprintf(stderr,
                "Warning: remain size header field great than actual file "
                "size. File corrupted?");
    else if (mhdr->remain_sz <
             (file_size - sizeof(mhdr->sign) - sizeof(mhdr->remain_sz)))
        fprintf(stderr,
                "Warning: remain size header field less than actual file size. "
                "File corrupted?");

    proc_main_print_main_hdr(mhdr);
    ptr += sizeof(struct npk_main_hdr);

#define REMAIN (file_size - (ptr - base))
    LOG_INFO("remain %d", REMAIN);

    /* Process file partitions */
    while (REMAIN != 0) {
        if (REMAIN < sizeof(struct npk_part_hdr)) {
            fprintf(
                stderr,
                "Error: remain file chunk not enogh for partition header.\n");
            return -EINVAL;
        }
        phdr = (struct npk_part_hdr*)ptr;
        LOG_INFO("read part %d %d", phdr->size, phdr->type);

        proc_main_print_part_hdr(phdr);
        ptr += sizeof(struct npk_part_hdr);

        if (REMAIN < phdr->size) {
            fprintf(stderr,
                    "Error: remain file chunk not enogh for partition data.\n");
            return -EINVAL;
        } else
            return -EINVAL;
        ptr += phdr->size;
    }

#undef REMAIN
    return 0;
}