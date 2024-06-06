/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */
typedef char L[250]; /* Definizione di un tipo L come array di 250 caratteri */

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 ... fileN \n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                /* process identifier per le fork() */
    int N;                  /* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *piped;          /* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int n, i, j, k;               /* indici per i cicli */
    int pidWaitedSon, status, ritorno;/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;              /* file descriptor */
    int nr,nw;              /* variabili per salvare valori di ritorno di read/write da/su pipe */
    int fdout;  /* file descriptor per la creazione del file */
    L linea;    /* per salvare la linea letta */
    L* tutteLinee; /* per salvare tutte le linee lette */
    
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

    /* allocazione dell'array delle linee */
    if ((tutteLinee = (L *) malloc(N * sizeof(L))) == NULL) {
        printf("Errore nell'allocazione dell'array delle linee\n");
        exit(4);
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* creazione file in cervinschi */
    /* usato la open in versione estesa per azzerare il file nel caso esista gia' */
    if ((fdout=creat("Cervinschi", 0644)) < 0) {
        printf("Errore nella creazione del file %s\n", "cervinschi");
        exit(5);
    }

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(6);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            printf("--------------------------\n");
            printf("DEBUG: Sono il figlio con pid=%d e indice %d, associato al file %s\n", getpid(), n, argv[n + 1]);
            printf("--------------------------\n");
            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                if (j != n) {
                    close(piped[j][0]);
                }
                if (j != (n + 1) % N) {
                    close(piped[j][1]);
                }
            }

            /* apertura file */
            if ((fd = open(argv[n + 1], O_RDONLY)) < 0) {
                printf("Impossibile aprire il file %s\n", argv[n + 1]);
                exit(-1);
            }

            /* inizializziamo il contatore del carattere cercato per ogni singola linea */
            j = 0;
            /* con un ciclo leggiamo tutte le linee, come richiede la specifica */
            while (read(fd, &(linea[j]), 1) != 0) {
                if (linea[j] == '\n') { /* siamo a fine linea */

                    nr = read(piped[n][0], tutteLinee, N*sizeof(L));
                    /* per sicurezza controlliamo il risultato della lettura da pipe */
                    if (nr != N*sizeof(L)) {
                        printf("Figlio %d ha letto un numero di byte sbagliati %d\n", n, nr);
                        exit(-1);
                    }

                    /* insetiamo la linea letta al posto giusto */
                    for (k = 0; k <= j; k++) {
                        tutteLinee[n][k] = linea[k];
                    }

                    nw = write(piped[(n + 1)%N][1], tutteLinee, N*sizeof(L));
                    /* anche in questo caso controlliamo il risultato della scrittura */
                    if (nw != N*sizeof(L)) {
                        printf("Figlio %d ha scritto un numero di byte sbagliati %d\n", n, nw);
                        exit(-1);
                    }

                    if (n == N - 1) {
                        /* se siamo all'ultimo figlio, scriviamo la linea su file */
                        for (i = 0; i < N; i++) {
                            for (k = 0; k < 250; k++) {
                                write(fdout, &(tutteLinee[i][k]), 1);
                                if (tutteLinee[i][k] == '\n') {
                                    break;
                                }
                            }
                        }
                    } 
                    ritorno = j+1;
                    j = 0;
                } else {
                    j++;
                }
            }
            /* ogni figlio deve tornare il numero di caratteri numerici dell'ultima linea */
            exit(ritorno); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* chiusura di tutte le pipe che non usa, a parte la prima e l'ultima */
    for (n = 1; n < N; n++) {
        close(piped[n][0]);
        close(piped[n][1]);
    }
    /* Poiche' in questo caso il padre e' nel ring, non ci sono problemi di dover lasciare aperti lati di pipe che il padre non usa! */

    /* mandiamo al primo figlio l'array delle linee */
    nw = write(piped[0][1], tutteLinee, N*sizeof(L));
    if (nw != N*sizeof(L)) {
        printf("Padre ha scritto un numero di byte sbagliati %d\n", nw);
        exit(7);
    }

    /* chiudiamo il lato di scrittura della pipe */
    close(piped[0][1]);

    
    /* Il padre aspetta i figli salvando lo status */
    for (n = 0; n < N; n++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", n);
            exit(8);
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