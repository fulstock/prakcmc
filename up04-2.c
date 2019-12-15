#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <limits.h>

enum { BUF_SIZE = sizeof(short) };

int
main(int argc, char *argv[])
{
    int fd = creat(argv[1], 0600);
    unsigned short u;
    unsigned char buf[BUF_SIZE];
    while(scanf("%hu", &u) != EOF) {
        buf[0] = u >> CHAR_BIT;
        buf[1] = u;
        if (write(fd, buf, BUF_SIZE) != BUF_SIZE) {
            return 1;
        }
    }
    close(fd);
    return 0;
}

