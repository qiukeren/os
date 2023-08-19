//XOS:3RD https://github.com/jwerle/fs.c
//XOS:3RDLICENSE MIT LICENSE

#ifndef X_FILE_H
#define X_FILE_H 1


#include <stdio.h>
#include <sys/stat.h>

#define X_FS_OPEN_READ "r"
#define X_FS_OPEN_WRITE "w"
#define X_FS_OPEN_READWRITE "rw"

#define X_FS_OPEN_READ_SYSCALL O_RDONLY
#define X_FS_OPEN_WRITE_SYSCALL O_WRONLY
#define X_FS_OPEN_READWRITE_SYSCALL O_RDWR

typedef struct stat x_fs_stats;

/**
 * Prints the last error to stderr
 */

void x_fs_error(const char* prefix);

/**
 * Opens a file with given flags
 * and returns a file descriptor
 */

FILE* x_fs_fopen(const char* path, const char* flags);


int x_fs_file_to_fd(FILE *);


int x_fs_open(const char* path, const int flags);
/**
 * Closes a given file descriptor
 */

int x_fs_close(FILE* file);

/**
 * Moves a path to a new destination
 */

int x_fs_rename(const char* from, const char* to);

/**
 * Stats a given path and returns
 * a `struct stat`
 */

int x_fs_stat(const char* path, x_fs_stats* stats);

/**
 * Stats a given file descriptor
 */

int x_fs_fstat(FILE* file,x_fs_stats* stats);

/**
 * Stats a given link path
 */

int x_fs_lstat(const char* path,x_fs_stats* stats);

/**
 * Truncates a file to a specified
 * length from a given file descriptor
 */

int x_fs_ftruncate(FILE* file, int len);

/**
 * Truncates a file to a specified
 * len from a given file path
 */

int x_fs_truncate(const char* path, int len);

/**
 * Changes ownership of a given
 * file path to a given owner
 * and group
 */

int x_fs_chown(const char* path, int uid, int gid);

/**
 * Change ownership of a given
 * file descriptor to a given owner
 * and group
 */

int x_fs_fchown(FILE* file, int uid, int gid);

/**
 * Returns the size of a file from
 * a given file path
 */

size_t x_fs_size(const char* path);

/**
 * Returns the size of a file
 * from a given file descriptor
 */

size_t x_fs_fsize(FILE* file);

/**
 * Change ownership of a given
 * link path to a given owner
 * and group
 */

int x_fs_lchown(const char* path, int uid, int gid);

/**
 * Reads a file by a given file
 * path
 */

char* x_fs_read(const char* path);

/**
 * Reads a file by a given
 * file path by a given `n`
 * number of bytes
 */

char* x_fs_nread(const char* path, int len);

/**
 * Reads a file by a given
 * file descriptor
 */

char* x_fs_fread(FILE* file);

/**
 * Reads a file by a given
 * file descriptor by a given
 * `n` number of bytes
 */

char* x_fs_fnread(FILE* file, int len);

/**
 * Writes a buffer
 * to a given file path
 */

int x_fs_write(const char* path, const char* buffer);

/**
 * Writes `n` bytes of a buffer to a given
 * file path
 */

int x_fs_nwrite(const char* path, const char* buffer, int len);

/**
 * Writes a buffer to a given
 * file stream
 */

int x_fs_fwrite(FILE* file, const char* buffer);

/**
 * Writes `n` bytes of a buffer
 * to a given file stream
 */

int x_fs_fnwrite(FILE* file, const char* buffer, int len);

/**
 * Makes a directory and returns 0
 * on success or -1 on failure
 */

int x_fs_mkdir(const char* path, int mode);

/**
 * Removes a directory and returns
 * 0 on success and -1 on failure
 */

int x_fs_rmdir(const char* path);

/**
 * Check if the given `path` exists
 */

int x_fs_exists(const char* path);

#endif