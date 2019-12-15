#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

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
        str[symb_read - 1] = (char) c;
        if (c == '\n') {
            break;
        }
    }
    if (symb_read == 0) {
        errno = EIO;
        free(str);
        return NULL;
    }
    str[symb_read] = '\0';
    return str;
}

