#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int
main(void)
{
    pid_t pid = fork();
    if (!pid) { //child
        pid_t pid2 = fork();
        if (!pid2) {  //grandchild
            printf("3 ");
        } else {
            int status2;
            wait(&status2);
            printf("2 ");
        }
    } else {
        int status;
        wait(&status);
        printf("1\n");
    }
    return 0;
}

