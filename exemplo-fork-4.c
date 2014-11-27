/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração de criação de múltiplos processos usando fork();
**/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char** argv){
    int rv;
    int i;
    int id = 0;
    int pid=1;
    const int NUMERO_DE_PROCESSOS = 10;
    int pid_filhos[NUMERO_DE_PROCESSOS];
    for(i=0;i<NUMERO_DE_PROCESSOS;i++){
        if(pid>0){
            pid = fork();
            if(pid ==-1){
                perror("Fork error: ");
                exit(EXIT_FAILURE);
            }
            else if(pid > 0){
                pid_filhos[i] = pid;
            }
            else{
                id = i+1;
            }
        }
    }
    printf("Sou o processo de identificador %d e pid %d.\n",id,getpid());
    sleep(10); /** Olhe a tabela de processos **/
    if(id==0){ /** Processo Pai **/
        for(i=0;i<NUMERO_DE_PROCESSOS;i++){
            waitpid(pid_filhos[id],&rv,0);
            printf("Filhão de pid %d encerrou com código %d.\n",
                   pid_filhos[i],rv);
        }
    }
    return(0);
}
