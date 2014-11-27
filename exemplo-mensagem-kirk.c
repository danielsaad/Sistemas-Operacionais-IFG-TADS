/**
    Autor: Beej http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html
    Adaptado por: Daniel Saad Nogueira Nunes
    Descrição: Descrição: Demonstração da utilização de troca de mensagens
    entre os processos kirk e spock.
    Kirk: Coloca mensagens na fila.
**/


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
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

    /** Geração de chave **/
    if ((key = ftok("exemplo-mensagem-kirk.c", 'B')) == -1) {
        perror("ftok: ");
        exit(1);
    }

    /** Obtenção da fila de mensagens **/
    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget: ");
        exit(1);
    }

    printf("Entre linhas de texto e pressione ^D para sair:\n");

    buf.mtype = 1; /** tipo da mensagem **/

    /** Lê da entrada padrão até o Ctrl + D ser acionado **/
    while(fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL) {
        int len = strlen(buf.mtext);

        /** Retira caractere de pular linha, caso haja **/
        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd:");
    }

    /** Remove a fila alocada **/
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl: ");
        exit(1);
    }

    return (0);
}
