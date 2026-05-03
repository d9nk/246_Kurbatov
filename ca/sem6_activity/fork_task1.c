#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        printf("Hello from Child (pid=%d)\n", getpid());
        pid_t pid2 = fork();
        if (pid2 < 0) {
            perror("fork");
            return 1;
        } else if (pid2 == 0) {
            printf("Hello from Grandchild (pid=%d)\n", getpid());
        } else {
            wait(NULL);
            printf("Child done (pid=%d)\n", getpid());
        }
    } else {
        wait(NULL);
        printf("Hello from Parent (pid=%d)\n", getpid());
    }
    return 0;
}
