/**
  Autor: https://computing.llnl.gov/tutorials/pthreads/
**/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

volatile int x=1; /** Variáveis globais são compartilhadas pelas threads.**/

void* imprime_x(void* arg){
    int id = (int) arg;
    printf("Sou a thread %d\n",id);
    for(;;){
        printf("x");
    }
    pthread_exit(NULL);
}

int main (int argc, char *argv[]){
    pthread_t thread;
    pthread_attr_t attr;
    int id  = 0;
    int rv;

    /* For portability, explicitly create threads in a joinable state */
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_create(&thread, &attr, imprime_x, (void *) id);

    /* Wait for all threads to complete */
    pthread_join(thread, (void*) &rv);
    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

}



