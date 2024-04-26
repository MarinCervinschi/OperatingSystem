#include <stdio.h> 	/* per poter usare printf e altre funzioni di I/O */
#include <stdlib.h>	/* per poter usare la primitiva exit */
#include <unistd.h>	/* per poter usare la primitiva close */
#include <fcntl.h>	/* per poter usare le costanti per la open (O_RDONLY, O_WRONLY e O_RDWR)*/

int main(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc != 4) {
        printf("Error: numero di parametri sbagliato\n");
        exit(1);
    }

    /* controllo che il primo parametro sia un file */

    int fd1; /* variabile per valore di ritorno open */
    if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
        printf("Errore in apertura file per %s dato che fd1 = %d\n", argv[1], fd1);
        exit(2);
    }

    close(fd1);	/* chiudiamo e quindi eliminiamo le informazioni relative all'elemento della tabella dei file aperti identificato da fd1 */

    /* controllo che il secondo parametro sia un numero > 0*/
    int N;
    if ((N = atoi(argv[2])) <= 0) {
        printf("Error: %s non numero o non strettamente positivo\n", argv[2]);
        exit(3);
    }

    /* controllo che il terzo parametro sia un sincolo carattere */
    char C;
    if ((C = argv[3][1]) != '\0') {
        printf("Error: %s non singolo carattere\n", argv[3]);
        exit(4);
    }

    /* stampo il nome del eseguibile + il numero dei parametri */
    printf("Il programma %s ha %d parametri\n", argv[0], argc - 1);

    /* stampo i parametri con spiegazione */
    printf("Il primo parametro e' il nome di un file: %s\n", argv[1]);
    printf("Il secondo parametro e' un numero strettamente positivo: %d\n", N);
    printf("Il terzo parametro e' un singolo carattere: %c\n", argv[3][0]);

    return 0;
}
