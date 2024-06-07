/* File main.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <string.h> /* STRING: memset */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */


/* VARIABILI GLOBALI */
int *finito;  /* array dinamico per indicare i figli che sono terminati */
/* la semantica di questo array e' che ogni elemento vale 0 se il corrispondente processo NON e' finito, altrimenti vale 1 */
int N;        /* numero di processi figli: deve essere una variabile globale perche' deve essere usata dalla funzione finitof */
/* ATTENZIONE 'N' nome indicato nel testo */
int finitof() {
    /* questa funzione verifica i valori memorizzati nell'array finito: 
    appena trova un elemento uguale a 0 vuole dire che non tutti i processi 
    figli sono finiti e quindi torna 0; tornera' 1 se e solo se tutti gli elementi 
    dell'array sono a 1 e quindi tutti i processi sono finiti */

    for (int i = 0; i < N; i++) {
        if (!finito[i]) {
            /* appena ne trova uno che non ha finito */
            return 0; /* ritorna falso */
        }
    }
    return 1;
}

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 4) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 file3 -opt[.. fileN]\n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                			/* process identifier per le fork() */
    /* ATTENZIONE 'N' variabile del testo */
    pipe_t *piped;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int n, j;               			/* indici per i cicli */
    /* ATTENZIONE 'n' variabile del testo */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;              				/* file descriptor per i file aperti in lettura*/
    int fdw;              				/* file descriptor per il file aperto in scrittura */
    /* ATTENZIONE 'fdw' variabile del testo */
    char chs[2];          				/* buffer per la comunicazione padre-figlio */
    /* ATTENZIONE 'chs' variabile del testo */
    int caratteriLetti;		    /* variabile per contare il numero di caratteri letti */
    int nr, nw;            				/* variabili per salvare il numero di caratteri letti e scritti */
    
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; /* argc -2 Sono i N processi figli da creare argc -1 e' il file su cui dobiamo scrivere */ 

    /* allocazione memoria dinamica per finito */
    finito = (int *) malloc(sizeof(int) * N);
    if(finito == NULL) {
        printf("Errore nella allocazione della memoria per array finito\n");
        exit(2);
    }
    /* ... e inizializzazione a 0: all'inizio nessun figlio e' finito */
    memset(finito, 0, sizeof(int) * N);

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(3);
    }

    /* Inizializzo l'array delle pipe */
    for(n = 0; n < N; n++) {
        if(pipe(piped[n]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", n);
            exit(4);
        }
    }

    /* Apro il file N+1 in scrittura */
    if ((fdw = open(argv[N + 1], O_WRONLY)) < 0) {
        printf("Errore in apertura file '%s' in scrittura\n", argv[N + 1]);
        exit(5);
    }
    lseek(fdw, 0L, SEEK_END); /* Sposto il puntatore alla fine del file */

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
            printf("************************\n");
            printf("DEBUG: Sono il processo figlio di indice [%d] associato al file '%s' con pid=[%d]\n", n, argv[n + 1], getpid());
            printf("************************\n");

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                close(piped[j][0]);
                if(n != j) {
                    close(piped[j][1]);
                }
            }

            /*###############son operation###################*/
            /* Apertura file in lettura */
            if ((fd = open(argv[n + 1], O_RDONLY)) < 0) {
                printf("Errore in apertura file '%s' in lettura\n", argv[n + 1]);
                exit(-1);
            }
            caratteriLetti = 0;
            /* Leggo il file due caratteri alla volta */
            while((nr = read(fd, chs, 2)) != 0) {
                /* Scrivo i due caratteri letti sulla pipe */
                nw = write(piped[n][1], chs, nr);
                if(nw != nr) { /* Controllo se il numero di byte scritti è diverso da quello letto */
                    printf("Figlio %d ha scritto un numero di byte sbagliati %d su pipe %d\n", n, nw, n);
                    exit(-1);
                }
                caratteriLetti += nr; /* Aggiorno il numero di caratteri letti */
            }

            exit(caratteriLetti); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(n = 0; n < N; n++) {
        close(piped[n][1]);
    }
    
    /*###############father operation###################*/

    while (!finitof()) {
        for (n = 0; n < N; n++) {
            nr = read(piped[n][0], chs, 2);
            finito[n] = (nr == 0);

            /* Verifico se il figlio ha finito */
            if (!finito[n]) {
                /* Scrivo i due caratteri letti sul file */
                write(fdw, chs, nr);
            }
        }
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