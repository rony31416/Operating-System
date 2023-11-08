#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include <time.h>


int main(int argc,char* argv[])
{

    int fd[2];
    //fd[0]  -   read
    //fd[1]  -   write

    if(pipe(fd) == -1)
    {
        printf("Error! to open pipe...\n");
        return 1;
    }

    int id = fork();
    if(id == 0)
    {
        close(fd[0]);
        int arr[10];
        srand(time(NULL));

        for(int i = 0 ; i <  10 ; i++)
        {
            int y = rand() % 10;
            printf("Y : %d\n",y);
            if(write(fd[1],&y,sizeof(int)) == -1)
            {
                return 2;
            }

        }
        close(fd[1]);
    }
    else
    {
        int  sum = 0;
        int a[10];
        close(fd[1]);
        for(int i = 0 ; i < 10 ; i++ )
        {
            if(read(fd[0], &a[i], sizeof(int)) == -1)
            {
                return 3;
            }
            sum+=a[i];
        }
        printf("parent x from y : %d\n",sum);
        close(fd[1]);
    }
    return;
}


