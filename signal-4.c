/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração do envio de um sinal (SIGTERM) de um processo
  para outro e a sua captura.
**/


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sigterm_handler(int sig){
    const char* str = "Filho: Tu não manda em mim, rapá!\n";
    write(0,str,strlen(str));
}

int main(int argc, char** argv){
    int pid;
    struct sigaction sa;

    pid = fork();
    if(pid == -1){
        perror("Fork error:");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ /** Código do Filho **/
        sa.sa_handler = sigterm_handler;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        if(sigaction(SIGTERM,&sa,NULL)==-1){
            perror("Sigaction: ");
            exit(EXIT_FAILURE);
        }
        for(;;){
            printf("Filho: Omelette du fromage }:-D.\n");
            sleep(1);
        }
    }
    else{ /** Código do Pai **/
        while(1){
            printf("Pai: Vou dormir. ZzZZzzzZzZzZZZ\n");
            sleep(10);
            printf("Pai: Acordei!\n");
            printf("Pai: Que zoeira é essa!\n");
            printf("Pai: Cala a boca!\n");
            kill(pid,SIGTERM);
            sleep(1);
        }
    }
    return(0);
}


