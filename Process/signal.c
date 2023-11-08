#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

int main() {

    int id = fork();
    if(id == -1)
    {
        return 1;
    }

    if(id == 0)
    {
        while(1) {
            printf("Some text goes here\n");
            usleep(500000);
        }
    }
    else{

        sleep(1);
        kill(id,SIGKILL);
        wait(NULL);
    }


    return 0;
}
