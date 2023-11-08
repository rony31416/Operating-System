#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t stopped = 0;

void stop_handler(int sig) {
    if (!stopped) {
        printf("Received SIGTSTP (Ctrl+Z) signal. Stopping...\n");
        stopped = 1;
    } else {
        printf("Received SIGTSTP (Ctrl+Z) signal again. Resuming...\n");
        stopped = 0;
    }
}

int main() {
    signal(SIGTSTP, stop_handler); // Set up a handler for the stop signal

    while (1) {
        if (!stopped) {
            printf("Running...\n");
            sleep(1);
        }
    }

    return 0;
}
