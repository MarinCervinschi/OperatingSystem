#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* funzione per contare il numero di occorenze di un carattere all'interno di un file */
long int numeroDiOccorenze(int file, char Cx) {
    long int conta = 0;
    char c; /* variabile temporanea per salvare il char corrente */

    /* leggi dal file finche non e' vuoto */
    while (read(file, &c, 1)) {
        if (c == Cx) {
            conta++;
        }
    }

    return conta;
}

int main(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 3) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }

    /* controllo che il primo parametro sia un file */
    
    int fd1; /* variabile per valore di ritorno open */
    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        printf("Errore in apertura file per %s dato che fd1 = %d\n", argv[1], fd1);
        exit(2);
    }

    /* controllo che il secondo parametro sia un singolo carattere */
    if (argv[2][1] != '\0') {
        printf("Error: %s non singolo carattere\n", argv[2]);
        exit(3);
    }
    char Cx = argv[2][0];

    /* stampo il nome del eseguibile e il numero di parametri */
    printf("L'eseguibile e' %s e ha %d parametri: file -> %s; Cx -> %c\n", argv[0], argc - 1, argv[1], Cx);

    long int totale = numeroDiOccorenze(fd1, Cx);
    printf("Il file '%s' contiene %ld caratteri '%c'\n", argv[1], totale, Cx);
    close(fd1);

    return 0;
}