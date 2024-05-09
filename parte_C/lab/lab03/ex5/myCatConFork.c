/* File myCatConFork.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 2) {
        printf("Error: numero di parametri '%d' errato\n", argc);
        printf("Usage: %s <file>\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int pid;
    if ((pid = fork()) < 0) {
        /* Fork fallita */
        printf("Errore in fork\n");
        exit(2);
    }

    if (pid == 0) {
        /* Processo figlio */
        printf("Processo figlio\n");
        printf("DEBUG-Esecuzione di cat %s da parte del figlio con pid %d\n", argv[1], getpid());
        /* simulazione ridirezione del STDIN */
        close(0);

        /* apertura del file in sola lettura */
        int fd;
        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            printf("Errore in apertura del file '%s'\n", argv[1]);
            exit(1);
        }

        /* esecuzione di cat */
        printf("DEBUG-Ho aperto il file '%s' con fd=%d\n", argv[1], fd);
        printf("DEBUG-Esecuzione di cat %s\n", argv[1]);
        printf("--------------------------------\n");
        execl("mycat", "mycat", (char *) 0);

        printf("Errore in execlp\n");
        exit(-1); /* -1 perche' il figlio non ha terminato correttamente */
    }

    /* Processo padre */
    printf("Processo padre\n");
    printf("DEBUG-Il pid del figlio e' %d\n", pid);
    int pidFiglio, status;
    if ((pidFiglio = wait(&status)) < 0) {
        printf("Errore in wait\n");
        exit(3);
    }

    printf("--------------------------------\n");

    int exitStatus = WEXITSTATUS(status);
    if (exitStatus == 0) {
        printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi)\n", pidFiglio, exitStatus);
    } else {
        printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    }

    exit(0);
}