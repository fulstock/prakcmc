#include <stdio.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>

struct Mesg 
{
    long mtype;
    long long x[2];
};

int
main(int argc, char *argv[])
{
    key_t key;
    int nproc;
    long long value1, value2, maxval;
    key = (key_t) strtol(argv[1], NULL, 10);
    nproc = (int) strtol(argv[2], NULL, 10);
    value1 = strtoll(argv[3], NULL, 10);
    value2 = strtoll(argv[4], NULL, 10);
    maxval = strtoll(argv[5], NULL, 10);
    int msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
    if (msgid < 0) {
        exit(1);
    }
    pid_t *pids = calloc(nproc, sizeof(pid_t));
    for (int i = 0; i < nproc; i++) {
        pids[i] = fork();
        if (!pids[i]) {
            free(pids);
            while (1) {
                long long x3;
                struct Mesg mes;
                if (msgrcv(msgid, &mes, sizeof(mes.x), (long) i + 1, 0) == -1) {
                    break;
                }
                x3 = mes.x[0] + mes.x[1];
                printf("%d %lld\n", i, x3);
                fflush(stdout);
                if (x3 > maxval) {
                    msgctl(msgid, IPC_RMID, 0);
                    break;
                }
                mes.mtype = x3 % nproc + 1;
                mes.x[0] = mes.x[1];
                mes.x[1] = x3;
                msgsnd(msgid, &mes, sizeof(mes.x), 0);
            }
            exit(0);
        } else if (pids[i] < 0) {
            for (int k = 0; k < i; k++) {
                kill(pids[k], SIGTERM);
            }
            while (wait(NULL) != -1) {}
            free(pids);
            msgctl(msgid, IPC_RMID, 0);
            exit(1);
        }
    }
    free(pids);
    struct Mesg startmsg = 
    {
        .mtype = 1,
        .x = {value1, value2}
    };
    msgsnd(msgid, &startmsg, sizeof(startmsg.x), 0);
    while (wait(NULL) != -1) {}
    return 0;
}

