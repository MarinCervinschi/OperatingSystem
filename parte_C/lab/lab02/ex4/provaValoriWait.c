/* File provaValoriWait.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */


int main(int argc, char **argv) {

    int pid; 				            /* pid per fork */
    int pidFiglio, status, ritorno;     /* per wait padre */

	if ((pid = fork()) < 0) { 	/* fork fallita */
		printf("Errore in fork\n");
		exit(1);
	}

	if (pid == 0) { 	
        /* codice del figlio */
		printf("Esecuzione del figlio\n");
		int valore;
		printf("Inserisci un numero 0 < valore <= 255\n");
		
		if (scanf("%d", &valore) != 1) {
			printf("Errore nella lettura\n");
		}

		if (valore > 255 || valore < 0) {
			printf("Valore che hai inserito verra' troncato\n");
		} else {
			printf("Valore NON verra' troncato\n");
		}

		exit(valore);

		/* fine codece del figlio */
	}

	/* padre */
	printf("Generato figlio con PID = %d\n", pid);

	/* il padre aspetta il figlio in questo caso interessandosi del valore della exit del figlio */
	if ((pidFiglio = wait(&status)) < 0) {
		printf("Errore in wait\n");
		exit(2);
	}

	if (pid == pidFiglio) {
        printf("Terminato figlio con PID = %d\n", pidFiglio);

    } else {      
        /* problemi */
        printf("Il pid della wait non corrisponde al pid della fork!\n");
        exit(3);
    }

	if ((status & 0xFF) != 0) {
        printf("Figlio terminato in modo involontario (cioe' anomalo)\n");
    } else {
        /* selezione del byte "alto" */
        ritorno = status >> 8;
        ritorno &= 0xFF;
    	printf("Per il figlio %d lo stato di EXIT e` %d\n", pid, ritorno);
    }

	exit(0);
}