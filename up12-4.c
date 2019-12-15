#include <stdio.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <sys/mman.h>
#include <limits.h>
#include <sys/stat.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    int count = (int) strtol(argv[1], NULL, 10);
    int num = 0;
    int semid = semget(600, count, IPC_CREAT | IPC_EXCL | 0600);
    if (semid < 0) {
        exit(1);
    }
    for (int i = 0; i < count; i++) {
        pid_t pid = fork();
        if (!pid) {
            setbuf(stdin, NULL);
            setbuf(stdout, NULL);
            while (1) {
                struct sembuf blocks[] = 
                {
                    { .sem_num = i, -1, 0 }
                };
                if (semop(semid, blocks, sizeof(blocks) / sizeof(blocks[0])) == -1) {
                    break;
                }
                if (scanf("%d", &num) == EOF) {
                    semctl(semid, 0, IPC_RMID, 0);
                    break;
                }
                printf("%d %d\n", i, num);
                if (num % count < 0) {
                    num = num % count + count;
                } else {
                    num = num % count;
                }
                struct sembuf unlocks[] = 
                {
                    { .sem_num = num, 1, 0 }
                };
                if (semop(semid, unlocks, sizeof(unlocks) / sizeof(unlocks[0])) == -1) {
                    break;
                }
            }
            exit(0);
        }
    }
    semctl(semid, 0, SETVAL, 1);
    while (wait(NULL) != -1) {}
    //semctl(semid, 0, IPC_RMID);
    return 0;
}

