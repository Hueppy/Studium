/*
 * copy.c
 *
 * Author: Carsten Gips
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define PANIC(msg)  {perror(msg); abort();}

int main(int argc, char *argv[]) {
    int src, dst;
    char buf[BUF_SIZE];
    ssize_t numRead;

    /* Parameter */
    if (argc != 3) {
        printf("usage: %s src dst\n", argv[0]);
        return 1;
    }

    /* Dateien aufmachen */
    src = open(argv[1], O_RDONLY);
    if (src == -1) {
        PANIC("open src file");
    }

    dst = open(argv[2], O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
    if (dst == -1) {
        PANIC("open dst file");
    }

    /* Kopieren */
    while ((numRead = read(src, buf, BUF_SIZE)) > 0) {
        if (write(dst, buf, numRead) != numRead) {
            PANIC("writing complete buffer");
        }
    }
    if (numRead == -1) {
        PANIC("reading src file");
    }

    /* Dateien schliessen */
    if (close(src) == -1) {
        PANIC("closing src");
    }
    if (close(dst) == -1) {
        PANIC("closing dst");
    }

    return 0;
}

int slightly_better_write(int fd, const char *buffer, size_t count) {
    ssize_t bytesWritten;
    while (count > 0) {
        bytesWritten = write(fd, buffer, count);
        if (bytesWritten == -1)
            return -1;
        count -= bytesWritten;
        buffer += bytesWritten;
    }
    return 0;
}
