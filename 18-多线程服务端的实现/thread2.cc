#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

void* thread_main(void* param){
    int count = *((int*)param);
    for(int i=0;i<count;i++){
        puts("thread run...");
    }

    char* msg = (char*)malloc(sizeof(char)*64);
    strcpy(msg, "hello, I'm thread~\n");
    return (void*)msg;
}

int main(int argc, char* argv[]){
    pthread_t t_id;
    int param = 5;
    void* retParam;
    if(0!=pthread_create(&t_id, NULL, &thread_main, &param)){
        perror("pthread_create error \n");
        exit(1);
    }

    if(0 != pthread_join(t_id, &retParam)){
        perror("pthread_join error \n");
        exit(1);
    }

    puts("in mainThread!");
    printf("Message from thread: %s \n", (char*)retParam);

    free(retParam);
    return 0;
}