#include <stdio.h>

enum { FRAC_SIZE = 23 };

int isReprFloat(unsigned int num)
{
    while (num && num % 2 == 0) {
        num >>= 1;
    }
    return (num <= (1 << (FRAC_SIZE + 1)) - 1);
}

int
main(void)
{
    unsigned num;
    while (scanf("%u", &num) == 1) {
        printf("%d\n", isReprFloat(num));
    }
    return 0;
}

