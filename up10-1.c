#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int
main()
{
    int fd[2];
    pipe(fd);
    struct tm *times;
    time_t t;
    if(!fork())
    {
        if(!fork())
        {
            if(!fork())
            {
                t = time(NULL);
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                write(fd[1], &t, sizeof(t));
                _exit(0);
            }
            wait(NULL);
            read(fd[0], &t, sizeof(t));
            close(fd[0]);
            close(fd[1]);
            times = localtime(&t);
            printf("D:%02d\n", times->tm_mday);
            fflush(stdout);
            _exit(0);
        }
        wait(NULL);
        read(fd[0], &t, sizeof(t));
        close(fd[0]);
        close(fd[1]);
        times = localtime(&t);
        printf("M:%02d\n", times->tm_mon + 1);
        fflush(stdout);
        _exit(0);
    }
    wait(NULL);
    read(fd[0], &t, sizeof(t));
    close(fd[0]);
    close(fd[1]);
    times = localtime(&t);
    printf("Y:%04d\n", times->tm_year + 1900);
    fflush(stdout);
    _exit(0);
}

