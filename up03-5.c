#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

char *getline2(FILE *f);

enum
{
    DEC_BASE = 10, 
    WRONG_SYM_NUM = 0xbedabeda,
    SPACE_NUM = 0x0bad1dea
};

int
main(void)
{
    int line_count = 1;
    char *str;
    while ((str = getline2(stdin))) {
        char *ptr = str;
        unsigned sum = 0;
        int flag = 0;
        int num_count = 0;
        while (*ptr && *ptr != '\n') {
            if (isspace((unsigned char)*ptr)) {
                ptr++;
            } else if (((*ptr == '-' || *ptr == '+') 
                    && isdigit((unsigned char)ptr[1])) 
                    || isdigit((unsigned char)*ptr)) {
                num_count++;
                long val = strtol(ptr, &ptr, DEC_BASE);
                if (errno == ERANGE || val < INT_MIN || val > INT_MAX || val != (int) val) {
                    if (val > 0) {
                        val = num_count;
                    } else if (val < 0) {
                        val = -num_count;
                    }
                }
                errno = 0;
                sum += (unsigned) val;
            } else {
                flag = 1;
                break;
            }
        }
        int res = (int) sum;
        if (flag) {
            res = WRONG_SYM_NUM + line_count;
        } else if (!num_count) {
            res = SPACE_NUM + line_count;
        }
        printf("%d\n", res);
        free(str);
        line_count++;
    }
    return 0;
}

