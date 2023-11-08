#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main(int argc,char* argv[])
{
    int id = fork();


   if(id != 0) {
         int a = fork();
          printf("value of a : %d\n",a);
    }
    //int id2 = fork();


    printf("hello world from id %d \n",id);
    return;
}
