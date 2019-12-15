#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int
main(void)
{
    uint32_t n;
    int w;
    int res = scanf("%"PRIo32" %o", &n, &w);
    if (res != 2) {
        return 1;
    }
    for (uint32_t i = 0; i < (1 << n); i++) {
        printf("|%*"PRIo32"", w, i);
        printf("|%*"PRIu32"", w, i);
        uint32_t j = i;
        if (i >= (1 << (n - 1))) {
            j = (1 << (n - 1)) - i;
        }
        printf("|%*"PRId32"|\n", w, j);
    }
    return 0;
}

