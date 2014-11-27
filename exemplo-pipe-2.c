/**
    Autor: Beej http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html
    Adaptado por: Daniel Saad Nogueira Nunes
    Descrição: uso de pipes utilizando stdin e stdout.
**/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char** argv){
    int pfds[2];
    int pid;
    pipe(pfds);
    pid = fork();
    if(pid == -1){
        perror("Fork error: ");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        close(1); /** Fecha o stdout padrão **/
        dup(pfds[1]); /** redireciona stdout para pdfs[1]**/
        close(pfds[0]); /** fecha pfds[0] **/
        execlp("ls", "ls", NULL);
    }
    else{
        close(0);
        dup(pfds[0]); /** redireciona stdin para pdfs[1]**/
        close(pfds[1]); /** fecha pfds[1] **/
        execlp("wc", "wc", "-l",  NULL);
    }
    return 0;
}
