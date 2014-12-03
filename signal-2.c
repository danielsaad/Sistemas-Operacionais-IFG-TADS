/**
  Autor: Daniel Saad Nogueira Nunes
  Descrição: Um processo que captura o sinal SIGALRM periodicamente.
**/
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
void sigalrm_handler(int sig){
    const char* msg = "Trim trim trim trim!\n";
    write(0,msg,strlen(msg));
    alarm(2);
}

int main(int argc, char** argv){
    struct sigaction sa;
    sa.sa_handler = sigalrm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGALRM,&sa,NULL)==-1){
        perror("Sigaction: ");
        exit(EXIT_FAILURE);
    }
    alarm(2);
    for(;;);
    return(0);
}
