#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

int
mysys (const char *str)
{
    pid_t pid = fork();
    if (pid < 0) {
        _exit(-1);
    } else if (!pid) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(127);
    } else {
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            int ex = WEXITSTATUS(status);
            if (ex >= 0 && ex <= 127) {
                return WEXITSTATUS(status);
            }
        } else if(WIFSIGNALED(status)) {
            return 128 + WTERMSIG(status);
        }
    }
    return 0;
}

