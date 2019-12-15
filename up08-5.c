#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(void)
{
    pid_t pid;
    int temp, res;
    res = 0;
    fflush(stdin);
    pid = fork();
    if (!pid) {
        res = 0;
        while (scanf("%d", &temp) == 1)
        {
            res = 0;
            fflush(stdin);
            pid = fork();
            if (pid < 0) {
                printf("-1\n");
                fflush(stdout);
                res = -1;
                break;
            } else if (pid > 0) {
                res = -1;
                int status;
                waitpid(pid, &status, 0);
                if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                    res = 0;
                    printf("%d\n", temp);
                    fflush(stdout);
                }
                break;
            }
        } 
        _exit(res);
    } else {
        waitpid(pid, NULL, 0);
        _exit(0);
    }
}


