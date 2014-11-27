/**
    Autor: Beej http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html
    Adaptado por: Daniel Saad Nogueira Nunes
    Descrição: Descrição: Demonstração da utilização de memória compartilhada
    por dois processos.
    Experimente rodar duas ou mais instâncias do processo,
    leitores e escritores. Note que pode haver condição de corrida.
**/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  /* make it a 1K shared memory segment */

int main(int argc, char *argv[])
{
    key_t key;
    int shmid;
    char *data;
    if (argc > 2) {
        fprintf(stderr, "uso (escrita): ./shmdemo <dados a serem escritos>\n");
        fprintf(stderr, "uso(leitura): ./shmdemo \n");
        exit(1);
    }

    /** gere a chave: (tem que ser a mesma entre os dois processos) **/
    if ((key = ftok("exemplo-memoria-1.c", 'R')) == -1) {
        perror("ftok: ");
        exit(1);
    }

    /** Conectar-se e possivelmente criar o segmento **/
    if ((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1) {
        perror("shmget: ");
        exit(1);
    }

    /** se acoplar ao segmente e obter um ponteiro para ele: **/
    data = shmat(shmid, (void *)0, 0);
    if (data == (char *)(-1)) {
        perror("shmat: ");
        exit(1);
    }

    /** ler ou modificar o segmento, de acordo com a linha de comando: */
    if (argc == 2) {
        printf("escrevendo no segmento: \"%s\"\n", argv[1]);
        strncpy(data, argv[1], SHM_SIZE);
    }
    else{
        while(1){
            printf("segmento contém: \"%s\"\n", data);
        }
    }
    /** Desacoplar segmento do processo: **/
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(1);
    }
    return (0);
}

/**
 * Para remover um segmento de memória.
 * shmctl(shmid, IPC_RMID, NULL);
 * OBS: Só é removido depois que todos os processos que o usam
 * dão dettach.
 **/
