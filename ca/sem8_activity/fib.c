#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static long *fib;
static int n;

static void *fib_thread(void *arg) {
    if (n >= 1) fib[0] = 0;
    if (n >= 2) fib[1] = 1;
    for (int i = 2; i < n; i++) fib[i] = fib[i - 1] + fib[i - 2];
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <count>\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);
    if (n <= 0) return 1;

    fib = malloc(n * sizeof(long));

    pthread_t t;
    pthread_create(&t, NULL, fib_thread, NULL);
    pthread_join(t, NULL);

    for (int i = 0; i < n; i++) printf("%ld ", fib[i]);
    printf("\n");

    free(fib);
    return 0;
}
