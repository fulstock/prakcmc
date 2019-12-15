#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

enum { CORR_COUNT = 2 };

int
main(void)
{
    long long a, b;
    int var_count = scanf("%lld %lld", &a, &b);
    if (var_count != CORR_COUNT) {
        return 1;
    }
    long long left_part, right_part;
    if (a < 0) {
        left_part = b + a % b;
        right_part = llabs(a % b);
    } else {
        left_part = a % b;
        right_part = b - a % b;
    }
    long long c;
    if (left_part < right_part) {
        if (llabs(a - left_part) <= INT_MAX) {
            c = a - left_part;
        } else {
            c = a + right_part;
        }
    } else {
        if (a + right_part > INT_MAX) {
            c = a - left_part;
        } else {
            c = a + right_part;
        }
    }
    printf("%d\n", (int) c);
    return 0;
}

