#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile int flag = 1;

void
handler (int sig)
{
    if (sig == SIGINT) {
        flag = 1;
    } else if (sig == SIGQUIT) {
        flag = 0;
    }
}

int
main(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGQUIT, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    int val = 0;
    int num;
    while (scanf("%d", &num) == 1) {
        fflush(stdin);
        if (flag) {
            __builtin_sadd_overflow(val, num, &val);
        } else {
            __builtin_smul_overflow(val, num, &val);
        }
        printf("%d\n", val);
        fflush(stdout);
    }
    return 0;
}

