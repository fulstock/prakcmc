#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void
err (pid_t pgid) {
    kill(-pgid, SIGKILL);
    while (wait(NULL) != -1) {}
    _exit(1);
}

int
main(int argc, char* argv[])
{
    int fd1[2];
    int fd2[2];
    pid_t pgid = getpid();
    setpgid(pgid, getppid());
    fd1[0] = dup(0);
    fd1[1] = dup(1);
    for (int i = 1; i < argc; i++) {
        if (i != argc - 1) {
            if (pipe(fd2) == -1) {
                err(pgid);
            }
        } else {
            fd2[0] = dup(0);
            fd2[1] = dup(1);
        }
        pid_t pid = fork();
        if (!pid) {
            if (dup2(fd1[0], 0) == -1 || dup2(fd2[1], 1) == -1) {
                _exit(1);
            }
            if (close(fd1[0]) || close(fd1[1]) || 
                close(fd2[0]) || close(fd2[1])) {
                _exit(1);
            }
            execlp(argv[i], argv[i], NULL);
            _exit(1);
        } else if (pid < 0) {
            err(pgid);
        }
        setpgid(pid, pgid);
        if (close(fd1[0]) || close(fd1[1])) {
            err(pgid);
        }
        fd1[0] = fd2[0];
        fd1[1] = fd2[1];
    }
    if (close(fd1[0]) || close(fd1[1])) {
        err(pgid);
    }
    int status;
    while (wait(&status) != -1) {}
    return 0;
}

