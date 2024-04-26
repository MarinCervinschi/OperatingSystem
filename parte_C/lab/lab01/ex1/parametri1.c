#include <stdio.h>
#include <stdlib.h> /* per exit() */

int main(int argc, char const *argv[]) {
    /* controllo il numero di parametri */
    if (argc < 2) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }

    /* stampo il numero totale di parametri e il nome del eseguibile */
    printf("Il programma %s ha %d parametri\n", argv[0], argc - 1);

    /* itero su tutti i parametri e li stampo, indicando l'indice */
    for (int i = 0; i < argc - 1; i++) {
        printf("Parametro %d: %s\n", i, argv[i + 1]);
    }
    
    return 0;
}
