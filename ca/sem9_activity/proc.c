#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <timeout>\n", argv[0]);
        return 1;
    }
    int timeout = atoi(argv[1]);
    pid_t pid = getpid();
    int i = 0;
    for (;;) {
        printf("%d: %d\n", pid, i++);
        sleep(timeout);
    }
    return 0;
}
