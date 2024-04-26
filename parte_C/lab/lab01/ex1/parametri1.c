#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    
    if (argc < 2) {
        printf("Error: numero di parametri errato\n");
        exit(1);
    }

    printf("Il programma %s ha %d parametri\n", argv[0], argc - 1);
    for (int i = 0; i < argc - 1; i++) {
        printf("Parametro %d: %s\n", i, argv[i + 1]);
    }
    
    return 0;
}
