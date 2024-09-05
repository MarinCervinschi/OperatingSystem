/* File main.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <ctype.h> /* Includere la libreria ctype.h per isupper */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

/* definizione della struttura di dati da passare */
typedef struct{
    int c1; /* deve contenere il pid del processo*/
    long int c2; /* deve contenere il numero di occorrenze del carattere C */
} data;

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
    int i, j;               			/* indici per i cicli */
    /* ATTENZIONE 'i' variabile del testo */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int nr,nw;							/* variabili per salvare valori di ritorno di read e write da/su pipe */
    int fd;              				/* file descriptor */
    char ch;                            /* variabile per il carattere letto dai file dai figli */
    /* ATTENZIONE 'ch' variabile del testo */
    data* cur;                          /* l’array dinamico creato da ogni figlio (della dimensione minima necessaria) e dal padre. */
    /* ATTENZIONE 'cur' variabile del testo */
    char C;                             /* variable per salvare l'ultimo parametro passato */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; /* -2 perche' l'ultimo parametro non e' un file */

    /* controllo che il l'ultimo parametro sia un singolo carattere */
    if (argv[N + 1][1] != '\0' || isupper(argv[N + 1][0])) {
        printf("Error: %s non singolo carattere minuscolo\n", argv[N + 1]);
        exit(2);
    }
    C = argv[N + 1][0];

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Inizializzo l'array delle pipe */
    for(i = 0; i < N; i++) {
        if(pipe(piped[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", i);
            exit(3);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(4);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                if (j != i)
                    close(piped[j][1]);
                if ((i == 0) || (j != i-1))
                    close(piped[j][0]);
            }

            /*###############son operation###################*/

            /* Apertura file in lettura */
            if ((fd = open(argv[i + 1], O_RDONLY)) < 0) {
                printf("Errore in apertura file '%s' in lettura\n", argv[i + 1]);
                exit(-1);
            }

            /* allocazione di memoria per l'array di strutture per questo figlio */
            if (!(cur=(data*) malloc((i + 1) * sizeof(data)))) {
                printf("Errore: Impossibile allocare memoria per l'array di strutture!\n");
                exit(-1);
            }
            
            long int occ = 0;
            /* leggi tutto il file */
            while (read(fd, &ch, 1)) {
                if (ch == C) {
                    occ++;
                }
            }

            /* lettura da pipe dell'array di strutture per tutti i figli a parte il primo */
            if (i != 0) {

                /* leggiamo dalla pipe il valore corrente */
                nr = read(piped[i-1][0], cur, i * sizeof(data));

                if (nr != i * sizeof(data)) {
                    printf("Figlio %d ha letto un numero di strutture sbagliate %d\n", i, nr);
                    exit(-1);
                }
            }
            /* inizializziamo l'ultima struttura che e' quella specifica del figlio corrente (nel caso del primo figlio sara' l'unica struttura */
            cur[i].c1 = getpid();
            cur[i].c2 = occ;

            /* tutti i figli mandano in avanti, l'ultimo figlio manda al padre un array di strutture (per tutti i figli a parte il primo sono i strutture ricevute dal processo precedente e la i+1-esima che e' la propria) */
            nw = write(piped[i][1], cur, (i + 1) * sizeof(data));
            if (nw != (i + 1) * sizeof(data)) {
                printf("Figlio %d ha scritto un numero di strutture sbagliate %d\n", i, nw);
                exit(-1);
            }

            exit(i); /* return del figlio al padre */
        }
    }

    /*###############father operation###################*/

    /* Chiudo tutte le pipe di non interesse */
    for(i = 0; i < N; i++) {
        close(piped[i][1]);
        if (i != N-1)
            close(piped[i][0]);
    }

    /* allocazione di memoria per l'array di strutture da parte del padre */
    if (!(cur=(data*) malloc((N * sizeof(data))))){
        printf("Errore: Impossibile allocare memoria per l'array di strutture da parte del padre!\n");
        exit(5);
    }
    
    /* il padre deve leggere un solo array, chiaramente controllando l'esito della lettura! */
    nr = read(piped[N-1][0], cur, N * sizeof(data));
    if (nr != N * sizeof(data)) {
        printf("Il padre ha letto un numero di array sbagliato [%d]\n", nr);
        exit(5);
    } else {
        nr=nr/sizeof(data);
        printf("Padre ha letto un numero di strutture [%d]\n", nr);
        for(i = 0; i < N; i++) {
            long int occ = cur[i].c2;
            int pidFiglio = cur[i].c1;
            printf("Il figlio %d con pid=[%d] associato al file '%s' ha letto [%ld] occorenze del carattere %c\n", 
                        i, pidFiglio, argv[i + 1], occ, C);
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for (i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(5);
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
