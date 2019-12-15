#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

enum
{
    GOODS_NAME_SIZE = 16,
    DELIM_PERCENT = 100
};

struct Check
{
    char buf[GOODS_NAME_SIZE];
    int sum;
};

int
main(int argc, char *argv[])
{
    struct Check tmp_check;
    int max1 = INT_MIN;
    int max2 = max1;
    int flag = 0;
    int flag2 = 0;
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            return 1;
        }
        while(read(fd, &tmp_check, sizeof(tmp_check)) == sizeof(tmp_check)) {
            if (!flag || tmp_check.sum > max1) {
                if (flag) {
                    flag2 = 1;
                }
                max2 = max1;
                max1 = tmp_check.sum;
                flag = 1;
            } else if (tmp_check.sum < max1 && tmp_check.sum >= max2) {
                max2 = tmp_check.sum;
                flag = 1;
                flag2 = 1;
            }         
        }
    }
    if (flag2) {
        printf("%.2f\n", max2 / (float) DELIM_PERCENT);
    }
    return 0;
} 

