/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração do envio de um sinal (SIGKILL) de um processo
  para outro e a sua impossibilidade de captura.
**/


#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sigkill_handler(int sig){
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
        sa.sa_handler = sigkill_handler;
        sa.sa_flags = 0;
        sigemptyset(&sa.sa_mask);
        if(sigaction(SIGKILL,&sa,NULL)==-1){
            perror("Impossível capturar SIGKILL");
        }
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
        kill(pid,SIGKILL);
        sleep(1);
        printf("Quem manda nessa p**** aqui, sou eu!\n");
    }
    return(0);
}



