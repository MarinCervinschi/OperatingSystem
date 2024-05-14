/* File pipe-Generico1.c */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#define MSGSIZE 5 


int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Numero dei parametri errato %d: ci vuole un singolo parametro\n", argc);
        exit(1);
    }

    int piped[2], L;
    char mess[MSGSIZE];

    if (pipe(piped) < 0) {
        printf("Errore creazione pipe\n");
        exit(2);
    }

    int pid;
    if ((pid = fork()) < 0) {
        printf("Errore creazione figlio\n");
        exit(3);
    }

    if (pid == 0) {
        int fd;

        close(piped[0]);

        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            printf("Errore in apertura file %s\n", argv[1]);
            exit(-1);
        }

        printf("------------------------------------------------------------\n");
        printf("DEBUG-Figlio %d sta per iniziare a scrivere una serie di messaggi, ognuno di lunghezza %d, sulla pipe dopo averli letti dal file passato come parametro\n", getpid(), MSGSIZE);
        printf("------------------------------------------------------------\n");
        int j = 0;
        L = 0; /* valore iniziale dell'indice */
        while (read(fd, (&mess[L]), 1)) {
            if (mess[L] == '\n') {	
 				/* il padre ha concordato con il figlio che gli mandera' solo stringhe e quindi dobbiamo sostituire il terminatore di linea con il terminatore di stringa */
    			mess[L] = '\0';
 				L++; /* incrementiamo L per tenere conto anche del terminatore di linea */
      			/* comunichiamo L al processo padre */
      			write(piped[1], &L, sizeof(L));
      			/* comunichiamo la stringa corrispondente alla linea al processo padre */
      			write(piped[1], mess, L);
                L = 0;  	/* azzeriamo l'indice per la prossima linea */
                j++;    /* incrementiamo il contatore */
        	
            } else L++;	/* se non siamo a fine linea, incrementiamo l'indice */
        }
        printf("-------------------------------------------------------------\n");
        printf("DEBUG-Figlio %d scritto %d messaggi sulla pipe\n", getpid(), j);
        printf("-------------------------------------------------------------\n");
        exit(j);
    }

    printf("--------------------------------------------------------------------------\n");
    printf("DEBUG-Padre %d sta per iniziare a leggere i messaggi dalla pipe\n", getpid());
    printf("--------------------------------------------------------------------------\n");
    close(piped[1]);

    int j = 0;
	while (read(piped[0], &L, sizeof(L))) { 	
		/* ricevuta la lunghezza, il padre puo' andare a leggere la linea/stringa */
		read(piped[0], mess, L);
        printf("%d: %s\n", j, mess);
        j++;
	}

    printf("Padre %d ha letto %d messaggi dalla pipe\n", getpid(), j);

    int pidFiglio, status, ritorno;
    pidFiglio = wait(&status);
    if (pidFiglio < 0) {
        printf("Errore wait\n");
        exit(4);
    }
    
    if ((status & 0xFF) != 0) {
        printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        exit(5);
    } else {
        ritorno = (int)((status >> 8) & 0xFF);
        printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);
    }

    exit(0);
}