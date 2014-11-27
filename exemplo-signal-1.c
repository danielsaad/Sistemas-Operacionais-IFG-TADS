/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Demonstração da captação do sinal SIGINT e a sobrescrita do
  comportamento padrão deste sinal.
**/

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

void sigint_handler(int sig){
    const char* msg = "Capturei sua interrupção }:-)\n";
    write(0,msg,strlen(msg));
}

int main(int argc, char** argv){
    struct sigaction sa;
    sa.sa_handler = sigint_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGINT,&sa,NULL)==-1){
        perror("Sigaction: ");
        exit(EXIT_FAILURE);
    }
    for(;;);
    return(0);
}
