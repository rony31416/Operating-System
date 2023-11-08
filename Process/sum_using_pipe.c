#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char* argv[])
{

   int arr[] = {1,2,3,4,1,2};
   int size = sizeof(arr) / sizeof(int);
   int start,end;

   int fd[2];

   if(pipe(fd) == -1 )
   {
       printf("Error to creating pipe!\n");
       return 1;
   }

   int id = fork();

   if(id == -1 )
   {
       printf("Error to create fork!\n");
       return 2;
   }

   if(id == 0)
   {
       start = 0;
       end = size/2;
   }
   else
   {
       start = size/2;
       end = size;
   }

   int sum = 0;
   for(int i = start ; i < end ; i++ )
   {
       sum += arr[i];
   }

   printf("Total partial value : %d\n",sum);


   if(id == 0)
   {
      close(fd[0]);
      int wr =  write(fd[1],&sum,sizeof(sum));
      if(wr == -1)
      {
          printf("Error to write\n");
      }
      close(fd[1]);
   }
   else{

       close(fd[1]);
       int sumFromChild;
       int rd = read(fd[0],&sumFromChild,sizeof(int));
       if(rd == -1)
       {
           printf("Erron on read from fd[0\n");
       }
       close(fd[0]);
       printf("Total sum : %d \n" ,sum +sumFromChild);

   }


    return 0;
}


