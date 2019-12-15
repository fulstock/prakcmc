#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <ctype.h>

enum
{
    BUF_SIZE = 16,
    DEC_RADIX = 10
};

int
main(void)
{
    char buf[BUF_SIZE];
    ssize_t bytes_read;
    unsigned long long sum = 0;
    unsigned long long num = 0;
    char sign_char = '\0';
    while ((bytes_read = read(STDIN_FILENO, buf, sizeof(buf))) != 0) {
        if (bytes_read == -1) {
            printf("\n");
            return 1;
        }
        for (int i = 0; i < bytes_read; i++) {
            if (isdigit((unsigned char)buf[i])) {
                num = num * DEC_RADIX + buf[i] - '0';
            } else if (buf[i] == '+' || buf[i] == '-') {
                sign_char = buf[i];
            } else if (isspace((unsigned char)buf[i])) {
                if (sign_char == '-')
                    num = -num;
                sum += num;
                num = 0;
                sign_char = '\0';
            }
        }
    }
    if (sign_char == '-') {
        num = -num;
    }
    sum += num;
    printf("%lld\n", sum);
    return 0;
}

