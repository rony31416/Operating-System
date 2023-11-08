#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
//print 1 to 10
//child 5 ta parent 5 ta

int main(int argc,char* argv[])
{
    int id = fork();
    int n;
    if(id == 0)
    {
        n = 6;//child 1 - 5
    }
    else {
        n = 1;// parent 6 -10
    }

    if(id == 1)
    {
        wait(NULL);
    }


    int i ;
    for(int i = n ; i < n+5 ; i++)
     {
        printf("%d ",i);
       // sleep(1);
        fflush(stdout);
     }
   // printf("hello world from id %d \n",id);
    return;
}
