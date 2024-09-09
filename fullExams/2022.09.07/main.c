/* File main.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */


int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
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
    int fcreato;                        /* file descriptor per il file da creare */
    /* ATTENZIONE 'fcreato' variabile del testo */
    char car;                           /* variabile per il carattere letto correntemente dai figli dal proprio file */
    /* ATTENZIONE 'car' variabile del testo */
    char* cur;                          /* variabile per l’array da passare fra i vari figli fino al padre */
    /* ATTENZIONE 'cur' variabile del testo */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 1; 

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Inizializzo l'array delle pipe */
    for(n = 0; n < N; n++) {
        if(pipe(piped[n]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", n);
            exit(3);
        }
    }

    /* Alloco memoria per l'array di char da passare in avanti */
    if(!(cur = (char*) malloc(N * sizeof(char)))) {
        printf("Errore: Impossibile allocare memoria per l'array di char da passare in avanti!\n");
        exit(4);
    }

    /* Creazione file */
    if ((fcreato = creat("CERVINSCHI", 0644)) < 0) {
        printf("Errore in creazione file 'CERVINSCHI'\n");
        exit(5);
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(6);
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
            /* Apertura file in lettura */
            if ((fd = open(argv[n + 1], O_RDONLY)) < 0) {
                printf("Errore in apertura file '%s' in lettura\n", argv[n + 1]);
                exit(-1);
            }

            int pos = 1;
            /* leggi tutto il file */
            while (read(fd, &car, 1)) {
                if (pos % 2 == 1) {
                    if (n != 0) {
                        /* leggiamo dalla pipe il valore corrente */
                        nr = read(piped[n-1][0], cur, N * sizeof(char));
                        if (nr != N * sizeof(char)) {
                            printf("Errore in lettura dalla pipe %d-esima\n", n-1);
                            exit(-1);
                        }
                    }
                    cur[n] = car;

                    /* scriviamo sulla pipe il valore aggiornato */
                    nw = write(piped[n][1], cur, N * sizeof(char));
                    if (nw != N * sizeof(char)) {
                        printf("Errore in scrittura sulla pipe %d-esima\n", n);
                        exit(-1);
                    }
                }
                pos++;
            }

            exit(car); /* return del figlio al padre */
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
    /* il padre deve leggere un solo array, chiaramente controllando l'esito della lettura! */
    while (read(piped[N-1][0], cur, N * sizeof(char))) {
        write(fcreato, cur, N * sizeof(char));
    }


    /* Il padre aspetta i figli salvando lo status */
    for (n = 0; n < N; n++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", n);
            exit(5);
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
