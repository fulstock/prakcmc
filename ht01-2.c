#include <stdint.h>

int32_t satsum(int32_t v1, int32_t v2) {
    int32_t res;
    uint32_t lim_value = 0;
    if (__builtin_add_overflow(v1, v2, &res)) {
        if (v1 > 0) {
            return ~lim_value >> 1;
        }
        return (~lim_value >> 1) + 1;
    }
    return res;
}

