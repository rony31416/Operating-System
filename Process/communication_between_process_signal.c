#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<signal.h>


void signal_handler(int sig)
{
     printf("multiplication is nasically addition\n");
}
int main(int argc,char* argv[])
{

    int pid = fork();
    if(pid == -1)
    {
       return 1;
    }

    if(pid == 0)
    {
       sleep(5);
       kill(getpid(),SIGUSR1);

    }
     else{

       // signal(SIGUSR1,&signal_handler);

       struct sigaction sa;
       sa.sa_flags = SA_RESTART;
       sa.sa_handler = &signal_handler;
       sigaction(SIGUSR1,&sa, NULL);


        int x;
        printf("What is the result of 3 X 5 : ");
        scanf("%d",&x);
        if(x == 15)
        {
            printf("Right\n");
        }
        else{
            printf("wrong\n");
        }
        wait(NULL);
     }
    return 0;
}

