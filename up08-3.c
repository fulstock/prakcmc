#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int
main(void)
{
    int i = 3;
    if (fork()) {
        if (fork()) {
            if (fork()) {
                if (getpid()) {
                    int status;
                    wait(&status);
                }
                char buf[9];
                read(STDIN_FILENO, buf, sizeof(buf) - 1);
                int num = (int)strtol(buf, NULL, 10);
                printf("%d %d\n", 3, num * num);
            }
        } else {
            i--;
            char buf[9];
            read(STDIN_FILENO, buf, sizeof(buf) - 1);
            int num = (int)strtol(buf, NULL, 10);
            printf("%d %d\n", 2, num * num);
        }
    } else {
        i--;       
        char buf[9];
        read(STDIN_FILENO, buf, sizeof(buf) - 1);
        int num = (int)strtol(buf, NULL, 10);
        printf("%d %d\n", 1, num * num);
    }
    return 0;
}

