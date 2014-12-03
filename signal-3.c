/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração do envio de um sinal (SIGTERM) de um processo
  para outro.
**/


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>


int main(int argc, char** argv){
    int pid = fork();
    if(pid == -1){
        perror("Fork error:");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ /** Código do Filho **/
        for(;;){
            printf("Filho: Omelette du fromage }:-D.\n");
            sleep(1);
        }
    }
    else{ /** Código do Pai **/
        printf("Pai: Vou dormir. ZzZZzzzZzZzZZZ\n");
        sleep(10);
        printf("Pai: Acordei!\n");
        printf("Pai: Que zoeira é essa!\n");
        printf("Pai: Cala a boca!\n");
        kill(pid,SIGTERM);
    }
    return(0);
}

