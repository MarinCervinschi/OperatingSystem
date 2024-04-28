#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* itero su tutti i parametri passati */
    for (int i = 1; i < argc; i++) {
        /* controllo che i parametri siano file */
        
        int fd1; /* variabile per valore di ritorno open */
        if ((fd1 = open(argv[i], O_RDONLY)) < 0) {
            printf("Errore in apertura file per %s dato che fd1 = %d\n", argv[i], fd1);
            exit(1);
        }
        close(fd1);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    /* itero su tutti i parametri passati */
    for (int i = 1; i < argc; i++) {
        int fd = open(argv[i], O_RDONLY);

        int nread; /* nread numero caratteri lettii */
        char buffer[BUFSIZ]; /* buffer per la lettura/scrittura */
        /* leggi tutto il file */
        while ((nread = read(fd, buffer, BUFSIZ)) > 0) {
            /* scrittura sullo standard output dei caratteri letti */
            write(1, buffer, nread);
        }
    }
    
    return 0;
}