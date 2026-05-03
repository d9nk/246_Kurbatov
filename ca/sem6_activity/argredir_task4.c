#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s infile outfile command [args...]\n", argv[0]);
        return 1;
    }
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        int in = open(argv[1], O_RDONLY);
        if (in < 0) {
            perror("open infile");
            return 1;
        }
        int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
        if (out < 0) {
            perror("open outfile");
            return 1;
        }
        dup2(in, STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        close(in);
        close(out);
        execvp(argv[3], &argv[3]);
        perror("execvp");
        return 1;
    } else {
        int wstatus;
        wait(&wstatus);
        printf("%d\n", WEXITSTATUS(wstatus));
    }
    return 0;
}
