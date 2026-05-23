#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define n 1024

double A[n][n];
double B[n][n];
double C[n][n];

float tdiff(struct timeval *start, struct timeval *end) {
    return (end->tv_sec - start->tv_sec) +
           1e-6 * (end->tv_usec - start->tv_usec);
}

static void *row_thread(void *arg) {
    int i = *(int *)arg;
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
    return NULL;
}

int main(void) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = (double)rand() / RAND_MAX;
            B[i][j] = (double)rand() / RAND_MAX;
            C[i][j] = 0;
        }
    }

    pthread_t *threads = malloc(n * sizeof(pthread_t));
    int *ids = malloc(n * sizeof(int));

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (int i = 0; i < n; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, row_thread, &ids[i]);
    }
    for (int i = 0; i < n; i++) pthread_join(threads[i], NULL);

    gettimeofday(&end, NULL);
    printf("%0.6f\n", tdiff(&start, &end));

    free(threads);
    free(ids);
    return 0;
}
