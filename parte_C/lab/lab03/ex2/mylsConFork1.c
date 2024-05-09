/* File mylsConFork1.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 2) {
        printf("Error: numero di parametri '%d' errato\n", argc);
        printf("Usage: %s <directory>\n", argv[0]);
        exit(1);
    }
    
    /* controllo che il parametro sia una directory */

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
        printf("DEBUG-Esecuzione di ls -l da parte del figlio con pid %d e con parametro %s\n", getpid(), argv[1]);
        printf("--------------------------------\n");
        execl("/bin/ls", "ls", "-l", argv[1], (char *) 0);
        
        /* Eseguiamo sono in caso di fallimento della EXECL */
        printf("Errore in execl\n");
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

    if (WIFEXITED(status)) {
        printf("Il figlio con pid %d ha terminato correttamente con stato %d\n", pidFiglio, WEXITSTATUS(status));
    } else {
        printf("Il figlio con pid %d ha terminato in modo anomalo\n", pidFiglio);
    }

    exit(0);
}