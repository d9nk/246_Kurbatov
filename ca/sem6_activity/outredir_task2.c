#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s command output_filename\n", argv[0]);
        return 1;
    }
    int fd = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open");
        return 1;
    }
    close(STDOUT_FILENO);
    dup2(fd, STDOUT_FILENO);
    close(fd);
    execlp(argv[1], argv[1], NULL);
    perror("execlp");
    return 1;
}
