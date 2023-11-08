#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

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
        int x;
        printf("Enter a number : ");
        scanf("%d",&x);

        int wr = write(fd[1],&x,sizeof(int));

        if( wr == -1)
        {
            printf("Error to writing on the file \n");
        }
        close(fd[1]);
    }
    else{
        //parent process will read
        close(fd[1]);
        int y;
        if(read(fd[0],&y,sizeof(int)) == -1)
        {
            printf("Error to reading from file is %y\n",y);
        }
          close(fd[0]);

        printf("this value is from child process : %d\n",y);
    }


    return;
}


