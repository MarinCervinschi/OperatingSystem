/* File 9Set16.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <sys/types.h> /* SYStem TYPES: pid_t */
#include <stdbool.h> /* Standard Boolean: bool, true, false */
#define N 26 /* numero di figli da creare: il valore e' COSTANTE! */

typedef int pipe_t[2]; /* tipo di dato per pipe */

/* struttura in cui 
il primo campo rappresenta il carattere e 
il secondo campo il numero di occorrenze di quel carattere trovate nel file */
typedef struct {
    char ch;        /* campo v1 del testo */
    long int occ;   /* campo v2 del testo */
} data;

/* funzione di ordinamento */
void bubbleSort(data *v, int dim) {
    int i;
    data tmp;
    int ordinato = 0;
    while(dim > 0 && !ordinato) {
        ordinato = 1;
        for(i=0; i < dim-1; i++) {
            if(v[i].occ > v[i+1].occ) {
                tmp = v[i];
                v[i] = v[i+1];
                v[i+1] = tmp;
                ordinato = 0;
            }
        }
        dim--;
    }
}


int main(int argc, char **argv) {
    /* controllo numero parametri */
    if (argc != 2) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1\n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid[N]; 			        /* array STATICO di process identifier dei processi generati tramite fork */
    char c; 				        /* carattere letto dai figli */
    pipe_t piped[N];                /* array STATICO di pipe usate a pipeline da primo figlio, a secondo figlio .... ultimo figlio e poi a padrem */
    int i, j;                       /* indici per i cicli */
    int fd; 				        /* file descriptor del file aperto dai figli in lettura */
    data d[N]; 				        /* array STATICO di strutture che i figli si passano nella pipeline, fino al padre */
    char C; 				        /* carattere da cercare */
    long int curr_occ; 		        /* conteggio corrente */
    int nr,nw;				        /* variabili per salvare valori di ritorno di read e write da/su pipe */
    int pidFiglio, status, ritorno;	/* per valore di ritorno figli */
    /* ------------------------------------ */

    /* creazione delle 26 pipe per la comunicazione */
	for(i = 0; i < N; i++) {
        if (pipe(piped[i]) < 0) {
            printf("Errore nella creazione delle pipe\n");
            exit(2);
        }
    }

    /* creazione dei 26 figli */
    printf("--------------------------\n");
    printf("DEBUG: La pid del padre e' %d, deve generare %d figli\n", getpid(), N);
    printf("--------------------------\n");
    
    /* Per la creazione di N figli */
    for(int i = 0; i < N; i++) {

        if ((pid[i] = fork()) < 0) {
            /* Fork fallita */
            printf("Errore in fork per il figlio %d-esimo\n", i);
            exit(3);
        }
        
        if (pid[i] == 0) {
            /* CODICE DEL FIGLIO*/

            /* inizializziamo le variabili per il figlio corrente */
			C = 'a'+i;  	/* ogni figlio deve essere associato ad una lettera dell'alfabeto inglese (minuscola), iniziando dalla 'a' */
			curr_occ = 0L;	/* inizializziamo il conteggio */
			printf("DEBUG: Sono il figlio di indice %d e pid %d e sto per cercare il carattere %c nel file %s\n", i, getpid(), C, argv[1]);
    

            /* chiusura di tutte le pipe che il figlio non usa */
            for(j = 0; j < N; j++) {
                if (j != i)
                    close(piped[j][1]);
                if ((i == 0) || (j != i-1))
                    close(piped[j][0]);
            }

            /* apertura del file (l'unico argomento passato)*/
            if ((fd = open(argv[1], O_RDONLY)) < 0) {
                printf("Errore in apertura file %s\n", argv[1]);
                exit(-1);
            }

            /* leggiamo il file carattere per carattere */
            while (read(fd, &c, 1)) {
                if (c == C)
                    curr_occ++;
            }

            if (i != 0) {

                /* leggiamo dalla pipe il valore corrente */
                nr = read(piped[i-1][0], d, sizeof(d));

                if (nr != sizeof(d)) {
                    printf("Errore in lettura dalla pipe %d-esima\n", i-1);
                    exit(-1);
                }
            }

            /* aggiorniamo il valore corrente */
            d[i].ch = C;
            d[i].occ = curr_occ;

            /* scriviamo sulla pipe il valore aggiornato */
            nw = write(piped[i][1], d, sizeof(d));
            if (nw != sizeof(d)) {
                printf("Errore in scrittura sulla pipe %d-esima\n", i);
                exit(-1);
            }

            /* torniamo l'ultimo carattere letto */
            exit(c);
    
            /*FINE CODICE DEL FIGLIO*/
        }
    }
    
    /* padre */

    /* chiusura di tutte le pipe che il padre non usa */
    for(i = 0; i < N; i++) {
        close(piped[i][1]);
        if (i != N-1)
            close(piped[i][0]);
    }

    /* il padre deve leggere un solo array, chiaramente controllando l'esito della lettura! */
    nr = read(piped[N-1][0], d, sizeof(d));
    if (nr != sizeof(d)) {
        printf("Errore in lettura dalla pipe %d-esima\n", N-1);
        exit(4);
    } else {
        bubbleSort(d, N);
        for(i = 0; i < N; i++) {
            printf("Il figlio di indice %d e pid %d ha trovato %ld occorrenze del carattere %c\n", d[i].ch-'a', pid[(d[i].ch-'a')], d[i].occ, d[i].ch);
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for(int i = 0; i < N; i++) {
        if ((pidFiglio = wait(&status)) < 0) {
            /* La wait non ha avuto successo */
            printf("Errore in wait\n");
            exit(5);
        }
    
        printf("--------------------------\n");
        printf("DEBUG: Terminato figlio con PID = %d\n", pidFiglio);
        printf("--------------------------\n");
        if (WIFEXITED(status)) {
            /* Ricavo l'exitcode del figlio con la funzione WEXITSTATUS */
            ritorno = WEXITSTATUS(status);
            printf("Il figlio con pid=%d ha ritornato il carattere %c (in decimale %d, se 255 problemi)\n", pidFiglio, ritorno, ritorno);
        } else {
            /* Lo status riporta una terminazione anomala */
            printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        }
    }

    exit(0);
}