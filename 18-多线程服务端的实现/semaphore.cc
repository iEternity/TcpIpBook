#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<semaphore.h>
#include<pthread.h>

int num = 0;
sem_t sem1,sem2;

void* read(void* arg){
    for(int i=0;i<5;i++){
        sem_wait(&sem1);
        puts("Please input a number:");
        scanf("%d", &num);
        sem_post(&sem2);
    }
    return 0;
}

void* accu(void* arg){
    int sum = 0;
    for(int i=0;i<5;i++){
        sem_wait(&sem2);
        sum += num;
        sem_post(&sem1);
    }

    printf("sum: %d \n", sum);
    return 0;
}

int main(){
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);

    pthread_t t_id[2];
    pthread_create(&t_id[0], NULL, read, NULL);
    pthread_create(&t_id[1], NULL, accu, NULL);

    pthread_join(t_id[0], NULL);
    pthread_join(t_id[1], NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}