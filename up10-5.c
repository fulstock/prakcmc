#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int proc(int fdr, int fdw, int max, int pid)
{
    int x = 0;
    while(x < max) {
        int r = read(fdr, &x, sizeof(x));
        if (!r || x >= max) {
            return -1;
        }
        printf("%d %d\n", pid, x);
        fflush(stdout);
        x++;
        write(fdw, &x, sizeof(x));
    }
    return 0;
}

int
main(int argc, char *argv[])
{
    int fd12[2];
    int fd21[2];
    pipe(fd12);
    pipe(fd21);
    int maxnum = strtol(argv[1], NULL, 10);
    int pid1, pid2;
    if (!fork())
    {
        pid1 = 1;
        close(fd21[1]);
        close(fd12[0]);
        proc(fd21[0], fd12[1], maxnum, pid1);
        _exit(0);
    }

    if(!fork())
    {
        pid2 = 2;
        close(fd12[1]);
        close(fd21[0]);
        proc(fd12[0], fd21[1], maxnum, pid2);
        _exit(0);
    }

    int x = 1;
    write(fd21[1], &x, sizeof(x));
    close(fd12[0]);
    close(fd21[0]);
    close(fd12[1]);
    close(fd21[1]);

    while (wait(NULL) > 0) {}

    printf("Done\n");
    return 0;
}

