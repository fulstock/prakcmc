#include <dirent.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
    if (argc != 3) {
        return 1;
    }
    DIR *dir = opendir(argv[1]);
    unsigned int num = (unsigned int) strtol(argv[2], NULL, 10);
    if (!dir) {
        return 1;
    }
    struct dirent *dd;
    char buf[PATH_MAX];
    unsigned long long sum = 0;
    while ((dd = readdir(dir))) {
        if (!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
            continue;
        }
        int slen = snprintf(buf, sizeof(buf), "%s/%s", argv[1], dd->d_name);
        if (slen + 1 > sizeof(buf)) {
            continue;
        }
        struct stat sb;
        if (lstat(buf, &sb) == -1) {
            continue;
        }
        if (S_ISREG(sb.st_mode) && !access(buf, W_OK)) {
            int fd = open(buf, O_RDONLY);
            if (!fd) {
                continue;
            }
            unsigned int rnum;
            if (read (fd, &rnum, sizeof(rnum)) != sizeof(rnum)) {
                continue;
            }
            if (rnum != num) {
                continue;
            } else {
                sum += (unsigned long long) sb.st_size;
            }
            close(fd);
        }
    }
    printf("%llu\n", sum);
    return 0;
}

