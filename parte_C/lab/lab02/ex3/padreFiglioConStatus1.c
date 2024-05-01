#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */

#include <time.h>

int mia_rand(int n) {
    int casuale;
    casuale = rand() % n;
    return casuale;
}

int main(int argc, char **argv) {
    srand(time(NULL));

    int pid, pidFiglio; /* pid per fork e pidFiglio per wait */
    int pidPadre = getpid();
    printf("La pid del padre e': %d\n", pidPadre);
    if ((pid = fork()) < 0) {
        //Fork fallita
        printf("Errore in fork\n");
        exit(1);
    }
    
    if (pid == 0) {
        /* CODICE DEL FIGLIO*/
    
        exit(mia_rand(100));
    
        /*FINE CODICE DEL FIGLIO*/
    }
    
    /* padre */
    printf("Generato figlio con PID = %d\n", pid);
    /* Il padre aspetta il figlio salvando lo status */
    int status;
    if ((pidFiglio = wait(&status)) < 0){
        /* La wait non ha avuto successo */
        printf("Errore in wait\n");
        exit(2);
    }

    /* Se il pid ritornato dalla wait e' corretto */
    if (pid == pidFiglio) {
        printf("Terminato figlio con PID = %d\n", pidFiglio);
        if (WIFEXITED(status)) {
            /* Ricavo l'exitcode del figlio con la funzione WEXITSTATUS */
            printf("Il figlio e' ritornato con codice: %d\n", WEXITSTATUS(status));
        } else {
            /* Lo status riporta una terminazione anomala */
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    } else {
        /* Il pid non corrisponde con il figlio aspettato */
        printf("Il pid della wait non corrisponde al pid della fork!\n");
        exit(3);
    }

    /* chiamo un secondo wait senza aver creato un nuovo figlio */
    if ((pidFiglio = wait(&status)) < 0) {
        /* la wait non ha avuoto successo, non avendo un secondo figlio in questo caso */   
        printf("Errore in wait\n");
        exit(4);
    }
    
    exit(0);
}