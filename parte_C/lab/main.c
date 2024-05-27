/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */


int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc != 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s \n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                			/* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *pipedFP;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    pipe_t *pipedNP;          			/* array dinamico di pipe descriptors per comunicazioni nipoti-padre  */
    int i, j;               			/* indici per i cicli */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;              				/* file descriptor */
    
    /* ------------------------------------ */


    /* Salvo il numero dei file in una variabile */
    N = argc - 1; 

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(pipedFP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione nipote-padre */
    if(!(pipedNP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione nipote-padre!\n");
        exit(3);
    }

    /* Inizializzo l'array delle pipe */
    for(i = 0; i < N; i++) {
        if(pipe(pipedFP[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe per il figlio %d-esimo!\n", i);
            exit(4);
        }
        if(pipe(pipedNP[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe per il nipote %d-esimo!\n", i);
            exit(5);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(6);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                close(pipedFP[j][0]);
                if(i != j)
                    close(pipedFP[j][1]);
            }

            /* Creo il processo nipote */
            if((pid = fork()) < 0) {
                printf("Errore: Impossibile creare il processo nipote!\n");
                exit(-1);
            }

            /* Codice del processo nipote */
            if(pid == 0) {
                /* chiusura della pipe rimasta aperta di comunicazione fra figlio-padre che il nipote non usa */
                close(pipedFP[i][1]);

                /* Chiudo tutte le pipe di non interesse */
                for(j = 0; j < N; j++) {
                    close(pipedNP[j][0]);
                    if(i != j)
                        close(pipedNP[j][1]);
                }

                /*###############grandson operation###################*/

                exit(0); /* return del nipote al figlio */
            }

            /* le pipe usate dal nipote vanno chiuse TUTTE */
            for(j = 0; j < N; j++) {
                close(pipedNP[j][0]);
                close(pipedNP[j][1]);
            }

            /*###############son operation###################*/

            /* il figlio aspetta il nipote */
            if ((pidWaitedSon = wait(&status)) < 0) {
                printf("Errore in wait per il nipote %d-esimo con pid=%d!\n", i, getpid());
            }
            if ((status & 0xFF) != 0)
                printf("Nipote con pid %d terminato in modo anomalo\n", pidWaitedSon);
            else {
                ritorno = (int)((status >> 8) & 0xFF);
                printf("--------------------------\n");
                printf("DEBUG: Il Nipote %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", i, pidWaitedSon, ritorno);
                printf("--------------------------\n");
            }

            exit(0); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(i = 0; i < N; i++) {
        close(pipedFP[i][1]);
        close(pipedNP[i][1]);
    }
    
    /*###############father operation###################*/



    /* Il padre aspetta i figli salvando lo status */
    for (int i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(7);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", i, pidWaitedSon);
        else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", i, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}