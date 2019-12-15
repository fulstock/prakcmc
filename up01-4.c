#include <ctype.h>
int
mystrspccmp(const char *str1, const char *str2)
{
    unsigned char *s1 = (unsigned char*) str1;
    unsigned char *s2 = (unsigned char*) str2;
    unsigned char c1 = (unsigned char) *s1++;
    unsigned char c2 = (unsigned char) *s2++;
    while (1) {
        while (isspace(c1)) {
            c1 = (unsigned char) *s1++;
        }
        while (isspace(c2)) {
            c2 = (unsigned char) *s2++;
        }
        if (c1 == '\0' || c1 != c2) {
            return c1 - c2;
        }
        c1 = (unsigned char) *s1++;
        c2 = (unsigned char) *s2++;
    }
}

