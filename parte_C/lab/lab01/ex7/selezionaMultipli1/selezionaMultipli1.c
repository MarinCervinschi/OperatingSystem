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

    int nread;

    char* buffer = malloc((N + 1) * sizeof(char));
    if (buffer == NULL) {
        printf("Error: allocazione dinamica fallita\n");
        exit(4);
    }
    int idx = 1;
    while ((nread = read(F, buffer, N)) > 0) {
        if (nread == N) {
            printf("Il carattere multiplo %d-esimo all'interno del file '%s' e' '%c'\n", idx++, argv[1], buffer[N - 1]);
        } else {
            printf("Il file non ha una dimensione multipla di %d\n", N);
        }
    }

    exit(0);
}