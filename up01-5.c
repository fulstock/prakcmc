#include <stdio.h>
#include <stdlib.h>

enum { MAX_N = 2000 };

int
main(void)
{
    int n, varc;
    varc = scanf("%d", &n);
    if (varc != 1) {
        return 1;
    }
    if (n <= 1 || n >= MAX_N) {
        return 1;
    }
    for (int i = 2; i * i < n; i++) {
        if (n % i == 0) {
            return 1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        printf("0 ");
    }
    printf("\n");
    int first_row[MAX_N];
    int prev_row[MAX_N];
    first_row[0] = 1;
    prev_row[0] = 1;
    for (int i = 1; i < n - 1; i++) {
        first_row[i] = (n - (n / (i + 1)) * first_row[n % (i + 1) - 1] % n) % n;
        prev_row[i] = first_row[i];
    }
    for(int i = 0; i < n - 1; i++) {
        printf("%d ", first_row[i]);
    }
    printf("\n");
    int tmp;
    for(int i = 1; i < n - 1; i++) {
        for(int j = 0; j < n - 1; j++) {
            tmp = (first_row[j] + prev_row[j]) % n;
            prev_row[j] = tmp;
            printf("%d ", tmp);
        }
        printf("\n");
    }
    return 0;
}
