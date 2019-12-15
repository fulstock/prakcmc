#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <inttypes.h>

int
main(int argc, char *argv[])
{
    if (argc != 2) {
        return 1;
    }
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    int flag = 0;
    uint16_t num;
    uint16_t min = INT16_MAX;
    uint8_t buf[2];
    while (read(fd, buf, sizeof(buf)) == sizeof(buf)) {
        num = ((uint16_t) buf[0]) << 8 | (uint16_t) buf[1];
        if ((num & 1) == 0 && (!flag || num < min)) {
            min = num;
            flag = 1;
        }
    }
    if (flag) {
        printf("%"PRIu16"\n", min);
    }
    close(fd);
    return 0;
}

