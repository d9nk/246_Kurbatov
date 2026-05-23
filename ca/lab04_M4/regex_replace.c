#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int main(int argc, char *argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regex> <text> <replacement>\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *text = argv[2];
    const char *repl = argv[3];

    regex_t re;
    if (regcomp(&re, pattern, REG_EXTENDED) != 0) {
        fprintf(stderr, "Invalid regex\n");
        return 1;
    }

    size_t cap = 256;
    size_t len = 0;
    char *buf = malloc(cap);
    buf[0] = '\0';

    size_t repl_len = strlen(repl);
    const char *cur = text;
    regmatch_t m;

    while (regexec(&re, cur, 1, &m, 0) == 0) {
        if (m.rm_so == m.rm_eo) break;

        size_t before = m.rm_so;
        size_t need = len + before + repl_len + 1;
        while (need > cap) {
            cap *= 2;
            buf = realloc(buf, cap);
        }

        memcpy(buf + len, cur, before);
        len += before;
        memcpy(buf + len, repl, repl_len);
        len += repl_len;
        buf[len] = '\0';

        cur += m.rm_eo;
    }

    size_t tail = strlen(cur);
    while (len + tail + 1 > cap) {
        cap *= 2;
        buf = realloc(buf, cap);
    }
    memcpy(buf + len, cur, tail + 1);

    printf("%s\n", buf);

    free(buf);
    regfree(&re);
    return 0;
}
