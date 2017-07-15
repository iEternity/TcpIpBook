#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>

#define NUM_THREAD 100

long long sum = 0;
pthread_mutex_t mutex;

void* thread_increase(void* arg){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<50000000;i++){
        sum += 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void* thread_decrease(void* arg){
    pthread_mutex_lock(&mutex);
    for(int i=0;i<50000000;i++){
        sum -= 1;
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

int main(){
    pthread_mutex_init(&mutex, NULL);
    pthread_t t_id[NUM_THREAD];

    for(int i=0;i<NUM_THREAD;i++){
        if(i%2 == 0){
            pthread_create(&t_id[i], NULL, thread_increase, NULL);
        }
        else{
            pthread_create(&t_id[i], NULL, thread_decrease, NULL);
        }
    }

    for(int i=0;i<NUM_THREAD;i++){
        pthread_join(t_id[i], NULL);
    }

    printf("sum: %lld \n", sum);

    pthread_mutex_destroy(&mutex);
    return 0;
}