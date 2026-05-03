#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s command1 command2 [args...]\n", argv[0]);
        return 1;
    }
    int pfd[2];
    if (pipe(pfd) == -1) {
        perror("pipe");
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        close(pfd[1]);
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        return 1;
    }
    close(pfd[1]);
    dup2(pfd[0], STDIN_FILENO);
    close(pfd[0]);
    execvp(argv[2], &argv[2]);
    perror("execvp");
    return 1;
}
