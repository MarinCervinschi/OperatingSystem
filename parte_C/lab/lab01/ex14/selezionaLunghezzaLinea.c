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
        printf("Errore in apertura file per '%s' -> FILE NON ESISTE\n", argv[1]);
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
    int n = atoi(argv[2]);

    int j = 0;
    char buffer[256];
    int trovata = 0;
    int idx = 1;

    while (read(F, &buffer[j], 1) != 0) {
        if (buffer[j] == '\n') {
            if (j + 1 == n) {
                buffer[j + 1] = '\0'; /* rendiamo buffer una stringa */
                printf("La linea '%d' del file '%s' lunga '%d' caratteri e':\n%s\n", idx++, argv[1], n, buffer);
                trovata = 1;
            }
            j = 0;
        } else {
            j++;
        }
    }

    if (!trovata) {
        printf("Non esiste nessuna linea con esattamente '%d' carattere in '%s'\n", n, argv[1]);
    }

    exit(0);
}