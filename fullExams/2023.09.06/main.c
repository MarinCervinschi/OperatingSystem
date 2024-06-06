/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

/* Definizione di una struttura per memorizzare le informazioni */
typedef struct{
    long int minimoLinee; /* variabile c1 del testo */
    int indice; /* variabile c2 del testo */
} Informazioni;

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 .. fileN\n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int* pid;                	        /* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    /* N variabile del testo*/
    pipe_t *piped_FP;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    pipe_t *piped_PF;          			/* array dinamico di pipe descriptors per comunicazioni padre-figli  */
    int n, j;               			/* indici per i cicli */
    /* n variabile del testo*/
    char linea[250];        			/* array di caratteri per la lettura di una linea */
    /* linea variabile del testo*/
    /* supponiamo che 250 sia la lunghezza massima di una linea compreso il terminatore */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int nr,nw;							/* variabili per salvare valori di ritorno di read e write da/su pipe */
    int fd;              				/* file descriptor */
    long int cur_tot;                   /* per il calcolo del numero di linee effettuato dai figli */
    char ch;                            /* per la lettura di un carattere */
    /* cur_tot variabile del testo*/
    long int min;                       /* per il valore minimo ricevuto dai figli da parte del padre */
    /* min variabile del testo*/
    Informazioni info;                 /* strutture per memorizzare le informazioni */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 1; 

    /* Alloco memoria per l'array dei pid */
    if(!(pid = (int*) malloc(N * sizeof(int)))) {
        printf("Errore: Impossibile allocare memoria per l'array dei pid!\n");
        exit(2);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(piped_FP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(3);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione padre-figlio */
    if(!(piped_PF = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione padre-figlio!\n");
        exit(4);
    }

    /* Inizializzo l'array delle pipe */
    for(n = 0; n < N; n++) {
        if(pipe(piped_FP[n]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", n);
            exit(5);
        }
        if(pipe(piped_PF[n]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe, si è bloccato alla pipe di indice: %d!\n", n);
            exit(6);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid[n] = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(7);
        }

        /* Codice del processo figlio */
        if(pid[n] == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                close(piped_PF[j][1]);
                if (j != n)
                    close(piped_FP[j][1]);
                    close(piped_PF[j][1]);

                if ((n == 0) || (j != n-1))
                    close(piped_FP[j][0]);
            }

            /* Apertura del file */
            if((fd = open(argv[n+1], O_RDONLY)) < 0) {
                printf("Errore: Impossibile aprire il file %s!\n", argv[n+1]);
                exit(-1);
            }


            /* Inizializzo la variabile cur_tot */
            cur_tot = 0;

            /* Leggi il numero di linee del file */
            while (read(fd, &ch, 1)) {
                if (ch == '\n')
                    cur_tot++;
            }

            /* se sono il primo figlio inizializzo la struttura altrimenti aggiorno il minimo e l'indice */
            if (n == 0) {
                info.minimoLinee = cur_tot;
                info.indice = n;
            } else {
                /* aggiorno la struttura info */
                if (cur_tot < info.minimoLinee) {
                    info.minimoLinee = cur_tot;
                    info.indice = n;
                }
            }

            /* figio che deve leggere il risulato di un altro figlio */
            if (n != 0) {

                /* leggiamo dalla pipe il valore corrente */
                nr = read(piped_FP[n-1][0], &info, sizeof(info));
                if (nr != sizeof(info)) {
                    printf("Errore in lettura dalla pipe %d-esima del figlio-padre\n", n-1);
                    exit(-1);
                }
            }

            /* scriviamo sulla pipe il valore aggiornato */
            nw = write(piped_FP[n][1], &info, sizeof(info));
            if (nw != sizeof(info)) {
                printf("Errore in scrittura sulla pipe %d-esima\n", n);
                exit(-1);
            }

            /* leggiamo dalla pipe il valore minimo */
            nr = read(piped_PF[n][0], &min, sizeof(min));
            if (nr != sizeof(min)) {
                printf("Errore in lettura dalla pipe %d-esima del padre-figlio\n", n);
                exit(-1);
            }

            /* leggo la linea di indice minimo */
            lseek(fd, 0, SEEK_SET);
            cur_tot = 1;
            j = 0;
            while (read(fd, &ch, 1)) {
                if (ch == '\n')
                    cur_tot++;
                if (cur_tot > min)
                    break;
                if (cur_tot == min && ch != '\n')
                    linea[j++] = ch;
            }
            linea[j] = '\0';

            printf("##########################################\n");
            printf("Il figlio di indice [%d] e pid=[%d] ha letto la linea di indice %ld dal file '%s' pari a '%s'\n", n, getpid(), min, argv[n + 1], linea);
            printf("##########################################\n");

            /* ritorno l'indice del figlio */
            exit(n); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(n = 0; n < N; n++) {
        close(piped_FP[n][1]);
        close(piped_PF[n][0]);
    }
    
    /* il padre deve leggere un solo array, chiaramente controllando l'esito della lettura! */
    nr = read(piped_FP[N-1][0], &info, sizeof(info));
    if (nr != sizeof(info)) {
        printf("Errore in lettura dalla pipe %d-esima\n", N-1);
        exit(4);
    }

    printf("************************************\n");
    printf("Il figlio con indice [%d] e pid=[%d] ha ritornato il minimo numero di linee pari a [%ld] corrispondente al file '%s'\n", info.indice, pid[info.indice], info.minimoLinee, argv[info.indice+1]);
    printf("************************************\n");

    for (n = 0; n < N; n++) {
        nw = write(piped_PF[n][1], &info.minimoLinee, sizeof(info.minimoLinee));
        if (nw != sizeof(info.minimoLinee)) {
            printf("Errore in scrittura sulla pipe %d-esima\n", n);
            exit(-1);
        }
    }

    /* Il padre aspetta n figli salvando lo status */
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