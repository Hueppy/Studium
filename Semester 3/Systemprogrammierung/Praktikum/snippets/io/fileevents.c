/*
 * fileevents.c
 *
 * Author: Carsten Gips
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>

#define PANIC(msg)  {perror(msg); abort();}
#define BUF_SIZE 1024

int main(int argc, char *argv[]) {
    int inotifyFD, wd, j;
    char buf[BUF_SIZE];
    ssize_t n;
    char *p;
    struct inotify_event *e;

    /* Init */
    inotifyFD = inotify_init();
    if (inotifyFD == -1) {
        PANIC("inotify_init");
    }

    /* Watches */
    for (j = 1; j < argc; j++) {
        wd = inotify_add_watch(inotifyFD, argv[j], IN_ALL_EVENTS);
        if (wd == -1) {
            PANIC("inotify_add_watch");
        }
        printf("watching %s using wd=%d\n", argv[j], wd);
    }

    /* Loop */
    for (;;) {
        /* Inotify-FD auslesen */
        n = read(inotifyFD, buf, BUF_SIZE);
        if (n <= 0) {
            PANIC("read(inotifyFD)");
        }
        printf("read %ld bytes from inotify fd\n", (long) n);

        /* ueber alle gelesenen Events iterieren */
        for (p = buf; p < buf + n;) {
            e = (struct inotify_event *) p;

            printf("wd=%d; ", e->wd);
            if (e->len > 0) {
                printf("name=%s; ", e->name);
            }
            printf("mask: ");
            if (e->mask & IN_ACCESS)
                printf("IN_ACCESS ");
            if (e->mask & IN_OPEN)
                printf("IN_OPEN ");
            if (e->mask & IN_CREATE)
                printf("IN_CREATE ");
            if (e->mask & IN_CLOSE_NOWRITE)
                printf("IN_CLOSE_NOWRITE ");
            if (e->mask & IN_CLOSE_WRITE)
                printf("IN_CLOSE_WRITE ");
            if (e->mask & IN_MODIFY)
                printf("IN_MODIFY ");
            if (e->mask & IN_ATTRIB)
                printf("IN_ATTRIB ");
            printf("\n");

            p += sizeof(struct inotify_event) + e->len;
        }
    }

    return 0;
}
