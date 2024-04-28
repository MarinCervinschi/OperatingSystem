#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
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
    close(fd1);

    /* controllo che il secondo parametro sia un numero strettamente positivo */
    int num = atoi(argv[2]);
    if (num <= 0) {
        printf("Error: %s non e' un numero strettamente positivo\n", argv[2]);
        exit(3);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int F = open(argv[1], O_RDONLY);
    int N = atoi(argv[2]);

    /* calcoliamo la lunghezza del file */
    long int lunghezza = lseek(F, 0L, SEEK_END);

    int idx = 1;
    int pos = 0L;

    while (pos < lunghezza) {
        /* calcoliamo la posizione del carattere che deve essere letto */
        pos=(long int)(idx * N);

        if (pos < lunghezza) {
            char ch;
            /* chiamiamo la lseek passando come offset pos-1 dall'inizio del file */
        	lseek(F, pos - 1, SEEK_SET);
        	read(F, &ch, 1);
			printf("Il carattere multiplo %d-esimo all'interno del file '%s' e' '%c'\n", idx++, argv[1], ch); 
        } else {
            printf("Il file non ha una dimensione multipla di %d\n", N);
        }
    }
    
    exit(0);
}