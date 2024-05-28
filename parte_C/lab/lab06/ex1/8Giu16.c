/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <time.h> /* time per srand */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */


int mia_random(int n) {
    int casuale;
    casuale = rand() % n;
    return casuale;
}


int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 6) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 file3 file4 ... (0 < num < 255) \n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                /* process identifier per le fork() */
    int N;                  /* numero di file passati sulla riga di comando (uguale al numero di file) */
    int H;                  /* numero di linee da leggere */
    pipe_t *pipedFP;        /* array dinamico di pipe descriptors per comunicazioni figli-padre */
    pipe_t *pipedPF;        /* array dinamico di pipe descriptors per comunicazioni padre-figli */
    int i, j;               /* indici per i cicli */
    int pidWaitedSon, status;/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;                 /* file descriptor */
    int fdout; 			    /* file descriptor per creazione file da parte del padre */
    char linea[255];        /* array di caratteri per memorizzare la linea, supponendo una lunghezza massima di ogni linea di 255 caratteri compreso il terminatore di linea */
    int valore;             /* variabile che viene usata dal padre per recuperare il valore comunicato da ogni figlio e che contiene la lunghezza della linea corrente */
    int giusto;             /* variabile che viene usata dal padre per salvare per ogni linea il valore inviato dal figlio selezionato in modo random */
    int r;                  /* variabile usata dal padre per calcolare i valori random e dal figlio per ricevere il numero dal padre */
    int ritorno = 0; 		/* variabile che viene ritornata da ogni figlio al padre e che contiene il numero di caratteri scritti sul file (supposta minore di 255): valore iniziale 0 */
   /* ------------------------------------ */

    /* Inizializzazione del generatore di numeri casuali */
    srand(time(NULL));


    /* Salvo il numero dei file in una variabile */
    N = argc - 2; 

    /* Salvo il numero di linee da leggere in una variabile */
    H = atoi(argv[argc-1]);
    if ((H <= 0) || (H >= 255)) {
        printf("Errore nel numero passato %d\n", H);
        exit(2);
    }

    /* creazione file in /tmp */
    /* usato la open in versione estesa per azzerare il file nel caso esista gia' */
    if ((fdout=open("/tmp/creato", O_CREAT|O_WRONLY|O_TRUNC, 0644)) < 0) {
        printf("Errore nella creazione del file %s\n", "/tmp/creato");
        exit(3);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(pipedFP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(4);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione padre-figlio */
    if(!(pipedPF = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione padre-figlio!\n");
        exit(5);
    }

    /* Creazione delle N pipe figli-padre e delle N pipe padre-figli */
    for(i = 0; i < N; i++) {
        if(pipe(pipedFP[i]) < 0) {
            printf("Errore: Impossibile creare la pipe figlio-padre %d-esima!\n", i);
            exit(6);
        }
        if(pipe(pipedPF[i]) < 0) {
            printf("Errore: Impossibile creare la pipe padre-figlio %d-esima!\n", i);
            exit(7);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(8);
        }

        /* Codice del processo figlio */
        if(pid == 0) {
            printf("--------------------------\n");
            printf("DEBUG: Sono il processo figlio di indice %d e pid %d e sono associato al file %s\n", i, getpid(), argv[i+1]);
            printf("--------------------------\n");

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
            if((fd = open(argv[i + 1], O_RDONLY)) < 0) {
                printf("Errore: Impossibile aprire il file %s in sola lettura!\n", argv[i + 1]);
                exit(-1);
            }

            /* adesso il figlio legge dal file una linea alla volta */
            j=0;
            while(read(fd, &(linea[j]), 1)){
                if(linea[j] == '\n'){
                    /* dobbiamo mandare al padre la lunghezza della linea corrente compreso il terminatore di linea (come int) e quindi incrementiamo j */
                    j++;
                    write(pipedFP[i][1], &j, sizeof(j));
                    /* il figlio Pi deve leggere il valore inviato dal padre */
                    read(pipedPF[i][0], &r, sizeof(r));

                    /* il figlio Pi deve controllare l'ammissibilita' del valore inviato dal padre rispetto alla lunghezza della linea corrente */
				   	if (r < j) {
                        /* dato che si riceve un indice che varia da 0 alla lung - 1 scelta dal padre 
                        e dato che j rappresenta la lunghezza della linea corrente, 
                        l'indice ricevuto per essere ammissibile deve essere strettamente minore di j */

				   		/* ogni figlio usa, per scrivere sul file, il valore di fdout ottenuto per copia 
                        dal padre e condivide l'I/O pointer con il padre e tutti i fratelli */
						write(fdout, &(linea[r]), 1);
						/* il figlio incrementa il valore di ritorno */
						ritorno++;
                    } else {
                        j = 0; /* azzeriamo l'indice per le prossime linee */
                    }
                } else {
                    j++;
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

    /* Il padre recupera le informazioni dai figli: prima in ordine di linee e quindi in ordine di indice */
    for (j = 1; j <= H; j++) {
        /* il padre calcola in modo random l'indice del figlio di cui considerera' il valore inviato */
        r = mia_random(N);
        /* stampa di controllo */
        printf("--------------------------\n");
        printf("DEBUG: Il numero generato in modo random (per la linea %d) compreso fra 0 e %d per selezionare il figlio e' %d\n", j, N - 1, r);
        printf("--------------------------\n");

        for (i = 0; i < N; i++) {
            /* il padre recupera tutti i valori interi dai figli */
            read(pipedFP[i][0], &valore, sizeof(valore));
            /* ma si salva solo il valore del figlio identificato in modo random */
            if (i == r)
                giusto = valore;
        }
        /* il padre calcola in modo random l'indice della linea che inviera' a tutti i figli */
        r = mia_random(giusto);
        /* stampa di controllo */
        printf("--------------------------\n");
        printf("DEBUG: Il numero generato in modo random compreso fra 0 e %d per selezionare l'indice della linea %d-esima e' %d\n", giusto - 1, j, r);
        printf("--------------------------\n");
        /* il padre deve inviare a tutti i figli l'indice */
        for (i = 0; i < N; i++)
            write(pipedPF[i][1], &r, sizeof(r));
    }

    /* Il padre aspetta i figli salvando lo status */
    for (int i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(9);
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