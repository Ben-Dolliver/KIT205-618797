#include <stdio.h>
#include "time.h"

main() {
    long n;
    printf("Enter a value for n\n");
    scanf_s("%d", &n);

    long base[] = { 1, 2, 5 };

    for (long scale = 1; scale <= 10000000; scale *= 10) {

        for (int i = 0; i < 3; i++) {

            long n = base[i] * scale;
            printf("n is currently: %ld\n", n);
            clock_t start = clock();
            f7(n);
            clock_t diff = clock() - start;
            long msec = diff * 1000 / CLOCKS_PER_SEC;
            printf("Operation took %d milliseconds\n\n", msec);

            if (n > 10000000)
                break;

        }
    }

    //clock_t start = clock();
    //f1(n);
    //clock_t diff = clock() - start;
    //long msec = diff * 1000 / CLOCKS_PER_SEC;
    //printf("Operation took %d milliseconds\n\n", msec);

}

long f1(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < n; j++) {
            k++;
        }
    }
    return k;
}

long f2(long n) {
    long k = 0;
    for (long i = 0; i < n; i++) {
        for (long j = 0; j < i; j++) {
            k++;
        }
        for (long t = 0; t < 10000; t++) {
            k++;
        }
    }
    return k;
}

long f3(long n) {
    if (n > 0) {
        f3(n / 2);
        f3(n / 2);
    }
    return n;
}

long f4(long n) {
    if (n > 0) {
        f4(n / 2);
        f4(n / 2);
        f2(n);
    }
    return n;
}

long f5(long n) {
    long k = 0;
    for (long i = 0; i < 10; i++) {
        long j = n;
        while (j > 0) {
            f1(1000);
            k++;
            j = j / 2;
        }
    }
    return k;
}

long f6(long n) {
    f2(n);
    f3(n);
    f5(n);
    return n;
}

long f7(long n) {
    long k = 0;
    for (long i = 0; i < f1(n); i++) {
        k++;
    }
    for (long j = 0; j < n; j++) {
        k++;
    }
    return k;
}