#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 1;
    }
    unsigned long long offset = 0;
    unsigned long long min_offset = 0;
    long long min = LLONG_MAX;
    int flag = 0;
    long long num;
    while (read(fd, &num, sizeof(num)) == sizeof(num)) {
        if (!flag || num < min) {
            flag = 1;
            min = num;
            min_offset = offset;
        }
        offset += sizeof(num);
    } 
    if (flag) {
        min = - (unsigned long long) min;
        if (lseek(fd, min_offset, SEEK_SET) == -1) {
            return 1;
        }
        if (write(fd, &min, sizeof(min)) != sizeof(min)) {
            return 1;
        }
    }
    close(fd);
    return 0;
}

