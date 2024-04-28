#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    if (argc == 1) {
        return;
    }
    /* controllo il numero di parametri */
    if (argc != 2) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }
    
    /* controllo che il primo parametro del carattere sia '-' */
    if (argv[1][0] != '-') {
        printf("Errore: carattere non valido: Usage is <-number>\n");
        exit(2);
    }

    /* controllo che il primo parametro sia un numero strettamente positivo */
    int num = atoi(argv[1]);
    if (-num <= 0) {
        printf("Error: %s non e' un numero strettamente positivo\n", argv[1]);
        exit(3);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int n;
    if (argc != 1) {
        n = -atoi(argv[1]);
    } else {
        n = 10;
    }

    /* leggi tutto il file */
    char c;
    int count = 1;
    while (read(0, &c, 1)) {
        if (c == '\n') {
            count++;
        }
        write(1, &c, 1);
        if (count > n) {
            break;
        }   
    }
    
    exit(0);
}