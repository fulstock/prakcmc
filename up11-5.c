#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t lastprime = 0;

void proc(int low, int high)
{
    for (int i = low; i < high; i++) {
        int isprime = 1;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                isprime = 0;
                break;
            }
        }
        if (isprime) {
            lastprime = i;
        }
    }
}

void
handler (int sig)
{
    fflush(stdout);
    if (sig == SIGINT) {
        if (counter == 3) { 
            _exit(0);
        }
        counter++;
        printf("%d\n", lastprime);
        fflush(stdout);
    } else if (sig == SIGTERM) {
        _exit(0);
    }
}

int
main(void)
{
    int low, high;
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    scanf("%d %d", &low, &high);
    if (low < 2) {
        low = 2;
    }
    printf("%d\n", getpid());
    fflush(stdout);
    proc(low, high);
    printf("-1\n");
    fflush(stdout);
    _exit(0);
}

