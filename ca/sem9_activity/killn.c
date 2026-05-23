#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>

static const char *signals[] = {
    NULL,
    "HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT", "BUS", "FPE",
    "KILL", "USR1", "SEGV", "USR2", "PIPE", "ALRM", "TERM", "STKFLT",
    "CHLD", "CONT", "STOP", "TSTP", "TTIN", "TTOU", "URG", "XCPU",
    "XFSZ", "VTALRM", "PROF", "WINCH", "IO", "PWR", "SYS"
};

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s PID NAME\n", argv[0]);
        return 1;
    }

    pid_t pid = atoi(argv[1]);
    const char *name = argv[2];
    if (strncmp(name, "SIG", 3) == 0) name += 3;

    int sig = -1;
    int n = sizeof(signals) / sizeof(signals[0]);
    for (int i = 1; i < n; i++) {
        if (strcmp(name, signals[i]) == 0) {
            sig = i;
            break;
        }
    }

    if (sig == -1) {
        printf("No such signal\n");
        return 1;
    }

    if (kill(pid, sig)) {
        perror("kill");
        return 1;
    }
    return 0;
}
