#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

void signal_function(int sig)
{
    printf("Stop not allowed\n");
}

int main(int argc, char* argv[])
{
    signal(SIGTSTP, &signal_function); // Set up signal handler for SIGTSTP

    int n;
    printf("Input a number: ");
    scanf("%d", &n);
    printf("You inputted %d\n", n);

    while(1)
    {

    }

    return 0;
}
