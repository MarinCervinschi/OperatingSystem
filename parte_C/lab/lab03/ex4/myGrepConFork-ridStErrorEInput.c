/* File myGrepConFork-ridStError.c */

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
    if (argc != 3) {
        printf("Error: numero di parametri '%d' errato\n", argc);
        printf("Usage: %s <stringa> <file>\n", argv[0]);
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
        printf("DEBUG-Esecuzione di grep %s %s da parte del figlio con pid %d\n", argv[1], argv[2], getpid());
        printf("--------------------------------\n");

        /* redirigo lo STDIN sul file argv[2] */
        close(0);
        if (open(argv[2], O_RDONLY) < 0) {
            printf("Errore in apertura file '%s'\n", argv[2]);
            exit(-1);
        }

        /* redirigo lo STDOUT su /dev/null */
        close(1);
        open("/dev/null", O_WRONLY);

        /* redirigo anche lo STDERROR su /dev/null come dice il testo */
        close(2);
        open("/dev/null", O_WRONLY);
        execlp("grep", "grep", argv[1], (char *) 0); /* eseguo grep passando solo la stringa */

        /* eseguiamo solo in caso del fallimento del EXECL */
        /* non stampo nulla poiche' STDOUT -> /dev/null */
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
    /* controllo il risultato del figlio */
    if (WIFEXITED(status)) {
        int ritorno = WEXITSTATUS(status);
        if (ritorno == 0) {
            printf("La stringa '%s' e' stata trovata nel file '%s'\n", argv[1], argv[2]);
        } else if (ritorno == 1) {
            printf("La stringa '%s' non e' stata trovata nel file '%s'\n", argv[1], argv[2]);
        } else {
            printf("Il figlio con pid %d ha terminato in modo anomalo con stato %d\n", pidFiglio, ritorno);
        }
    } else {
        printf("Il figlio con pid %d ha terminato in modo anomalo\n", pidFiglio);
    }
    
    exit(0);
}