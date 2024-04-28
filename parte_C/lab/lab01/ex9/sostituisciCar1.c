#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 4) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }

    /* controllo che il primo parametro sia un file */
    
    int fd1; /* variabile per valore di ritorno open */
    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        printf("Errore in apertura file per '%s' -> FILE NON ESISTE\n", argv[1]);
        exit(2);
    }
    close(fd1);

    /* controllo che il secondo parametro sia un singolo carattere */
    if (argv[2][1] != '\0') {
        printf("Error: %s non singolo carattere\n", argv[2]);
        exit(3);
    }

    /* controllo che il terzo parametro sia un singolo carattere */
    if (argv[3][1] != '\0') {
        printf("Error: %s non singolo carattere\n", argv[3]);
        exit(4);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int F = open(argv[1], O_RDWR);
    char Cx = argv[2][0];
    char Change = argv[3][0];
    
    /* leggi tutto il file */
    char c;
    while (read(F, &c, 1)) {
        if (c == Cx) {
            lseek(F, -1L, 1);
            write(F, &Change, 1);
        }
    }
    exit(0);
}