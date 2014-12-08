#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N (10)
#define N_THREADS (4)
#define MAX (3)


pthread_mutex_t prod_mutex;
int prod = 0;


typedef struct thread_arg{
	int* A;
	int* B;
	int size;
	int id;
}thread_arg;


void* prod_escalar(void* arg){
	int i;
	int begin;
	int end;
	int local_prod=0;
	int block_size = N/N_THREADS;
	thread_arg* t_arg = (thread_arg*) arg; 
	begin = t_arg->id * block_size;
	end = t_arg->id == (N_THREADS -1) ? t_arg->size : begin+block_size;
	for(i=begin; i<end ;i++){
		local_prod += t_arg->A[i] * t_arg->B[i];
	}
	printf("Thread %d -> Produto local: %d\n",t_arg->id,local_prod);
	pthread_mutex_lock(&prod_mutex);
	prod+=local_prod;
	pthread_mutex_unlock(&prod_mutex);
	pthread_exit(NULL);
}


int main(void){
	int i;
	int A[N],B[N];
	pthread_t threads[N_THREADS];
	int rv;
	thread_arg t_arg[N_THREADS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    srand(time(NULL));
    for(i=0;i<N;i++){
    	A[i] = rand()% MAX;
    	B[i] = rand()% MAX;
    }

    for(i=0;i<N;i++){
    	printf("%d ",A[i]);
    }
    printf("\n");
    for(i=0;i<N;i++){
    	printf("%d ",B[i]);
    }
    printf("\n");
    for(i=0;i<N_THREADS;i++){
    	t_arg[i].id = i;
    	t_arg[i].A = A;
    	t_arg[i].B = B;
    	t_arg[i].size = N;
    	pthread_create(&threads[i], &attr, prod_escalar, (void*) &t_arg[i]);
    }
    for(i=0;i<N_THREADS;i++){
    	pthread_join(threads[i],(void*) &rv);
    }
    printf("O produto escalar é: %d\n",prod);
	pthread_exit(NULL);
}