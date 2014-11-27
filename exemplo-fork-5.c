/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração do fork() seguido de execv()
**/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv){
    int id = 0;
    int rv;
    int pid = fork();
    char* args[] = {"ls", "-la"};
    if(pid == -1){
        perror("Fork error:");
        exit(EXIT_FAILURE);
    }
    else if(pid==0){ /** Código do Filho **/
        execv("/bin/ls", args); /** Carrega o processo ls com argumentos -la **/
    }
    else{ /** Código do Pai **/
        printf("Sou o processo PAI!\n");
        printf("Meu pid é %d!\n",getpid());
        printf("Meu id é %d!\n",id);
        wait(&rv); /** Espera o filho **/
        printf("Meu filhão de pid %d já terminou com código %d.\n",pid,rv);
    }
    return(0);
}
