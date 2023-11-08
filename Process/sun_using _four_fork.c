#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int main() {

    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);

    int arr[]={1,2,3,4,5,6,7,8,9,10,11,12};
    int sizeOfArr=sizeof(arr)/sizeof(int);

    int id1, id2;
    id1=fork();
    id2=fork();
    if(id1==-1)
    {
        printf("fork 1 caused error!\n");
        return 1;
    }
    if(id2==-1)
    {
        printf("fork 2 caused error!\n");
        return 2;
    }

    int start, end;
    int sum=0;
    if(id1!=0 && id2!=0)    //parent process
    {
        start=0;
        end=start+sizeOfArr/4;
    }
    else if(id1==0 && id2!=0)   //process x
    {
        start=sizeOfArr/4;
        end=start+sizeOfArr/4;
    }
    else if(id1!=0 && id2==0)   //process y
    {
        start=(sizeOfArr/4)*2;
        end=start+sizeOfArr/4;
    }
    else                        //process z
    {
        start=(sizeOfArr/4)*3;
        end=sizeOfArr;
    }

    // we set the start and end pointers for all processes

    for(int i=start; i<end; i++)
    {
        sum+=arr[i];
    }

    printf("Partial sum is %d\n", sum);


    if(id1!=0 && id2!=0)    //parent process
    {
        int sum1, sum2;
        close(fd1[1]);
        close(fd2[1]);
        read(fd1[0], &sum1, sizeof(sum1));
        read(fd1[0], &sum2, sizeof(sum2));
        int totalSum=sum+sum1+sum2;
        printf("Total sum is %d\n",totalSum);
        close(fd1[0]);
        close(fd2[0]);
    }
    else if(id1==0 && id2!=0)   //process x
    {
        int sumFromZ=0;
        close(fd2[1]);
        read(fd2[0], &sumFromZ, sizeof(sumFromZ));
        close(fd2[0]);
        // wait(NULL);
        int totalSum=sum+sumFromZ;
        close(fd1[0]);
        write(fd1[1], &totalSum, sizeof(totalSum));
        close(fd1[1]);
    }
    else if(id1!=0 && id2==0)   //process y
    {
        close(fd1[0]);
        write(fd1[1], &sum, sizeof(sum));
        close(fd1[1]);
    }
    else                        //process z
    {
        close(fd2[0]);
        write(fd2[1], &sum, sizeof(sum));
        close(fd2[1]);

    }




    return 0;
}
