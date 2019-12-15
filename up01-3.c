#include <stdlib.h>

struct Pair
{
    int key;
    int value;
};

void process(struct Pair *data, size_t size)
{
    if (size <= 0)
        return;
    int curr_size, left, mid, right;
    for (curr_size = 1; curr_size <= size - 1; curr_size *= 2) {
        for (left = 0; left < size - 1; left += curr_size * 2) {
            mid = left + curr_size - 1;
            mid = mid < size - 1 ? mid : size - 1;
            right = left + curr_size * 2 - 1;
            right = right < size - 1 ? right : size - 1;
            // merge
            struct Pair *buf = calloc(curr_size, sizeof(*buf));
            if (!buf) {
                return;
            }
            int first, second;
            for (int i = 0; left + i <= mid; i++) {
                buf[i] = data[left + i];
            }
            int count = 0;
            first = left;
            second = mid + 1;
            while (first <= right && count < curr_size && second <= right) {
                if (buf[count].key <= data[second].key) {
                    data[first] = buf[count];
                    count++;
                } else {
                    data[first] = data[second];
                    second++;
                }
                first++;
            }
            while (first <= right && count < curr_size) {
                data[first] = buf[count];
                first++;
                count++;
            }
            free(buf);
        }
    }
}

