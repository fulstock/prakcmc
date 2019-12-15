#include <sys/stat.h>

enum
{
    RIGHTS_MASK = 7,
    S_USR = 6,
    S_GRP = 3,
    S_OTH = 0
};

struct Task
{
    unsigned uid;
    int gid_count;
    unsigned *gids;
};

int isAccessed(int accessbits, int rights) {
    return ((accessbits & rights) == accessbits);
}

int getExecUsId(int mode, int bit_usr) {
    return (mode & (RIGHTS_MASK << bit_usr)) >> bit_usr;
}

int myaccess(const struct stat *stb, const struct Task *task, int access)
{
    int bits = getExecUsId(stb->st_mode, S_USR);
    if (!task->uid) {
        return 1;
    }
    if (task->uid == stb->st_uid) {
        return isAccessed(access, bits);
    }
    bits = getExecUsId(stb->st_mode, S_GRP);
    for (int i = 0; i < task->gid_count; i++) {
        if (task->gids[i] == stb->st_gid) {
            return isAccessed(access, bits);
        }
    }
    bits = getExecUsId(stb->st_mode, S_OTH);
    return isAccessed(access, bits);
}

