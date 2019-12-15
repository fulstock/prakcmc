#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    off_t sum_size = 0;
    for (int i = 1; i < argc; i++) {
        struct stat sb;
        if (lstat(argv[i], &sb) == 0 && S_ISREG(sb.st_mode) && sb.st_nlink == 1) {
            sum_size += sb.st_size;
        }
    }
    printf("%llu\n", (unsigned long long) sum_size);
    return 0;
}

