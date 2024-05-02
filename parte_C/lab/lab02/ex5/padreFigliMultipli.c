/* File padreFigliMultipli.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */


/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 2) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }
    /* controllo che il primo parametro sia un numero strettamente positivo */
    int num = atoi(argv[1]);
    if (num <= 0 || num > 255) {
        printf("Error: %s non e' un numero 0 < numero < 255\n", argv[1]);
        exit(2);
    }
}
int main(int argc, char **argv) {
    checkParams(argc, argv);

    int N = atoi(argv[1]);
    int pid;
    int pidPadre = getpid();

    printf("La pid del padre e' :%d\n", pidPadre);
    printf("Il padre deve generare %d figli\n", N);
    
    /* Per la creazione di N figli */
    for(int i = 1; i <= N; i++){
        if ((pid = fork()) < 0) {
            //Fork fallita
            printf("Errore in fork\n");
            exit(4);
        }
        
        if (pid == 0) { 
            /* CODICE DEL FIGLIO*/
    
            printf("Figlio, pid: %d, indice %d\n", getpid(), i);
            exit(i);
    
            /*FINE CODICE DEL FIGLIO*/
        }
        printf("Generato figlio con PID = %d\n", pid);
    }
    
    /* padre */
    int pidFiglio, status, ritorno;

    /* Il padre aspetta i figli salvando lo status */
    for(int i = 0; i < N; i++) {
        if ((pidFiglio = wait(&status)) < 0) {
            //La wait non ha avuto successo
            printf("Errore in wait\n");
            exit(5);
        }

        printf("Terminato figlio con PID = %d\n", pidFiglio);
        if (WIFEXITED(status)) {
            /* Ricavo l'exitcode del figlio con la funzione WEXITSTATUS */
            ritorno = WEXITSTATUS(status);
            printf("Il figlio e' ritornato con codice: %d\n", ritorno);
        } else {
            /* Lo status riporta una terminazione anomala */
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    }

    exit(0);
}