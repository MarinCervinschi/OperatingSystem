#include <stdio.h>      /* Per funzioni di input/output come printf */
#include <stdlib.h>     /* Per funzioni di gestione della memoria come malloc e free, e controllo del processo come exit */
#include <unistd.h>     /* Per funzioni di sistema UNIX come fork e getpid */
#include <sys/wait.h>   /* Per la funzione wait che permette a un processo di aspettare la terminazione di un altro processo */

int main(int argc, char **argv) {
    
    int pidFiglio; /* pid per fork e pidFiglio per wait */
    int pidPadre = getpid(); /* Ottiene il pid del processo corrente (padre) */
    printf("La pid del padre e': %d\n", pidPadre); /* Stampa il pid del padre */
    
    /* padre */
    /* Il padre aspetta il figlio salvando lo status */
    int status;
    if ((pidFiglio = wait(&status)) < 0){ /* Il padre aspetta la terminazione del figlio */
        /* La wait non ha avuto successo */
        printf("Errore in wait\n"); /* Stampa un messaggio di errore se la wait fallisce */
        exit(1); /* Termina il processo con un codice di errore */
    }

    exit(0); /* Termina il processo con successo */
}