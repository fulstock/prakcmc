#include <time.h>
#include <stdio.h>
#include <stdlib.h>

enum
{
    INIT_YEAR = 25,
    INIT_MON = 9,
    INIT_DAY = 7,
    SECS_DAY = 86400,
    BASE_YEAR = 1900,
    ARG_COUNT = 3,
    DAYS_YEAR = 360,
    DAYS_MONTH = 30,
    MON_COUNT = 12
};

int
main(void)
{
    struct tm *init_day = calloc(1, sizeof(*init_day));
    init_day->tm_year = INIT_YEAR;
    init_day->tm_mon = INIT_MON;
    init_day->tm_mday = INIT_DAY;
    init_day->tm_isdst = 1;
    time_t init_time = mktime(init_day);
    int year, mon, day;
    struct tm *date = calloc(1, sizeof(*date));
    while (scanf("%d %d %d\n", &year, &mon, &day) == ARG_COUNT) {
        date->tm_year = year - BASE_YEAR;
        date->tm_mon = mon - 1;
        date->tm_mday = day;
        date->tm_isdst = -1;
        unsigned long long diff = (unsigned long long) mktime(date) - init_time;
        diff /= SECS_DAY;
        printf("%llu %llu %llu\n", diff / DAYS_YEAR + 1, 
                (diff / DAYS_MONTH) % MON_COUNT + 1, (diff) % DAYS_MONTH + 1);
    }
    free(date);
    free(init_day);
    return 0;
}

