#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void * funcCall(void * args) {
    sleep(2);
    printf("%s\n", (char *)args);
}

int main(int argc, char const *argv[])
{
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t thread;
    int fc;
    if((fc = pthread_create(&thread, NULL, funcCall, (void *)"hello")) == 0) {
        printf("Thread Created!\n");
        pthread_join(thread, NULL);
        printf("After Thread Complete!\n");
    }else {
        perror("Thread creation failure!\n");
        exit(-1);
    }


    pthread_exit(NULL);
    return 0;
}
