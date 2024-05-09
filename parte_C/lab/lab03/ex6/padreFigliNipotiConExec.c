/* File padreFigliNipotiConExec.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */

#define PERM 0644 /* DIRitti di accesso ai file */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc < 4) {
        printf("Error: numero di parametri '%d' errato\n", argc);
        printf("Uso corretto: %s file1 file2 file3... fileN\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int N = argc - 1;

    printf("DEBUG-Sono il processo padre con pid %d e creero' %d processi figli che generanno a loro volta ognuno un nipote\n", getpid(), N);

    for (int i = 0; i < N; i++) {
        int pid;
        if ((pid = fork()) < 0) {
            printf("Errore nella fork\n");
            exit(2);
        }

        if (pid == 0) {
            /* codice figlio */
            printf("Sono il figlio con pid %d\n", getpid());

            /* alloco la memoria quanto la lunghezza del file + 6 */
            /* 6 = 1 (".") + 4 ('sort') + 1 ('\0') */
            char* FOut = malloc((strlen(argv[i + 1]) + 6) * sizeof(char));
            if (FOut == NULL) {
                printf("Errore nell'allocazione della memoria\n");
                exit(-1);
            }

            /* copio il nome del file in FOut */
            strcpy(FOut, argv[i + 1]);

            /* aggiungo l'estensione .sort */
            strcat(FOut, ".sort");

            /* creo il file .sort */
            int fdw;
            if ((fdw = creat(FOut, PERM)) < 0) {
                printf("Impossibile creare il file %s\n", FOut);
                exit(-1);
            }
            close(fdw);

            /* creo il nipote */
            if ((pid = fork()) < 0) {
                printf("Errore nella fork del nipote\n");
                exit(-1);
            }

            if (pid == 0) {
                /* codice nipote */
                printf("Sono il nipote %d-esimo con pid %d, sto per eseguire la sort per il file %s\n", i, getpid(), argv[i + 1]);

				/* chiudiamo lo standard input dato che la specifica dice che dobbiamo usare il comando-filtro sort */
                close(0);

                /* redirezione dell'output */
                if ((open(argv[i + 1], O_RDONLY)) < 0) {
                    printf("Errore nell'apertura del file %s\n", argv[i + 1]);
                    printf("IL FILE NON ESISTE\n");
                    exit(-1);
                }
                /* chiudiamo lo standard output dato che la specifica indica che il risultato del comando-filtro sort va scritto sul file creato da ogni figlio (padre di questo processo) */
                close(1);

                /* apriamo il file creato solo in scrittura */
                if ((open(FOut, O_WRONLY)) < 0) {
                    printf("Errore nell'apertura del file %s in scrittura\n", FOut);
                    exit(-1);
                }

                /* eseguo il comando sort */
                execlp("sort", "sort", (char*)0);

                /* usiamo perror che scrive su standard error, dato che lo standard output e' collegato ad un file */
                perror("Problemi di esecuzione del sort da parte del nipote");
                exit(-1); 
            } /* fine codice nipote */

            /* codice figlio */
            int pidNipote, statusNipote;
            if ((pidNipote = wait(&statusNipote)) < 0) {
                printf("Errore nella wait del figlio\n");
                exit(-1);
            }
            int exitReturnNipote = WEXITSTATUS(statusNipote);
            if (exitReturnNipote == 0) {
                printf("Il nipote con pid %d ha terminato con successo\n", pidNipote);
                exit(exitReturnNipote);
            } else {
                printf("Il nipote con pid %d ha terminato con errore\n", pidNipote);
            }
        } /* fine codice figlio */
    } /* fine for */

    for (int i = 0; i < N; i++) {

        /* codice padre */
        int pidFiglio, status;
        if ((pidFiglio = wait(&status)) < 0) {
            printf("Errore nella wait\n");
            exit(4);
        }

        printf("-----------------------------\n");
        int exitReturn = WEXITSTATUS(status);
        if (exitReturn == 0) {
            printf("Il figlio con pid %d ha terminato con successo\n", pidFiglio);
        } else {
            printf("Il figlio con pid %d ha terminato con errore\n", pidFiglio);
        }
    } /* fine for */

    exit(0);
}