#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>

#define PAGE_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 4) {
        const char *msg = "Usage: ./task1 <file> <start_line> <num_lines>\n";
        write(2, msg, strlen(msg));
        return 1;
    }

    const char *filename = argv[1];
    long start = atol(argv[2]);
    long count = atol(argv[3]);

    int fd = open(filename, O_RDONLY);
    if (fd < 0)
        return 1;

    struct stat st;
    if (fstat(fd, &st) < 0) {
        close(fd);
        return 1;
    }

    size_t bufsize = (st.st_size < PAGE_SIZE) ? (size_t)st.st_size : PAGE_SIZE;
    
    if (bufsize == 0) {
        close(fd);
        return 0;
    }

    char *buf = (char *)malloc(bufsize);

    long cur_line = 1;
    long printed = 0;
    int in_range = (cur_line >= start);

    ssize_t n;
    
    while (printed < count && (n = read(fd, buf, bufsize)) > 0) {
        ssize_t i = 0;
        
        while (i < n && printed < count) {
            ssize_t chunk_start = i;

            
            while (i < n && buf[i] != '\n')
                i++;
            
            int has_newline = (i < n);
            
            if (has_newline)
                i++;

            if (in_range) {
                write(1, buf + chunk_start, i - chunk_start);
                
                if (has_newline) {
                    printed++;
                    cur_line++;
                    if (printed >= count) break;
                }
            } else {
                if (has_newline) {
                    cur_line++;
                    if (cur_line >= start) in_range = 1;
                }
            }
        }
    }

    free(buf);
    close(fd);
    return 0;
}
