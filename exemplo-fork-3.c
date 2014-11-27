/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração de criação de processos usando fork();
  Neste caso, um processo adota o filho do processo pai original.
**/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv){
    int id = 0;
    int rv;
    int pid = fork();
    if(pid == -1){
        perror("Fork error:");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ /** Código do Filho **/
        id = 1;
        printf("Sou o processo FILHO!\n");
        printf("Meu pid é %d!\n",getpid());
        printf("O pid do meu pai é %d.\n",getppid());
        printf("Meu id é %d!\n",id);
        sleep(10); /** Cheque o que houve na tabela de processos **/
    }
    else{ /** Código do Pai **/
        printf("Sou o processo PAI!\n");
        printf("Meu pid é %d!\n",getpid());
        printf("Meu id é %d!\n",id);
    }
    return(0);
}
