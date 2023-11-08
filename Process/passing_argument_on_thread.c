#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

int prime[10] = {1,2,3,4,5,6,7,8,9,10};
int sum = 0 ;

void *routine(void *arg)
{

    int index = *(int *)arg;

    sum +=prime[index];
    printf("%d ",prime[index]);
    free(arg);
}

int main(int argc,char* argv[])
{
    pthread_t th[10];

    int i;
    for(i = 0  ; i < 10 ; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(th+i,NULL,&routine,a) != 0)
        {
            perror("failed to create thread\n");
        }
    }

    for(i = 0 ; i < 10 ; i++)
    {
         if(pthread_join(th[i],NULL) != 0)
         {
             perror("error to join thread\n");
         }
    }

    printf("\nsum = %d\n",sum);

    return;
}

