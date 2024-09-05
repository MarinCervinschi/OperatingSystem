/* File main.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <string.h>

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

typedef char L[250];

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 4) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                	        /* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    /* ATTENZIONE 'N' variabile del testo */
    pipe_t *piped;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int n, j;               			/* indici per i cicli */
    /* ATTENZIONE 'n' variabile del testo */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int nr,nw;							/* variabili per salvare valori di ritorno di read e write da/su pipe */
    int fd;              				/* file descriptor per i file in lettura*/
    int fcreato;                        /* file descriptor per il file creato*/
    L linea;                            /* variabile per la linea letta correntemente dai figli dal proprio file */
    /* ATTENZIONE 'linea' variabile del testo */
    int nroLinee;                       /* variabile per la lunghezza in linee dei file */
    /* ATTENZIONE 'nroLinee' variabile del testo */
    L *tutteLinee;                        /* variabile per la linea letta correntemente dai figli dal proprio file */
    /* ATTENZIONE 'tutteLinee' variabile del testo */
    /* other variables */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; 

    /* controllo che l'ultimo parametro sia un numero strettamente positivo */
    nroLinee = atoi(argv[N + 1]);
    if (nroLinee <= 0) {
        printf("Error: %s non e' un numero strettamente positivo\n", argv[N + 1]);
        exit(2);
    }

    /* Creazione file fcreato con il proprio cognome */
    if ((fcreato = creat("CERVINSCHI", 0644)) < 0) {
        printf("Errore in creazione file fcreato\n");
        exit(3);
    }

    /* Alloco memoria per l'array di N linee*/
    if (!(tutteLinee = (L*) malloc(N * sizeof(L)))) {
        printf("Errore: Impossibile allocare memoria per l'array di N linee!\n");
        exit(4);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(5);
    }

    /* Inizializzo l'array delle pipe */
    for(n = 0; n < N; n++) {
        if(pipe(piped[n]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", n);
            exit(6);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(7);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                if (j != n)
                    close(piped[j][1]);
                if ((n == 0) || (j != n-1))
                    close(piped[j][0]);
            }

            /*###############son operation###################*/
            /* apertura file */
            if ((fd = open(argv[n + 1], O_RDONLY)) < 0) {
                printf("Impossibile aprire il file %s\n", argv[n + 1]);
                exit(-1);
            }

            /* inizializziamo l'indice dei caratteri letti per ogni singola linea */
            j = 0;
            /* con un ciclo leggiamo tutte le linee, come richiede la specifica */
            while (read(fd, &(linea[j]), 1) != 0) {
                if (linea[j] == '\n') /* siamo a fine linea */
                {
                    if (n != 0) {
                        /* se non siamo il primo figlio, dobbiamo aspettare
                         * l'array dal figlio precedente per mandare avanti */
                        nr = read(piped[n - 1][0], tutteLinee, N * sizeof(L));
                        /* per sicurezza controlliamo il risultato della lettura
                         * da pipe */
                        if (nr != N * sizeof(L)) {
                            printf(
                                "Figlio %d ha letto un numero di byte "
                                "sbagliati %d\n",
                                n, nr);
                            exit(-1);
                        }
                    }
                    /* a questo punto si deve inserire la linea letta nel posto
                     * giusto */
                    for (int k = 0; k <= j; k++) { /* ricordarsi che non si puo' fare una copia diretta di un array! */
                        tutteLinee[n][k] = linea[k];
                    }

                    /* ora si deve mandare l'array in avanti */
                    nw = write(piped[n][1], tutteLinee, N * sizeof(L));
                    /* anche in questo caso controlliamo il risultato della scrittura */
                    if (nw != N * sizeof(L)) {
                        printf(
                            "Figlio %d ha scritto un numero di byte sbagliati "
                            "%d\n",
                            n, nw);
                        exit(-1);
                    }
                    /* si deve azzerare l'indice della linea, dopo averlo
                     * salvato (incrementato) per poterlo tornare correttamente
                     */
                    ritorno = j + 1;
                    j = 0;
                } else {
                    j++; /* incrementiamo sempre l'indice della linea */
                }
            }
            /* ogni figlio deve tornare il numero di caratteri dell'ultima linea */
            exit(ritorno);
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(n = 0; n < N; n++) {
        close(piped[n][1]);
        if (n != N-1)
            close(piped[n][0]);
    }
    
    /*###############father operation###################*/

    for (j = 1; j <= nroLinee; j++) {
        nr = read(piped[n - 1][0], tutteLinee, N * sizeof(L));
        /* per sicurezza controlliamo il risultato della lettura da pipe */
        if (nr != N * sizeof(L)) {
            printf("Padre ha letto un numero di byte sbagliati %d\n", nr);
            exit(8);
        }

        /* il padre deve scrivere le linee sul file creato */
        for (n = 0; n < N; n++) {
            for (int k = 0; k < 250; k++) {
                /* fino a che non incontriamo il fine linea scriviamo sul file
                 * creato */
                write(fcreato, &(tutteLinee[n][k]), 1);
                if (tutteLinee[n][k] == '\n') {
                    /* quando troviamo il terminatore di linea, ... */
                    break; /* usciamo dal ciclo for piu' interno */
                }
            }
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for (n = 0; n < N; n++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", n);
            exit(9);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", n, pidWaitedSon);
        else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", n, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}