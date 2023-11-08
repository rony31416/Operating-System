#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char* argv[])
{

    int id = fork();

    if(id != 0 )
    {
         printf("Currenyt Id : %d \n",getpid());
    }
    if(id == 0)
    {
        printf("current ID %d and parent ID : %d \n",getpid(),getppid());
        sleep(1);
    }


    int  res = wait(NULL);
    if( res ==  -1)
    {
        printf("No child process for execution\n");
    }
    else{
        printf("%d finished execution\n",res);
    }


    return;
}

