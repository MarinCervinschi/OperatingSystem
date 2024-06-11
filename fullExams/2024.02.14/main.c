/* File main.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <string.h> /* STRING: strlen, strcpy */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

typedef struct{
    char c1[12];    /* deve contenere la stringa TROVATA o NON TROVATA*/
    int c2; /* deve contenere il pid del processo nipote */
} Strut;
/* ATTENZIONE 'Strut' variabile del testo */

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 4) {
        printf("Error: numero parametri '%d' errato\n", argc);
        printf("Uso: %s file stringa1 stringa2 -opt[.. stringaN] \n", argv[0]);
        exit(1);
    }

    /* dato che in questo caso il programma viene chiamato dalla parte shell siamo sicuri sulla validità dei parametri */

    /* -------- Variabili locali ---------- */
    int pid;                	        /* l'array di process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    /* ATTENZIONE 'N' variabile del testo */
    pipe_t *piped;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    int n, j;               			/* indici per i cicli */
    /* ATTENZIONE 'n' variabile del testo */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int nr,nw;							/* variabili per salvare valori di ritorno di read e write da/su pipe */
    Strut* cur;                            /* l'array di strutture da usare nei figli e nipoti */
    /* ATTENZIONE 'cur' variabile del testo */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 2; /* argc - 2 perche' il primo parametro e' il file e gli altri N i processi da creare*/ 

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

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(4);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            printf("***********************\n");
            printf("DEBUG: Sono il figlio %d-esimo con pid=%d associato alla stringa '%s'\n", n, getpid(), argv[n+2]);
            printf("***********************\n");

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                if (j != n) {
                    close(piped[j][1]);
                }
                if ((n == 0) || (j != n-1)) {
                    close(piped[j][0]);
                }
            }

            /* creazione del nipote */
            if((pid = fork()) < 0) {
                printf("Errore: Impossibile creare il processo nipote %d-esimo!\n", n);
                exit(-1);
            }

            /* Codice del processo nipote */
            if (pid == 0) {

                /* Codice del nipote */
                printf("#####################################\n");
                printf("Sono il nipote %d-esimo con pid=%d associato anche io alla stringa '%s'\n", n, getpid(), argv[n+2]);
                printf("#####################################\n");

                /* Chiusura degli unici lati di pipe rimasti aperti: il nipote non usa le pipe! */
				close(piped[n][1]);
				if (n != 0) {
                    close(piped[n-1][0]);
                }

                /* Ridirezione dello stdout su /dev/null */
                close(1);
                open("/dev/null", O_WRONLY);

                /* Ridirezione dello stderr su /dev/null */
                close(2);
                open("/dev/null", O_WRONLY);

                /* cerco la stringa nel file */
                execlp("grep", "grep", argv[n + 2], argv[1], (char *)0);

                /* se sono qui c'è stato un errore */
                printf("Errore in execlp di grep\n");

                exit(-1); /* torno un valore diverso da zero per indicare insuccesso*/
            }

            /* Codice del processo figlio */
            /* allocazione dell'array di strutture specifico di questo figlio */
            /* creiamo un array di dimensione n+1 anche se leggeremo n strutture, dato che poi ci servira' riempire la n+1-esima struttura! */
            if ((cur = (Strut *)malloc((n + 1) * sizeof(Strut))) == NULL) {
                printf("Errore allocazione cur\n");
                exit(-1);
            }
            /* lettura da pipe dell'array di strutture per tutti i figli a parte il primo */
            if (n != 0) {
                nr = read(piped[n - 1][0], cur, n * sizeof(Strut));
                if (nr != n * sizeof(Strut)) {
                    printf("Figlio %d ha letto un numero di strutture sbagliate %d\n", n, nr);
                    exit(-1);
                }
            }
            /* inizializziamo l'ultima struttura che e' quella specifica del figlio corrente (nel caso del primo figlio sara' l'unica struttura */
            cur[n].c2 = pid;

            ritorno = 1;

			/* Aspettiamo la fine del nipote/grep */
			pid = wait(&status);
			if (pid < 0) {
				printf("Errore in wait\n");
				/* si decide di mandare la stringa NON TROVATA al padre e tornare il valore 1 */
                strcpy(cur[n].c1, "NON TROVATA");
			}

            if ((status & 0xFF) != 0) {
                printf("Nipote terminato in modo involontario\n");
                /* si decide di mandare la stringa NON TROVATA al padre e tornare il valore 1 */
                strcpy(cur[n].c1, "NON TROVATA");
            } else {
                /* recupero il suo codice di ritorno */
                ritorno = (status >> 8) & 0xFF;
                if (ritorno == 0) { /* stringa trovata */
                    strcpy(cur[n].c1, "TROVATA");
                } else {
                    strcpy(cur[n].c1, "NON TROVATA");
                }
            }

            /* tutti i figli mandano in avanti, l'ultimo figlio manda al padre un array di strutture (per tutti i figli a parte il primo sono i strutture ricevute dal processo precedente e la i+1-esima che e' la propria) */
            nw = write(piped[n][1], cur, (n + 1) * sizeof(Strut));
            if (nw != (n + 1) * sizeof(Strut)) {
                printf("Figlio %d ha scritto un numero di strutture sbagliate %d\n", n, nr);
                exit(-1);
            }

            exit(ritorno); /* fine codice del figlio */
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(n = 0; n < N; n++) {
        close(piped[n][1]);
        if (n != N-1)
            close(piped[n][0]);
    }

    /* allocazione dell'array di strutture specifico per il padre */
    /* creiamo un array di dimensione N quanto il numero di figli! */
    if ((cur = (Strut *)malloc(N * sizeof(Strut))) == NULL) {
        printf("Errore allocazione cur nel padre\n");
        exit(5);
    }

    /* il padre deve leggere l'array di strutture che gli arriva dall'ultimo figlio */
    nr = read(piped[N - 1][0], cur, N * sizeof(Strut));
    if (nr != N * sizeof(Strut)) {
        printf("Padre ha letto un numero di strutture sbagliate %d\n", nr);
        exit(6);
    }
    printf("--------------------------\n");
    printf("DEBUG-Padre ha letto un numero %d di strutture\n", N);
    printf("--------------------------\n");
    /* il padre deve stampare i campi delle strutture ricevute */
    for (n = 0; n < N; n++) {
        if (strcmp(cur[n].c1, "TROVATA") == 0) {
            printf("Il figlio di indice %d ha generato un nipote con pid %d che ha trovato la stringa %s nel file %s\n", n, cur[n].c2, argv[n + 2], argv[1]);
        } else {
            printf("Il figlio di indice %d ha generato un nipote con pid %d che NON ha trovato la stringa %s nel file %s\n", n, cur[n].c2, argv[n + 2], argv[1]);
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for (n = 0; n < N; n++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", n);
            exit(7);
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