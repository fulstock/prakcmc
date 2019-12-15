#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

int
main(void)
{
    int n, i;
    scanf("%d", &n);
    pid_t pid = getpid();
    pid_t initpid = pid;
    i = 0;
    printf("%d", i + 1);
    fflush(stdout);
    while (i++ < n - 1 && pid) {
        pid = fork();
        int status;
        wait(&status);
    }
    if (!pid) {
        printf(" %d", i);
    }
    if (getpid() == initpid) {
        printf("\n");
    }
    return 0;
}

