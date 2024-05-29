/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <sys/stat.h> /* SYStem STAT: stat */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */


int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 ... char \n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                /* process identifier per le fork() */
    int N;                  /* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *pipedFP;        /* array dinamico di pipe descriptors per comunicazioni figli-padre */
    pipe_t *pipedPF;        /* array dinamico di pipe descriptors per comunicazioni padre-figli */
    int i, j;               /* indici per i cicli */
    int pidWaitedSon, status;/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;                 /* file descriptor */
    char Cx;                /* carattere passato come parametro */
    char ch; 			    /* variabile che viene usata dai figli per leggere dal file */
    char cx; 			    /* variabile che viene usata dal padre per avere dall'utente l'informazione del carattere da sostituire e  dai figli per recuperare il carattere comunicato dal padre */
    long int pos; 			/* valore per comunicare la posizione al padre e quindi all'utente */
    int ritorno = 0; 		/* variabile che viene ritornata da ogni figlio al padre e che contiene il numero di caratteri scritti sul file (supposta minore di 255): valore iniziale 0 */
    int nr;     			/* variabile che serve al padre per sapere se non ha letto nulla */
  	int finito;     		/* variabile che serve al padre per sapere se non ci sono piu' posizioni da leggere */
    char scarto; 			/* variabile che viene usata dal padre per eliminare lo '\n' letto dallo standard input */
    
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; 

    /* controllo che il lultimo parametro sia un singolo carattere */
    if (argv[argc - 1][1] != '\0') {
        printf("Error: %s non singolo carattere\n", argv[argc - 1]);
        exit(2);
    }

    /* Salvo il carattere passato come parametro */
    Cx = argv[argc-1][0];

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(pipedFP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(3);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione padre-figlio */
    if(!(pipedPF = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione padre-figlio!\n");
        exit(4);
    }

    /* Creazione delle N pipe figli-padre e delle N pipe padre-figli */
    for(i = 0; i < N; i++) {
        if(pipe(pipedFP[i]) < 0) {
            printf("Errore: Impossibile creare la pipe figlio-padre %d-esima!\n", i);
            exit(5);
        }
        if(pipe(pipedPF[i]) < 0) {
            printf("Errore: Impossibile creare la pipe padre-figlio %d-esima!\n", i);
            exit(6);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(7);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiusura delle pipe non usate nella comunicazione con il padre */
            for (j = 0; j < N; j++) {
                close(pipedFP[j][0]);
                close(pipedPF[j][1]);
                if (i != j) {
                    close(pipedFP[j][1]);
                    close(pipedPF[j][0]);
                }
            }

            /* Apro il file in sola lettura */
            if((fd = open(argv[i + 1], O_RDWR)) < 0) {
                printf("Errore: Impossibile aprire il file %s in lettura e scrittura!\n", argv[i + 1]);
                exit(-1);
            }

            /* Leggo il file carattere per carattere */
            while (read(fd, &ch, 1)) {
                /* controlliamo se abbiamo trovato un occorenza */
                if (ch == Cx) {
                    /* se si, dobbiamo mandare al padre la posizione del carattere trovato */
                    pos = lseek(fd, 0L, SEEK_CUR);
                    write(pipedFP[i][1], &pos, sizeof(pos));
                    /* il figlio Pi deve leggere il valore inviato dal padre */
                    read(pipedPF[i][0], &cx, sizeof(cx));

                    /* adesso il figlio deve tornare indietro con il file pointer per sovrascrivere, nel caso, il carattere trovato con quello comunicato dal padre */
                    if (cx != '\n') {
                        lseek(fd, -1L, SEEK_CUR);
                        write(fd, &cx, 1);
                        ritorno++;
                    }
                    
                }
            }

            exit(ritorno); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Il padre chiude i lati delle pipe che non usa */
    for (i = 0; i < N; i++) {
        close(pipedFP[i][1]);
        close(pipedPF[i][0]);
    }

    /* Il padre recupera le informazioni dai figli: prima in ordine di posizioni e quindi in ordine di indice */
 	finito = 0; /* all'inizio supponiamo che non sia finito nessun figlio */
    while (!finito) {
        finito = 1; /* mettiamo finito a 1 perche' potrebbero essere finiti tutti i figli */
        for (i = 0; i < N; i++) {
            /* il padre legge dai figli */
            nr = read(pipedFP[i][0], &pos, sizeof(pos));
            if (nr == sizeof(pos)) {
                finito = 0; /* c'e' almeno un figlio che non ha finito */
                printf("Il figlio di indice %d ha letto dal file %s nella posizione %ld il carattere %c. Se vuoi sostituirlo, fornisci il carattere altrimenti una linea vuota?\n", i,  argv[i+1], pos, Cx);
        		read(0, &cx, 1);

                if (cx != '\n') {
                    read(0, &scarto, 1); /* se e' stato letto un carattere, bisogna fare una lettura a vuoto per eliminare il carattere corrispondente all'invio */
                }
                write(pipedPF[i][1], &cx, 1);  /* inviamo comunque al figlio */
            }
        }
        
    }
    
    /* Il padre aspetta i figli salvando lo status */
    for (int i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(8);
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