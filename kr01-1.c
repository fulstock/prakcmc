#include <stdlib.h>
#include <stdio.h>

enum
{
    BASE_HEX = 16,
    SECOND_NUM_BIT = 8,
    FOURTH_NUM_BIT = 16,
    BASE_THT = 32,
    SHIFT_VAL = 4
};

int
main(int argc, char *argv[])
{
    unsigned long long sum = 0;
    for (int i = 1; i < argc; i++) {
        unsigned long long num = (unsigned long long) strtoll(argv[i],
                NULL, BASE_THT);
        sum ^= num;
    }
    printf("%x\n", (unsigned int) ((sum >> SECOND_NUM_BIT) % BASE_HEX *
                (1 << SHIFT_VAL) + (sum >> FOURTH_NUM_BIT) % BASE_HEX));
    return 0;
}

