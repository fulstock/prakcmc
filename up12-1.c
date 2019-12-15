#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    int nproc;
    unsigned long long maxval;
    key_t key;
    nproc = (int) strtol(argv[1], NULL, 10);
    key = (key_t) strtol(argv[2], NULL, 10);
    maxval = (unsigned long long) strtoll(argv[3], NULL, 10);
    int semid = semget(key, nproc, IPC_CREAT | IPC_EXCL | 0600);
    if (semid < 0) {
        exit(1);
    }
    unsigned long long *ptr = mmap(NULL, sizeof(*ptr), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    int *sender = mmap(NULL, sizeof(*sender), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
    *ptr = 0;
    *sender = 0;
    for (int i = 1; i <= nproc; i++) {
        if(!fork()) {
            while (1) {
                struct sembuf block[] = 
                {
                    { .sem_num = i - 1, -1, 0 }
                };
                if (semop(semid, block, sizeof(block) 
                            / sizeof(block[0])) == -1) {
                    break;
                }
                printf("%d %llu %d\n", i, *ptr, *sender);
                fflush(stdout);
                (*ptr)++;
                if (*ptr > maxval) {
                    semctl(semid, 0, IPC_RMID);
                    break;
                }
                *sender = i;
                struct sembuf unlock[] = 
                {
                    { .sem_num = ((*ptr) % nproc) * ((*ptr) % nproc) * 
                        ((*ptr) % nproc) * ((*ptr) % nproc) % nproc, 1, 0 }
                };
                if (semop(semid, unlock, sizeof(unlock) / 
                            sizeof(unlock[0])) == -1) {
                    break;
                }
            }
            exit(0);
        }
    }
    semctl(semid, 0, SETVAL, 1);
    while (wait(NULL) != -1) {}
    return 0;
}

