#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        const char *msg = "Usage: ./task2 <file>\n";
        write(2, msg, strlen(msg));
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return 1;

    struct stat st;
    
    if (fstat(fd, &st) < 0) {
        close(fd);
        return 1;
    }

    off_t size = st.st_size;
    
    if (size == 0) {
        close(fd);
        return 0;
    }

    off_t mid = size / 2;

    
    if (lseek(fd, mid, SEEK_SET) == (off_t)-1) {
        close(fd);
        return 1;
    }

    size_t bufsize = PAGE_SIZE;
    char *buf = (char *)malloc(bufsize);

    
    ssize_t n;
    int done = 0;
    
    while (!done && (n = read(fd, buf, bufsize)) > 0) {
        ssize_t i = 0;
        
        while (i < n && buf[i] != '\n')
            i++;
        if (i < n) {
        
            write(1, buf, i + 1);
            done = 1;
        } else {
            write(1, buf, n);
        }
    }

    free(buf);
    close(fd);
    return 0;
}
