/* File 31Mag19.c */
/* Standard compliance: C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */


/* Struttura dati da inviare al padre */
typedef struct {
    int pidNipote; /* variabile c1 del testo */
    int lunghezza; /* variabile c2 del testo */
    char linea[250] /* variabile c3 del testo */;
} infoFiglio;

typedef int pipe_t[2];

int main(int argc, char **argv) {
    /* controllo numero parametri */
    if (argc < 4) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 file3 ... fileN\n", argv[0]);
        exit(1);
    }

    /* salvo il numero di file */
    int N = argc - 1;
    pipe_t* piped = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (piped == NULL) {
        printf("##################################################\n");
        printf("Error: allocazione della memoria per le pipe\n");
        printf("##################################################\n");
        exit(2);
    }

    /* Creazione delle pipe */
    for (int i = 0; i < N; i++) {
        if (pipe(piped[i]) < 0) {
            printf("##################################################\n");
            printf("Error: nella creazione della pipe %d-esima\n", i);
            printf("##################################################\n");
            exit(3);
        }
    }

    printf("DEBUG: Sono il  padre con pid = %d e sto per generare %d figli con %d nipoti\n", getpid(), N, N);

    int pid;
    for (int i = 0; i < N; i++) {
        
        if ((pid = fork()) < 0) {
            printf("##################################################\n");
            printf("Error: nella fork per il figlio %d-edimo\n", i);
            printf("##################################################\n");
            exit(3);
        }

        if (pid == 0) {
            /* Figlio */

            /* chiusura delle pipe non usate */
            for (int j = 0; j < N; j++) {
                
                close(piped[j][0]);
                if (j != i) {
                    close(piped[j][1]);
                }
            }

            /* Creazione della pipe per il nipote */
            pipe_t pipedNipote;
            if (pipe(pipedNipote) < 0) {
                printf("##################################################\n");
                printf("Error: nella creazione della pipe per il nipote %d\n", i);
                printf("##################################################\n");
                exit(-1);
            }

            /* creazione del nipote */
            if ((pid = fork()) < 0) {
                printf("##################################################\n");
                printf("Error: nella fork per il nipote %d-edimo\n", i);
                printf("##################################################\n");
                exit(-1);
            }

            if (pid == 0) {

                /* Nipote */

                /* Chiusura della pipe del padre in scrittura */
                close(piped[i][1]);


                /* Redirezione dello stdout sulla pipe */
                close(1);
                dup(pipedNipote[1]);
                /* Chiusura della pipe in lettura e in scrittura */
                close(pipedNipote[0]);
                close(pipedNipote[1]);

                /* Costruiamo la stringa di opzione per il comando sort */
                char opzione[3]; /* variabile per l'opzione */
                sprintf(opzione, "-%c", 'f');
                /* Il nipote diventa il comando sort: bisogna usare le versioni dell'exec con la p in fondo in modo da usare la variabile di ambiente PATH  */
                execlp("sort", "sort", opzione, argv[i+1], (char *)0);

                /* Se execlp ritorna, c'è stato un errore */
                printf("##################################################\n");
                printf("Error: execlp per il nipote %d\n", i);
                printf("##################################################\n");
                exit(-1);
            }

            /* Figlio */

            /* Chiusura della pipe in scrittura */
            close(pipedNipote[1]);

            /* Lettura del risultato del nipote */
            infoFiglio infoNipote;
            char c;

            infoNipote.pidNipote = pid;
            infoNipote.lunghezza = 0;

            /* Lettura del risultato del nipote */
            while (read(pipedNipote[0], &c, 1) > 0) {
                infoNipote.linea[infoNipote.lunghezza++] = c;
                if (c == '\n') {
                    infoNipote.linea[infoNipote.lunghezza - 1] = '\0';
                    break;
                }
            }

            /* comunicazione del risultato al padre */
            write(piped[i][1], &infoNipote, sizeof(infoFiglio));

            /* Attesa della terminazione del nipote */
            int pidNipote, statusNipote;
            if ((pidNipote = wait(&statusNipote)) < 0) {
                printf("##################################################\n");
                printf("Error: nella wait per il nipote %d\n", i);
                printf("##################################################\n");
                exit(-3);
            }

            /* Controllo del valore di ritorno del nipote */
            if (WIFEXITED(statusNipote) == 0) {
                printf("##################################################\n");
                printf("Error: il nipote %d non è terminato correttamente\n", i);
                printf("##################################################\n");
                exit(-4);
            } else {
                printf("DEBUG: Il nipote %d con pid = %d è terminato correttamente\n", i, pidNipote);
                exit(infoNipote.lunghezza -1);
            }
        }
    }

    /* Padre */

    /* Chiusura delle pipe non usate */
    for (int i = 0; i < N; i++) {
        close(piped[i][1]);
    }

    /* Lettura dei risultati dai figli */
    for (int i = 0; i < N; i++) {

        /* Lettura del risultato del figlio */
        infoFiglio info;
        if (read(piped[i][0], &info, sizeof(infoFiglio)) < 0) {
            printf("##################################################\n");
            printf("Error: nella lettura del figlio %d\n", i);
            printf("##################################################\n");
            exit(4);
        }

        printf("DEBUG: Il figlio %d-esimo associato al file %s ha trovato:\n", i, argv[i + 1]);
        printf("'pidNipote -> %d; lunghezza -> %d; linea -> %s'\n", info.pidNipote, info.lunghezza, info.linea);        
    }

    /* Attesa della terminazione dei figli */
    int pidFiglio, statusFiglio; /* variabili per la wait */
    for (int i = 0; i < N; i++) {
        if ((pidFiglio = wait(&statusFiglio)) < 0) {
            printf("##################################################\n");
            printf("Error: nella wait per il figlio %d\n", i);
            printf("##################################################\n");
            exit(4);
        }

        /* Controllo del valore di ritorno del figlio */
        int result = WEXITSTATUS(statusFiglio);

        if (result == 0) {
            printf("##################################################\n");
            printf("Error: il figlio %d non è terminato correttamente\n", i);
            printf("##################################################\n");
            exit(5);
        } else {
            printf("DEBUG: Il figlio %d con pid = %d è terminato correttamente ritornando %d\n", i, pidFiglio, result);
        }
    }

    exit(0);
}