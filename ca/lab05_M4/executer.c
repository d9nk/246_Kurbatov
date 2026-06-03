#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGS 64

void parse(char *str, char **argv) {
    int i = 0;
    char *tok = strtok(str, " ");
    while (tok != NULL && i < MAX_ARGS - 1) {
        argv[i++] = tok;
        tok = strtok(NULL, " ");
    }
    argv[i] = NULL;
}

int main(int argc, char *argv[]) {
    for (int c = 1; c < argc; c++) {
        char *cmd[MAX_ARGS];
        parse(argv[c], cmd);

        int pfd[2];
        pipe(pfd);

        if (fork() == 0) {
            dup2(pfd[1], STDOUT_FILENO);
            close(pfd[0]);
            close(pfd[1]);
            execvp(cmd[0], cmd);
            perror("execvp");
            exit(1);
        }

        if (fork() == 0) {
            dup2(pfd[0], STDIN_FILENO);
            close(pfd[0]);
            close(pfd[1]);
            execlp("wc", "wc", "-c", NULL);
            perror("execlp");
            exit(1);
        }

        close(pfd[0]);
        close(pfd[1]);
        wait(NULL);
        wait(NULL);
    }
    return 0;
}
