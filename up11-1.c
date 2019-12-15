#include <unistd.h>
#include <signal.h>
#include <stdio.h>

volatile sig_atomic_t counter = 0;

void
handler (int sig)
{
    if (counter == 5) {
        _exit(0);
    } else {
        printf("%d\n", counter++);
        fflush(stdout);
    }
}

int
main (void)
{
    counter = 0;
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGHUP, &sa, NULL);
    printf("%d\n", getpid());
    fflush(stdout);
    while (1) {
        pause();
    }
    return 0;
}

