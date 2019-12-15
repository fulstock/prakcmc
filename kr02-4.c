#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    char *sep = argv[1];
    int lastarg = argc;
    for (int i = argc - 1; i >= 1; i--) {
        if(!strcmp(argv[i], sep)) {
            pid_t pid = fork();
            if(!pid) {
                argv[lastarg] = NULL;
                execvp(argv[i + 1], &argv[i + 1]);
                _exit(1);
            } else if (pid > 0) {
                wait(NULL);
                lastarg = i;
            }
        }
    }
    _exit(0);
}

