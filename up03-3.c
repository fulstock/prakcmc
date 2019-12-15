#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum 
{
    PERCENT = 100,
    ROUND_SCALE = 10000,
    FIRST_ARG = 2
};

int
main(int argc, char *argv[])
{
    double x;
    double course;
    char *end;
    course = strtod(argv[1], &end);
    for (int i = FIRST_ARG; i < argc; i++) {
        x = strtod(argv[i], &end);
        course *= (x + PERCENT) / PERCENT;
        course = round(course * ROUND_SCALE) / ROUND_SCALE;
    }
    printf("%.4lf\n", course);
}

