/* File prova.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */


int main(int argc, char **argv) {

    printf("Vuoi effettuare la chiamata ricorsiva? [no -> 0; yes -> != 0]\n");
    int N;
    scanf("%d", &N);

    if (N == 0) {
        printf("Non eseguiamo la chiamata ricorsiva\n");
        exit(0);
    }

    execl(argv[0], argv[0], (char *) 0);
    
    printf("Errore in execl\n");
    exit(1);
}