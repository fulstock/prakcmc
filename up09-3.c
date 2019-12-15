#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

int usecmd(char *argv)
{
    pid_t pid = fork();
    if (pid < 0) {
        return 1;
    } else if (!pid) {
        execlp(argv, argv, NULL); //cmd_i
        _exit(1);
    } else {
        int status;
        waitpid(pid, &status, 0);
        return (WIFEXITED(status) && !WEXITSTATUS(status));
    }
}

int
main (int argc, char *argv[])
{
    return !((usecmd(argv[1]) || usecmd(argv[2])) && usecmd(argv[3]));
}

