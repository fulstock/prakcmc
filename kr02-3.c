#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    float num, sum;
    sum = 0;
    pid_t ppid, pid;
    int ppfd[2];
    pipe(ppfd);
    ppid = fork();
    if (!ppid) {
        int pfd[2];
        pipe(pfd);
        pid = fork();
        if(!pid) {
            close(pfd[1]);
            close(ppfd[0]);
            while (read(pfd[0], &num, sizeof(num)) == sizeof(num)) {
                sum += num;
            }
            close(pfd[0]);
            write(ppfd[1], &sum, sizeof(sum));
            close(ppfd[1]);
            _exit(0);
        } else if (pid > 0) {
            close(ppfd[0]);
            close(ppfd[1]);
            int fd = open(argv[1], O_RDONLY);
            FILE *fin = fdopen(fd, "r");
            close(pfd[0]);
            while (fscanf(fin, "%f", &num) == 1) {
                fflush(fin);
                if (num >= 0) {
                    write(pfd[1], &num, sizeof(num));
                }
            }
            close(pfd[1]);
            close(fd);
            _exit(0);
        }
    } else if (ppid > 0) {
        close(ppfd[1]);
        read(ppfd[0], &sum, sizeof(sum));
        close(ppfd[0]);
        printf("%.10g\n", sum);
        fflush(stdout);
        _exit(0);
    }
    return 0;
}

