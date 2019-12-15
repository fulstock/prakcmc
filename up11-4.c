#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int maxnum;
FILE *fins[2];

void
handler (int sig)
{
    int pidnum, num;
    pid_t pid;
    fscanf(fins[0], "%d%d%d", &num, &pidnum, &pid);
    fflush(fins[0]);
    if (num >= maxnum) {
        fclose(fins[0]);
        fclose(fins[1]);
        _exit(0);
    }
    printf("%d %d\n", pidnum, num++);
    fflush(stdout);
    pidnum = pidnum % 2 + 1;
    pid_t pidnext = getpid();
    fprintf(fins[1], "%d\n%d\n%d\n", num, pidnum, pidnext);
    fflush(fins[1]);
    kill(pid, SIGUSR1);
}

int
main(int argc, char* argv[])
{
    int fd[2];
    pid_t pid1, pid2;
    pipe(fd);
    fins[0] = fdopen(fd[0], "r");
    fins[1] = fdopen(fd[1], "w");
    struct sigaction sa;
    sa.sa_flags = SA_RESTART;
    sa.sa_handler = handler;
    sigaction(SIGUSR1, &sa, NULL);
    maxnum = (int) strtol(argv[1], NULL, 10);
    pid1 = fork();
    if (!pid1) {
        while(1) {
            pause();
        }
    } else {
        pid2 = fork();
        if (!pid2) {
            while (1) {
                pause();       
            }
        } else {
            int num = 1;
            fprintf(fins[1], "%d\n%d\n%d\n", num, num, pid2);
            fflush(fins[1]);
            kill(pid1, SIGUSR1);
            pid_t w_pid = wait(NULL);
            fprintf(fins[1], "%d\n%d\n%d\n", maxnum, maxnum, w_pid);
            fflush(fins[1]);
            fclose(fins[0]);
            fclose(fins[1]);
            if (w_pid == pid1) {
                kill(pid2, SIGUSR1);
            } else {
                kill(pid1, SIGUSR1);  
            } 
            wait(NULL);
            printf("Done\n");
        }
    }
    return 0;
}

