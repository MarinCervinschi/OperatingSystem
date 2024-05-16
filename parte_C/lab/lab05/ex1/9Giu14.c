/* File 9Giu14.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */



int main(int argc, char **argv) {
    /* Controllo argomenti */
    if (argc < 3) {
        printf("##################################################\n");
        printf("Error: Numero di parametri '%d' sbagliato\n", argc - 1);
        printf("Uso: %s <file1> <file2>\n", argv[0]);
        printf("##################################################\n");
        exit(1);
    }
    
    int N = argc - 1;
    int piped[N][2];

    printf("DEBUG: Sono il  padre con pid = %d e sto per generare %d figli con %d nipoti\n", getpid(), N, N);

    int pid;
    for (int i = 0; i < N; i++) {

        /* creazione della pipe */
        if (pipe(piped[i]) < 0) {
            printf("##################################################\n");
            printf("Error: nella creazione della pipe %d-esima\n", i);
            printf("##################################################\n");
            exit(2);
        }

        /* creazione pipe per il nipote */
        int pipedNipote[2];
        if (pipe(pipedNipote) < 0) {
            printf("##################################################\n");
            printf("Error: nella creazione della pipe per il nipote %d-esimo\n", i);
            printf("##################################################\n");
            exit(3);
        }
        
        if ((pid = fork()) < 0) {
            printf("##################################################\n");
            printf("Error: nella fork per il figlio %d-edimo\n", i);
            printf("##################################################\n");
            exit(3);
        }

        if (pid == 0) {
            /* Figlio */

            printf("DEBUG: Sono il figlio %d con pid = %d\n", i, getpid());

            /* creazione del nipote */
            if ((pid = fork()) < 0) {
                printf("##################################################\n");
                printf("Error: nella fork per il nipote %d-edimo\n", i);
                printf("##################################################\n");
                exit(-1);
            }

            if (pid == 0) {
                /* Nipote */
                printf("DEBUG: Sono il nipote %d con pid = %d\n", i, getpid());

                /* Chiusura della pipe in lettura */
                close(pipedNipote[0]);

                /* Redirezione dello stdout sulla pipe */
                close(1);
                dup(pipedNipote[1]);
                close(pipedNipote[1]);

                execlp("wc", "wc", "-l", argv[i + 1], (char *)0);

                /* Se execlp ritorna, c'è stato un errore */
                printf("##################################################\n");
                printf("Error: execlp per il nipote %d\n", i);
                printf("##################################################\n");
                exit(-1);
            }

            /* Figlio */

            /* Lettura del risultato del nipote */
            long int lunghezza = 0;
            char buffer[BUFSIZ];
            char c;

            /* Chiusura della pipe in scrittura */
            close(pipedNipote[1]);

            /* Lettura del risultato del nipote */
            while (read(pipedNipote[0], &c, 1) > 0) {
                buffer[lunghezza++] = c;
                if (c == '\n') {
                    buffer[lunghezza] = '\0';
                    break;
                }
            }

            /* conversione del risultato del nipote */
            int lunghezzaNipote = atoi(buffer);
            if (lunghezzaNipote < 0) {
                printf("##################################################\n");
                printf("Error: lunghezzaNipote %d\n", lunghezzaNipote);
                printf("##################################################\n");
                exit(-2);
            }

            /* comunicazione del risultato al padre */

            write(piped[i][1], &lunghezzaNipote, sizeof(lunghezzaNipote));

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
                exit(WIFEXITED(statusNipote));
            }
        }
    }

    /* Padre */


    /* Lettura dei risultati dai figli */
    long int lunghezza;
    long int lunghezzaTotale = 0;
    for (int i = 0; i < N; i++) {
        /* Chiusura della pipe in scrittura */
        close(piped[i][1]);

        /* Lettura del risultato del figlio */
        if (read(piped[i][0], &lunghezza, sizeof(lunghezza)) > 0) {
            lunghezzaTotale += lunghezza;
        }

        /* Chiusura della pipe in lettura */
        close(piped[i][0]);

        printf("DEBUG: Il figlio %d ha trovato %ld linee\n", i, lunghezza);
        int pidFiglio, statusFiglio;
        if ((pidFiglio = wait(&statusFiglio)) < 0) {
            printf("##################################################\n");
            printf("Error: nella wait per il figlio %d\n", i);
            printf("##################################################\n");
            exit(4);
        }

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

    printf("DEBUG: Il padre ha trovato %ld linee\n", lunghezzaTotale);

    exit(0);
}