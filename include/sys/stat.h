#ifndef SYS_STAT_H
#define SYS_STAT_H

#include <stdint.h>

/* File types (matches kernel fs/fs.h) */
#define DT_UNKNOWN  0
#define DT_REG      1   /* regular file */
#define DT_DIR      2   /* directory */
#define DT_CHRDEV   3   /* character device */
#define DT_BLKDEV   4   /* block device */
#define DT_SYMLINK  5   /* symbolic link */

/* File mode bits (simplified) */
#define S_IFMT   0170000  /* file type mask */
#define S_IFREG  0100000  /* regular file */
#define S_IFDIR  0040000  /* directory */
#define S_IFCHR  0020000  /* character device */
#define S_IFBLK  0060000  /* block device */

#define S_ISREG(m)  (((m) & S_IFMT) == S_IFREG)
#define S_ISDIR(m)  (((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR(m)  (((m) & S_IFMT) == S_IFCHR)
#define S_ISBLK(m)  (((m) & S_IFMT) == S_IFBLK)

/* stat structure (matches kernel fs/fs.h stat_t) */
struct stat {
    uint32_t st_size;    /* file size in bytes */
    uint8_t  st_type;    /* file type (DT_REG, DT_DIR, etc.) */
    uint32_t st_ino;     /* inode number */
    uint32_t st_ctime;   /* creation time */
    uint32_t st_mtime;   /* modification time */
    uint32_t st_mode;    /* permission bits */
};

/* Function declarations */
int stat(const char *path, struct stat *buf);
int fstat(int fd, struct stat *buf);

#endif /* SYS_STAT_H */