#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

enum 
{ 
    NUM_AMOUNT = 10,
    INIT_SIZE = 128
};

char *getline2(FILE *f)
{
    if (!f) { 
        errno = EINVAL;
        return NULL;
    }
    size_t size = 16;
    char *str = malloc(size * sizeof(*str));
    if (!str) { 
        errno = ENOMEM;
        free(str);
        return NULL;
    }
    int c;
    size_t symb_read = 0;
    while ((c = getc(f)) != EOF) {
        symb_read++;
        if (symb_read >= size) {
            char *tmp = realloc(str, (size << 1) + 1);
            if (!tmp) { 
                errno = ENOMEM;
                free(str);
                return NULL;
            }
            str = tmp;
            size = (size << 1) + 1;
        }
        if (c == '\n' || c == '\r') {
            symb_read--;
            break;
        }
        str[symb_read - 1] = (char) c;    
    }
    if (symb_read == 0) {
        errno = EIO;
        free(str);
        return NULL;
    }
    str[symb_read] = '\0';
    return str;
}

int
main(void)
{
    char *path = NULL;
    FILE *fin = NULL;   
    unsigned long long num_count[NUM_AMOUNT];
    memset(num_count, 0, sizeof(num_count));
    path = getline2(stdin);  
    if (path && !errno) {
        errno = 0;
        fin = fopen(path, "r");
    }
    if (!errno && fin && path){
        char buf[INIT_SIZE];
        while (fgets(buf, sizeof(buf), fin)) {
            char *ptr = buf;
            while (*ptr) {
                if (*ptr >= '0' && *ptr <= '9') {
                    num_count[*ptr - '0']++;
                }
                ptr++;
            }
        }
    }
    for (int i = 0; i < NUM_AMOUNT; i++) {
        printf("%d %llu\n", i, num_count[i]);
    }
    if (path) {
        free(path);
    }
    if (fin) {
        fclose(fin);
    }
    return 0;
}

