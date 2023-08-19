
/**
 * fs.c
 *
 * copyright 2013 - joseph werle <joseph.werle@gmail.com>
 */

#define _POSIX_C_SOURCE 200809L
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "x_file.h"

void x_fs_error(const char* prefix) {
    char fmt[256];
    sprintf(fmt, "XOS_FS: %s: error", prefix);
    perror(fmt);
}

FILE* x_fs_fopen(const char* path, const char* flags) {
    return fopen(path, flags);
}

int x_fs_file_to_fd(FILE* file) {
    int fd = fileno(file);
    return fd;
}

int x_fs_open(const char* path, const int flags) {
    return open(path, flags);
}

int x_fs_close(FILE* file) {
    return fclose(file);
}

int x_fs_rename(const char* from, const char* to) {
    return rename(from, to);
}

int x_fs_stat(const char* path, x_fs_stats* stats) {
    int e = stat(path, stats);

    return e;
}

int x_fs_fstat(FILE* file, x_fs_stats* stats) {
    if (NULL == file)
        return 0;
    int fd = fileno(file);
    int e = fstat(fd, stats);
    return e;
}

int x_fs_lstat(const char* path, x_fs_stats* stats) {
    int e = lstat(path, stats);
    return e;
}

int x_fs_ftruncate(FILE* file, int len) {
    int fd = fileno(file);
    return ftruncate(fd, (off_t)len);
}

int x_fs_truncate(const char* path, int len) {
    return truncate(path, (off_t)len);
}

int x_fs_chown(const char* path, int uid, int gid) {
    return chown(path, (uid_t)uid, (gid_t)gid);
}

int x_fs_fchown(FILE* file, int uid, int gid) {
    int fd = fileno(file);
    return fchown(fd, (uid_t)uid, (gid_t)gid);
}

int x_fs_lchown(const char* path, int uid, int gid) {
    return lchown(path, (uid_t)uid, (gid_t)gid);
}

size_t x_fs_size(const char* path) {
    size_t size;
    FILE* file = x_fs_fopen(path, X_FS_OPEN_READ);
    if (NULL == file)
        return -1;
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    x_fs_close(file);
    return size;
}

size_t x_fs_fsize(FILE* file) {
    // store current position
    unsigned long pos = ftell(file);
    rewind(file);
    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    fseek(file, pos, SEEK_SET);
    return size;
}

char* x_fs_read(const char* path) {
    FILE* file = x_fs_fopen(path, X_FS_OPEN_READ);
    if (NULL == file)
        return NULL;
    char* data = x_fs_fread(file);
    fclose(file);
    return data;
}

char* x_fs_nread(const char* path, int len) {
    FILE* file = x_fs_fopen(path, X_FS_OPEN_READ);
    if (NULL == file)
        return NULL;
    char* buffer = x_fs_fnread(file, len);
    x_fs_close(file);
    return buffer;
}

char* x_fs_fread(FILE* file) {
    size_t fsize = x_fs_fsize(file);
    return x_fs_fnread(file, fsize);
}

char* x_fs_fnread(FILE* file, int len) {
    char* buffer = (char*)malloc(sizeof(char) * (len + 1));
    size_t n = fread(buffer, 1, len, file);
    buffer[n] = '\0';
    return buffer;
}

int x_fs_write(const char* path, const char* buffer) {
    return x_fs_nwrite(path, buffer, strlen(buffer));
}

int x_fs_nwrite(const char* path, const char* buffer, int len) {
    FILE* file = x_fs_fopen(path, X_FS_OPEN_WRITE);
    if (NULL == file)
        return -1;
    int result = x_fs_fnwrite(file, buffer, len);
    fclose(file);
    return result;
}

int x_fs_fwrite(FILE* file, const char* buffer) {
    return x_fs_fnwrite(file, buffer, strlen(buffer));
}

int x_fs_fnwrite(FILE* file, const char* buffer, int len) {
    return (int)fwrite(buffer, 1, len, file);
}

int x_fs_mkdir(const char* path, int mode) {
    return mkdir(path, (mode_t)mode);
}

int x_fs_rmdir(const char* path) {
    return rmdir(path);
}

int x_fs_exists(const char* path) {
    struct stat b;
    return stat(path, &b);
}