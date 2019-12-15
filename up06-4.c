#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int
main (int argc, char *argv[])
{
    DIR *dir = opendir(argv[1]);
    if (!dir) {
        return 1;
    }
    struct dirent *dt;
    char path[PATH_MAX];
    unsigned long long sum_size = 0;
    struct stat sb;
    while ((dt = readdir(dir))) {
        if (strcmp(dt->d_name, ".") && strcmp(dt->d_name, "..") ) {
            int res = snprintf(path, sizeof(path), "%s/%s", 
                    argv[1], dt->d_name);
            if (res + 1 <= sizeof(path) && stat(path, &sb) != -1
                    && S_ISREG(sb.st_mode) && sb.st_uid == getuid()
                    && isupper((unsigned char)dt->d_name[0])) {
                sum_size += (unsigned long long) sb.st_size;
            }
        }
    }
    printf("%llu\n", sum_size);
    return 0;
}

