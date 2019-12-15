#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

unsigned long long hash_function(unsigned long long);

int
main(int argc, char *argv[])
{
    umask(0000);
    if (argc != 4) {
        return 1;
    }
    int fd = open(argv[1], O_WRONLY | O_CREAT,
            S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd == -1) {
        return 1;
    }
    unsigned long long init_offset = lseek(fd, 0, SEEK_END);
    if (init_offset == -1) {
        return 1;
    }
    char *end;
    unsigned long long hash = strtoll(argv[2], &end, 16);
    unsigned long long count = strtoll(argv[3], &end, 10);
    if (count == 0) {
        close(fd);
        return 0;
    }
    for (int i = count - 1; i >= 0; i--) {
        lseek(fd, init_offset + sizeof(hash) * i, SEEK_SET);
        if (write(fd, &hash, sizeof(hash)) != sizeof(hash)) {
            return 1;
        }
        hash = hash_function(hash);
    }
    close(fd);
    return 0;
}

