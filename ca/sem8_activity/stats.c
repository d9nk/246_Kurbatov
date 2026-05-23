#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static int *nums;
static int count;
static double avg;
static int min_val;
static int max_val;

static void *avg_thread(void *arg) {
    long sum = 0;
    for (int i = 0; i < count; i++) sum += nums[i];
    avg = (double)sum / count;
    return NULL;
}

static void *min_thread(void *arg) {
    int m = nums[0];
    for (int i = 1; i < count; i++) if (nums[i] < m) m = nums[i];
    min_val = m;
    return NULL;
}

static void *max_thread(void *arg) {
    int m = nums[0];
    for (int i = 1; i < count; i++) if (nums[i] > m) m = nums[i];
    max_val = m;
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s n1 n2 n3 ...\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    nums = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) nums[i] = atoi(argv[i + 1]);

    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, avg_thread, NULL);
    pthread_create(&t2, NULL, min_thread, NULL);
    pthread_create(&t3, NULL, max_thread, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("The average value is %.0f\n", avg);
    printf("The minimum value is %d\n", min_val);
    printf("The maximum value is %d\n", max_val);

    free(nums);
    return 0;
}
