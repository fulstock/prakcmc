#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

int
main(int argc, char *argv[])
{
    char *cmd1 = argv[1];
    char *file4 = argv[2];
    char *cmd2 = argv[3];
    char *cmd3 = argv[4];
    char *file5 = argv[5];
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 < 0) {
        return 1;
    }
    if (!pid1) {
        int fd4 = open(file4, O_RDONLY);
        if (fd4 < 0) {
            return 1;
        }
        dup2(fd4, 0);
        close(fd4);
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);
        execlp(cmd1, cmd1, NULL);
        _exit(1);
    }
    dup2(fd[0], 0);
    close(fd[0]);
    close(fd[1]);
    int fd5 = open(file5, O_RDWR | O_CREAT | O_APPEND, 0640);
    if (fd5 < 0) {
        return 1;
    }
    dup2(fd5, 1);
    close(fd5);
    pid_t pid2 = fork();
    if (pid2 < 0) {
        return 1;
    }
    if (!pid2) {
        pid_t pid3 = fork();
        if (pid3 < 0) {
            return 1;
        }
        if(!pid3) {
            execlp(cmd2, cmd2, NULL);
            _exit(1);
        } else {
            int status;
            wait(&status);
            if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                execlp(cmd3, cmd3, NULL);
                _exit(1);
            }
            _exit(1);
        }
        _exit(1);
    }
    wait(NULL);
    return 0;
}

