/* File provaPipe-bis.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 3) {
        printf("Error: numero di parametri '%d' errato\n", argc - 1);
        exit(1);
    }
    
}

int main(int argc, char **argv) {
    
    checkParams(argc, argv);

    int fd1, fd2;
    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        printf("Errore apertura file '%s'\n", argv[1]);
        exit(2);
    }
    printf("Aperto file '%s' con fd %d\n", argv[1], fd1);

    if ((fd2 = open(argv[2], O_RDONLY)) < 0) {
        printf("Errore apertura file '%s'\n", argv[2]);
        exit(3);
    }
    printf("Aperto file '%s' con fd %d\n", argv[2], fd2);

    printf("/------------------------------------------/\n");
    printf("  DEBUG -> Chiudo il file '%s' con fd %d\n", argv[1], fd1);
    printf("/------------------------------------------/\n");

    close(fd1);

    int piped[2];
    if (pipe(piped) < 0) {
        printf("Errore creazione pipe\n");
        exit(4);
    }

    printf("pipe creata con piped[0] %d\n", piped[0]);
    printf("pipe creata con piped[1] %d\n", piped[1]);

    exit(0);
}