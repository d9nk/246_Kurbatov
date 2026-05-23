#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

static const char *signals[] = {
    NULL,
    "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE",
    "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
    "CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU",
    "XFSZ", "VTALRM", "PROF", "WINCH", "IO", "PWR", "SYS"
};

static int name_to_signum(const char *name) {
    if (strncmp(name, "SIG", 3) == 0) name += 3;
    int n = sizeof(signals) / sizeof(signals[0]);
    for (int i = 1; i < n; i++)
        if (strcmp(name, signals[i]) == 0) return i;
    return -1;
}

static void handler(int sig) {
    printf("[Caught: %s]", strsignal(sig));
    fflush(stdout);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s timeout SIG1 SIG2 ...\n", argv[0]);
        return 1;
    }

    int timeout = atoi(argv[1]);

    for (int i = 2; i < argc; i++) {
        int s = name_to_signum(argv[i]);
        if (s == -1) {
            printf("No such signal: %s\n", argv[i]);
            continue;
        }
        signal(s, handler);
    }

    pid_t pid = getpid();
    int i = 0;
    for (;;) {
        printf("%d: %d\n", pid, i++);
        sleep(timeout);
    }
    return 0;
}
