#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char* argv[])
{

    int id1 = fork();
    int id2 = fork();
    if( id1 == 0)
    {
         if(id2 == 0)
         {
             printf("child of child process\n");
         }
         else{
            printf("this is the child process of parent preocess\n");
         }
    }
    else{
        if(id2 == 0)
        {
            printf("this is also child process of parent preocess after second fork\n");
        }
        else{
            printf("this is the parent process\n");
        }

    }

    while(wait(NULL) != -1 ) {
        printf("wait child for finish\n");
    }


    return;
}


