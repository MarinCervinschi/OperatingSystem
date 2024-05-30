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
    if (argc < 5) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file (num > 0) char char ... \n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                /* process identifier per le fork() */
    int Q;                  /* numero di processi da creare (variabile del testo) */
    pipe_t *piped;          /* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int q, j;               /* indici per i cicli (q variabli del testo)*/
    int pidWaitedSon, status, ritorno;/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;                 /* file descriptor */
    int nr,nw;              /* variabili per salvare valori di ritorno di read/write da/su pipe */
    char ok;                /* carattere letto dai figli dalla pipe precedente e scritta su quella successiva */
    char ch;                /* carattere lette dai figli dall'unico file */
    int nrChar;             /* contatore carattere cercato per ogni linea */
    int L;                  /* per valore numero linee del file (variabile del testo) */
    
    /* ------------------------------------ */

    /* ricaviamo il numero di linee del file e controlliamo che sia strettamente maggiore di 0 */
	L = atoi(argv[2]);
    if (L <= 0) {
        printf("Errore: il numero di linee deve essere strettamente maggiore di 0\n");
        exit(2);
    }

    /* controlliamo che i parametri a partire dal terzo siano singoli parametri */
    for (j = 3; j < argc; j++) {
        if (argv[j][1] != '\0') {
            printf("Errore: i parametri a partire dal terzo devono essere singoli caratteri\n");
            exit(3);
        }
    }
    /* calcoliamo il numero di caratteri e quindi di processi da creare */
    Q = argc - 3; 

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc((Q + 1) * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(4);
    }

    /* Inizializzo l'array delle pipe */
    for(q = 0; q < Q + 1; q++) {
        if(pipe(piped[q]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", q);
            exit(5);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), Q);
    printf("--------------------------\n");

    /* Creo Q processi figli */
    for(q = 0; q < Q; q++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", q);
            exit(6);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < Q + 1; j++) {
                if(q != j)
                    close(piped[j][0]);
                if(j != (q + 1))
                    close(piped[j][1]);
            }

            /* apertura file */
            if ((fd = open(argv[1], O_RDONLY)) < 0) {
                printf("Impossibile aprire il file %s\n", argv[1]);
                exit(-1);
            }

            /* inizializziamo il contatore del carattere cercato per ogni singola linea */
            nrChar = 0;
            /* con un ciclo leggiamo tutte le linee, come richiede la specifica */
            while (read(fd, &ch, 1) != 0) {
                if (ch == '\n') { /* siamo a fine linea */
                    /* dobbiamo aspettare l'ok dal figlio precedente per scrivere */
                    nr = read(piped[q][0], &ok, sizeof(char));
                    /* per sicurezza controlliamo il risultato della lettura da pipe */
                    if (nr != sizeof(char)) {
                        printf("Figlio %d ha letto un numero di byte sbagliati %d\n", q, nr);
                        exit(-1);
                    }
                    /* a questo punto si deve riportare su standard output l'indice e il pid del processo, il numero di caratteri cercato presenti e la linea letta */
                    printf("Figlio con indice %d e pid %d ha letto %d caratteri %c nella linea corrente\n", q, getpid(), nrChar, argv[q + 3][0]);
                    /* ora si deve mandare l'OK in avanti: nota che il valore della variabile ok non ha importanza */
                    nw = write(piped[q + 1][1], &ok, sizeof(char));
                    /* anche in questo caso controlliamo il risultato della scrittura */
                    if (nw != sizeof(char)) {
                        printf("Figlio %d ha scritto un numero di byte sbagliati %d\n", q, nw);
                        exit(-1);
                    }
                    /* si deve azzerare il conteggio delle occorrenze, dopo averlo salvato per poterlo tornare correttamente, nel caso la linea corrente sia l'ultima! */
                    ritorno = nrChar;
                    nrChar = 0;
                } else {
                    /* se non siamo a fine linea dobbiamo fare il controllo sul carattere corrente */
                    if (ch == argv[q + 3][0]) { /* se abbiamo letto il carattere da cercare incrementiamo il contatore */
                        nrChar++;
                    }
                }
            }
            /* ogni figlio deve tornare il numero di caratteri numerici dell'ultima linea */
            exit(ritorno); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* chiusura di tutte le pipe che non usa, a parte la prima e l'ultima */
    for (int q = 0; q < Q + 1; q++) {
        if (q != Q) close(piped[q][0]);
        if (q != 0) close(piped[q][1]);
    }

    /* Poiche' in questo caso il padre e' nel ring, non ci sono problemi di dover lasciare aperti lati di pipe che il padre non usa! */

    for (j = 0; j < L; j++) { /* il padre deve leggere una riga per volta da ciascun file */
        /* il padre deve riportare il numero di linea correntemente analizzata dai figli, insieme con il nome del file */
        printf("Linea %d del file %s\n", j + 1, argv[1]); /* il numero di linea deve partire da 1! */
        /* il padre deve inviare un 'segnale' di sincronizzazione al processo di indice 0 */
        nw = write(piped[0][1], &ok, sizeof(char));
        /* anche in questo caso controlliamo il risultato della scrittura */
        if (nw != sizeof(char)) {
            printf("Padre ha scritto un numero di byte sbagliati %d\n", nw);
            exit(7);
        }
        /* il padre quindi deve aspettare che l'ultimo figlio gli invii il 'segnale' di sincronizzazione per fare ripartire il ring */
        nr = read(piped[Q][0], &ok, sizeof(char));
        /* per sicurezza controlliamo il risultato della lettura da pipe */
        if (nr != sizeof(char)) {
            printf("Padre ha letto un numero di byte sbagliati %d\n", nr);
            exit(8);
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for (int q = 0; q < Q; q++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", q);
            exit(9);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", q, pidWaitedSon);
        else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", q, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}