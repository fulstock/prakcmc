#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

void proc(int num, int maxdep, int idep)
{
    pid_t pid = fork();
    if (!pid) {
        if (idep < maxdep) {
            proc(num * 2 + 1, maxdep, idep + 1);
        }
        printf("%d\n", num);
        fflush(stdout);
        if (idep < maxdep) {
            proc(num * 2 + 2, maxdep, idep + 1);
        }
        _exit(0);
    } else if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    }
}

int
main(int argc, char *argv[])
{
    int n = (int) strtol(argv[1], NULL, 10);
    proc(0, n, 0);
    _exit(0);
}

