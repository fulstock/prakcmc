#include <string.h>

const char sample[] = "rwxrwxrwx";

int parse_rwx_permissions(const char *str)
{
    const int sample_len = sizeof(sample) - 1;
    if (!str) {
        return -1;
    }
    if (strlen(str) != sample_len) {
        return -1;
    }
    int counter = 0;
    unsigned int octet = 0;
    while (str[counter]) {
        if (str[counter] == sample[counter]) {
            octet += (1 << ((sample_len - 1) - counter));
        } else if (str[counter] != '-') {
            return -1;
        }
        counter++;
    } 
    return (int) octet;
}

