#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
    int fd12[2];
    int x;
    long long sum = 0;
    pipe(fd12);
    
    if (!fork())
    {
        close(fd12[1]);
        if(!fork())
        {
            while(read(fd12[0], &x, sizeof(x)))
            {
                sum += (long long) x;
            }
            printf("%lld\n", sum);
            fflush(stdout);
            close(fd12[0]);
            close(fd12[1]);
            _exit(0);
        } else {
            close(fd12[0]);
            close(fd12[1]);
            wait(NULL);
            _exit(0);
        }
    } else {
        close(fd12[0]);
        while (scanf("%d", &x) != EOF)
        {
            fflush(stdin);
            write(fd12[1], &x, sizeof(x));
        }
        close(fd12[1]);
        wait(NULL);
        return 0;
    }
    return 0;
}

