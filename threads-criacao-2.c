/**
  Autor: https://computing.llnl.gov/tutorials/pthreads/
**/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int x=1; /** Variáveis globais são compartilhadas pelas threads.**/

void* imprime_o(void* arg){
    int id = (int) arg;
    printf("Sou a thread %d\n",id);
    sleep(5);
    for(;;){
        printf("o");
    }
    pthread_exit(NULL);
}

void* imprime_x(void* arg){
    int id = (int) arg;
    printf("Sou a thread %d\n",id);
    sleep(5);
    for(;;){
        printf("x");
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    pthread_t threads[2];
    pthread_attr_t attr;
    int id  = 0;
    int rv;
    int i;

    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&threads[0], &attr, imprime_x, (void *) id);
    pthread_create(&threads[1], &attr, imprime_o, (void *) id);

    /* Wait for all threads to complete */
    for(i=0;i<2;i++){
        pthread_join(threads[i], (void*) &rv);
    }
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

}




