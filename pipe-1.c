/**
    Autor: Beej http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html
    Adaptado por: Daniel Saad Nogueira Nunes
    Descrição: uso de pipes.
**/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char** argv){
    int pfds[2]; /** Descritor de pipes **/
    char buf[30];
    int pid;
    pipe(pfds);
    pid = fork();
    if(pid == -1){
        perror("Fork error: ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        printf("Filho: Escrevendo no pipe.\n");
        write(pfds[1], "teste", 6);
        printf("Filho: saindo.\n");
        exit(0);
    }
    else{
        printf("Pai: lendo do pipe.\n");
        read(pfds[0], buf, 6);
        printf("Pai: li %s \n", buf);
        wait(NULL);
    }
    return 0;
}
