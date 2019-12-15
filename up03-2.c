#include <stdio.h>
#include <stdlib.h>

enum { BASE = 10 };

int
main(int argc, char *argv[])
{
    long long pos = 0;
    long long neg = 0;
    for (int i = 1; i < argc; i++) {
        char *end;
        long long x = strtoll(argv[i], &end, BASE);
        if (x > 0) {
            pos += x;
        } else if (x < 0) {
            neg += x;
        }
    }
    printf("%lld\n%lld\n", pos, neg);
}
