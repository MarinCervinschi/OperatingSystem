/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <ctype.h> /* per islower e toupper */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc != 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 ...\n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                			/* process identifier per le fork() */
    int N;                  			/* numero di file passati sulla riga di comando (uguale al numero di file) */
    pipe_t *pipedFP;          			/* array dinamico di pipe descriptors per comunicazioni figli-padre  */
    pipe_t *pipedNP;          			/* array dinamico di pipe descriptors per comunicazioni nipoti-padre  */
    int i, j;               			/* indici per i cicli */
    char ch; 			                /* variabile che serve per leggere i caratteri sia da parte dei figli che dei nipoti */
    long int trasformazioni = 0L;	        /* variabile che mantiene il numero delle trasformazioni effettuate sia dai figli che dai nipoti */
    int pidWaitedSon, status, ritorno;	/* per valore di ritorno dei vari processi (figli/nipoti) */
    int fd;              				/* file descriptor */
    
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 1; 

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(pipedFP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione nipote-padre */
    if(!(pipedNP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione nipote-padre!\n");
        exit(3);
    }

    /* Inizializzo l'array delle pipe */
    for(i = 0; i < N; i++) {
        if(pipe(pipedFP[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe per il figlio %d-esimo!\n", i);
            exit(4);
        }
        if(pipe(pipedNP[i]) < 0) {
            printf("Errore: Impossibile inizializzare l'array delle pipe per il nipote %d-esimo!\n", i);
            exit(5);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(i = 0; i < N; i++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", i);
            exit(6);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiudo tutte le pipe di non interesse */
            for(j = 0; j < N; j++) {
                close(pipedFP[j][0]);
                if(i != j)
                    close(pipedFP[j][1]);
            }

            /* Creo il processo nipote */
            if((pid = fork()) < 0) {
                printf("Errore: Impossibile creare il processo nipote!\n");
                exit(-1);
            }

            /* Codice del processo nipote */
            if(pid == 0) {
                /* chiusura della pipe rimasta aperta di comunicazione fra figlio-padre che il nipote non usa */
                close(pipedFP[i][1]);

                /* Chiudo tutte le pipe di non interesse */
                for(j = 0; j < N; j++) {
                    close(pipedNP[j][0]);
                    if(i != j)
                        close(pipedNP[j][1]);
                }

                /*###############grandson operation###################*/

                /* Apro il file in lettura e scrittura */
                if ((fd = open(argv[i + 1], O_RDWR)) < 0) {
                    printf("Errore: Impossibile aprire il file %s in lettura e scrittura!\n", argv[i + 1]);
                    exit(-1);
                }

                /* Leggo il file carattere per carattere */
                while (read(fd, &ch, 1)) {
                    /* controlliamo se abbiamo trovato un carattere alfabetico minuscolo */
                    if (islower(ch)) {
                        /* trasformiamo il carattere in maiuscolo */
                        ch = toupper(ch);
                        /* ci posizioniamo all'inizio del carattere da sovrascrivere */
                        lseek(fd, -1L, SEEK_CUR);
                        /* sovrascriviamo il carattere */
                        write(fd, &ch, 1);
                        /* incrementiamo il contatore delle trasformazioni */
                        trasformazioni++;
                    }
                }

                /* il nipote deve inviare al padre il numero di trasformazioni operate */
                write(pipedNP[i][1], &trasformazioni, sizeof(trasformazioni));

                /* torniamo il valore richiesto dal testo operando una divisione intera per 256 */
				ritorno = trasformazioni / 256;	
                exit(ritorno); /* return del nipote al figlio */
            }

            /* le pipe usate dal nipote vanno chiuse TUTTE */
            for(j = 0; j < N; j++) {
                close(pipedNP[j][0]);
                close(pipedNP[j][1]);
            }

            /*###############son operation###################*/

            /* Anche il figlio apre il file in lettura e scrittura */
            if ((fd = open(argv[i + 1], O_RDWR)) < 0) {
                printf("Errore: Impossibile aprire il file %s in lettura e scrittura!\n", argv[i + 1]);
                exit(-1);
            }

            /* Leggo il file carattere per carattere */
            while (read(fd, &ch, 1)) {
                /* controlliamo se abbiamo trovato un carattere numerico */
                if (isdigit(ch)) {
                    /* trasformiamo il carattere in uno spazio come richiede il testo */
                    ch = ' ';
                    /* ci posizioniamo all'inizio del carattere da sovrascrivere */
                    lseek(fd, -1L, SEEK_CUR);
                    /* sovrascriviamo il carattere */
                    write(fd, &ch, 1);
                    /* incrementiamo il contatore delle trasformazioni */
                    trasformazioni++;
                }
            }

            /* il figlio deve inviare al padre il numero di trasformazioni operate */
            write(pipedFP[i][1], &trasformazioni, sizeof(trasformazioni));

            /* il figlio deve aspettare il nipote e stampare il suo pid con il valore ritornato (come richiesto dal testo) */
            if ((pidWaitedSon = wait(&status)) < 0) {
                printf("Errore in wait per il nipote %d-esimo con pid=%d!\n", i, getpid());
            }
            if ((status & 0xFF) != 0)
                printf("Nipote con pid %d terminato in modo anomalo\n", pidWaitedSon);
            else {
                ritorno = (int)((status >> 8) & 0xFF);
                printf("--------------------------\n");
                printf("DEBUG: Il Nipote %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", i, pidWaitedSon, ritorno);
                printf("--------------------------\n");
            }

            /* torniamo il valore richiesto dal testo operando una divisione intera per 256 */
			ritorno = trasformazioni / 256;
            exit(ritorno); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Chiudo tutte le pipe di non interesse */
    for(i = 0; i < N; i++) {
        close(pipedFP[i][1]);
        close(pipedNP[i][1]);
    }
    
    /*###############father operation###################*/

    /* Il padre recupera le informazioni dai figli e dai nipoti in ordine di indice */
	for (i=0; i < N; i++)
	{
		read(pipedFP[i][0], &trasformazioni, sizeof(trasformazioni));
		printf("Il figlio di indice %d ha operato %ld trasformazioni di caratteri numerici in carattere spazio sul file %s\n", i, trasformazioni, argv[i+1]);
		read(pipedNP[i][0], &trasformazioni, sizeof(trasformazioni));
		printf("Il nipote di indice %d ha operato %ld trasformazioni di caratteri minuscoli in MAIUSCOLI sullo stesso file %s\n", i, trasformazioni, argv[i+1]);
	}

    /* Il padre aspetta i figli salvando lo status */
    for (int i = 0; i < N; i++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", i);
            exit(7);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", i, pidWaitedSon);
        else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", i, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}