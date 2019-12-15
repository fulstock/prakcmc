#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

struct Node
{
    int32_t key;
    int32_t left_idx;
    int32_t right_idx;
};

void revorder(int fd, int32_t node_index)
{
    if (!node_index) {
        return;
    }
    struct Node node;
    if (lseek(fd, node_index * sizeof(node), SEEK_SET) == -1) {
        return;
    }
    if (read(fd, &node, sizeof(node)) != sizeof(node)) {
        return;
    }
    revorder(fd, node.right_idx);
    printf("%d ", node.key);
    revorder(fd, node.left_idx);
}
int
main(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    struct Node root_node;
    if (read(fd, &root_node, sizeof(root_node)) != sizeof(root_node)) {
        return 1;
    }
    revorder(fd, root_node.right_idx);
    printf("%d ", root_node.key);
    revorder(fd, root_node.left_idx);
    printf("\n");
    return 0;
}

