#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int bc(signed long long num)
{
    int count = 0;
    int unum = (unsigned long long) num;
    while(unum > 0) {
        count += unum & 1;
        unum >>= 1;
    }
    return count;
}

int
main(int argc, char *argv[])
{
    pid_t *pids = calloc(argc - 1, sizeof(pid_t));
    pid_t pid;
    for (int i = 1; i < argc; i++) {
        pids[i] = fork();
        if (!pids[i]) {
            _exit(bc(strtoll(argv[i], NULL, 10)));
        }
    }
    int *nums = calloc(argc - 1, sizeof(int));
    int status;
    while((pid = wait(&status)) != -1)
    {
        int j = 0;
        while (pids[j] != pid) {
            j++;
        }
        nums[j - 1] = WEXITSTATUS(status);
    }
    for (int i = 0; i < argc - 1; i++) {
        printf("%d\n", nums[i]);
    }
    free(pids);
    free(nums);
    return 0;
}

