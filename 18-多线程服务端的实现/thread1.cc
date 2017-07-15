#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

void* thread_proc(void* arg){
    int count = *(int*)arg;
    for(int i=0;i<count;i++){
        puts("thread run");
        sleep(1);
    }
    return 0;
}

int main(int argc, char* argv[]){
    pthread_t t_id;
    int num = 5;
    if(pthread_create(&t_id, NULL, &thread_proc, &num) !=0){
        perror("pthread_create error!");
        exit(1);
    }

    sleep(10);

    return 0;
}