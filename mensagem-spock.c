/**
    Autor: Beej http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html
    Adaptado por: Daniel Saad Nogueira Nunes
    Descrição: Descrição: Demonstração da utilização de troca de mensagens
    entre os processos kirk e spock.
    Spock: Obtém mensagens da fila.
**/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    if ((key = ftok("mensagem-kirk.c", 'B')) == -1) {  /* same key as kirk.c */
        perror("ftok");
        exit(1);
    }

    /** Não colocamos IPC_CREAT aqui, pois deixamos Kirk lidar com isso,
     * se a fila não tiver sido criada, obteremos um erro
     **/
    if ((msqid = msgget(key, 0644)) == -1) { /** Conecta até a fila **/
        perror("msgget");
        exit(1);
    }


    printf("Spock: pronto para receber mensagens, capitão.\n");

    /**  ssize_t	msgrcv(int  msqid,  void *msgp, size_t msgsz, long msgtyp, int
       msgflg);
       Como o campo está 0, não importao valor de msgtype setado em kirk.
       Quando é 0, a primeira mensagem é lida.
    **/
    for(;;) { /** Spock nunca para de ouvir**/
        if (msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }
        printf("spock: \"%s\"\n", buf.mtext);
    }
    return 0;
}
