#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


#define NUMBER_OF_THREAD 16
pthread_mutex_t mutx;
sem_t semaphore;
void *routine(void *args)
{
    printf("(%d) Watting the hte login queue\n",*(int*)args);
    pthread_mutex_lock(&mutx);
    sem_wait(&semaphore);
    printf("(%d) Logged in\n",*(int*)args);
    sleep(rand() % 5 + 1) ;
    printf("(%d) Logged out \n",*(int*)args);
    sem_post(&semaphore);
     pthread_mutex_unlock(&mutx);
    free(args);

}

int main(int argc,char* argv[])
{
    pthread_t th[NUMBER_OF_THREAD];
    sem_init(&semaphore, 0 , 12);
    pthread_mutex_init(&mutx,NULL);



    int i;
    for(i = 0  ; i < NUMBER_OF_THREAD ; i++)
    {
        int* a = malloc(sizeof(int));
        *a = i;
        if(pthread_create(th+i,NULL,&routine,a) != 0)
        {
            perror("failed to create thread\n");
        }
    }

    for(i = 0 ; i < NUMBER_OF_THREAD ; i++)
    {
         if(pthread_join(th[i],NULL) != 0)
         {
             perror("error to join thread\n");
         }
    }
    sem_destroy(&semaphore);

    return;
}

