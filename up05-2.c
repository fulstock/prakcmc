#include <stdio.h>
#include <stdlib.h>

char rights[] = "xwrxwrxwr";

enum
{ 
    RIGHTS_MAX_BIT = sizeof(rights),
    OCTAL_BASE = 8
};

int
main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        char *s = argv[i];
        unsigned long num = strtol(s, &s, OCTAL_BASE);
        for (unsigned int bit = RIGHTS_MAX_BIT - 2; bit <= RIGHTS_MAX_BIT - 2; bit--) {
            putchar(num & (1 << bit) ? rights[bit] : '-');
        }
        putchar('\n');
    }
    return 0;
}

