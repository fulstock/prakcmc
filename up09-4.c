#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

enum { EXT_SIZE = PATH_MAX * 2 + 7 };

int
main (int argc, char *argv[])
{
    const char *path;
    path = getenv("XDG_RUNTIME_DIR");
    if (!path) {
        path = getenv("TMPDIR");
        if (!path) {
            path = "/tmp";
        }
    }
    char filepath[PATH_MAX];
    snprintf(filepath, sizeof(filepath), "%s/run%d.py", path, getpid());
    umask(0);
    int fd = open(filepath, O_RDWR | O_TRUNC | O_CREAT, 0700);
    if (fd < 0) {
        _exit(1);
    }
    FILE *fin = fdopen(fd, "w+");
    int r = fputs("#! /usr/bin/python3\nprint(", fin);
    if (r < 0) {
        _exit(1);
    }
    for (int i = 1 ; i < argc - 1; i++) {
        r = fprintf(fin, "%s*", argv[i]);
        if (r < 0) {
            _exit(1);
        }
    }
    r = fprintf(fin, "%s)", argv[argc - 1]);
    if (r < 0) {
        _exit(1);
    }
    fflush(fin);
    fclose(fin);
    close(fd);
    char fullcmd[EXT_SIZE];
    snprintf(fullcmd, sizeof(fullcmd), "%s && rm %s", filepath, filepath);
    execl("/bin/sh", "sh", "-c", fullcmd, NULL);
    _exit(1);
}

