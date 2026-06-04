#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define THREADS 4

static int *arr;
static int N;
static long sum = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int from;
    int to;
} range_t;

static void *worker(void *arg) {
    range_t *r = (range_t *)arg;
    long local = 0;
    for (int i = r->from; i < r->to; i++) local += arr[i];

    pthread_mutex_lock(&mtx);
    sum += local;
    pthread_mutex_unlock(&mtx);
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <N>\n", argv[0]);
        return 1;
    }

    N = atoi(argv[1]);
    if (N < 16) {
        fprintf(stderr, "N must be >= 16\n");
        return 1;
    }

    srand(time(NULL));
    arr = malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) arr[i] = rand() % 100;

    printf("Array: ");
    for (int i = 0; i < N; i++) printf("%d ", arr[i]);
    printf("\n");

    pthread_t threads[THREADS];
    range_t ranges[THREADS];
    int chunk = N / THREADS;

    for (int i = 0; i < THREADS; i++) {
        ranges[i].from = i * chunk;
        ranges[i].to = (i == THREADS - 1) ? N : (i + 1) * chunk;
        pthread_create(&threads[i], NULL, worker, &ranges[i]);
    }

    for (int i = 0; i < THREADS; i++) pthread_join(threads[i], NULL);

    printf("sum = %ld\n", sum);

    free(arr);
    return 0;
}
