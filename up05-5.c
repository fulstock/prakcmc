#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

enum { MAX_STR_SIZE = 1001 };

int
main(int argc, char *argv[])
{
    FILE *f = fopen(argv[1], "r");
    if (!f) {
        return 1;
    }
    struct tm *first, *second;
    first = malloc(sizeof(*first));
    second = malloc(sizeof(*second));
    char init_line[MAX_STR_SIZE];
    fgets(init_line, MAX_STR_SIZE, f);
    strptime(init_line, "%Y/%m/%d %H:%M:%S", first);
    first->tm_isdst = -1;
    while (fgets(init_line, 1001, f)) {
        strptime(init_line, "%Y/%m/%d %H:%M:%S", second);
        second->tm_isdst = -1;
        printf("%ld\n", mktime(second) - mktime(first));
        *first = *second;
    }
    free(first);
    free(second);
    fclose(f);
    return 0;
}

