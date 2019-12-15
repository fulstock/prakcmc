#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

int
main (int argc, char *argv[])
{
    int n = (int) strtol(argv[1], NULL, 10);
    for (int k = 0; k < n; k++) {
        pid_t pid = fork();
        if (!pid) {
            FILE *fin = fopen(argv[k + 2], "r");
            char path[PATH_MAX];
            fgets(path, sizeof(path), fin);
            path[strlen(path) - 1] = '\0';
            fclose(fin);
            execlp(path, path, NULL);
            _exit(1);
        }
    }
    int num = 0;
    int status;
    while (wait(&status) != -1) {
        if (WIFEXITED(status) && !WEXITSTATUS(status)) {
            num++;
        }
    }
    for (int k = n; k < argc - 2; k++) {
        pid_t pid = fork();
        if (!pid) {
            FILE *fin = fopen(argv[k + 2], "r");
            char path[PATH_MAX];
            fgets(path, sizeof(path), fin);
            path[strlen(path) - 1] = '\0';
            fclose(fin);
            execlp(path, path, NULL);
            _exit(1);
        } else {
            wait(&status);
            if (WIFEXITED(status) && !WEXITSTATUS(status)) {
                num++;
            }
        }
    }
    printf("%d\n", num);
    return 0;
}

