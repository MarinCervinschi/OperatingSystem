/* File 12Set18.c */
/* Standard C = C11 */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: memset */
#include <sys/wait.h> /* SYStem WAIT: wait */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

int main(int argc, char const **argv) {
    /* controllo numero parametri */
    if (argc < 3) {
        printf("Error: numero parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 .. fileN\n", argv[0]);
        exit(1);
    }

    /* -------- Variabili locali ---------- */
    int pid;                /* process identifier per le fork() */
    pipe_t *pipedFP;        /* array dinamico di pipe descriptors per comunicazioni figli-padre */
    pipe_t *pipedPF;        /* array dinamico di pipe descriptors per comunicazioni padre-figli */
    int n, j;               /* indici per i cicli */
    int pidWaitedSon, status, ritorno;/* per valore di ritorno dei vari processi (figli/nipoti) */
    int N;                  /* numero di processi figli: deve essere una variabile globale perche' deve essere usata dalla funzione finitof */
    int fd;                 /* file descriptor */
    char linea[250];        /* array di caratteri per memorizzare la linea, supponendo una lunghezza massima di ogni linea di 250 caratteri compreso il terminatore di linea */
    char car;               /* variabile usata dal padre per leggere gli ultimi caratteri delle linee inviati dai figli */
    char chMin;             /* variabile usata dal padre per tenere traccia del carattere di codice ASCII massimo */
    char chControllo;       /* variabile per inviare indicazione ai figli */
    int indice;             /* variabile usata dal padre per tenere traccia dell'indice del figlio che ha calcolato il massimo */
    int stampe;             /* numero di stampe fatte dai figli che va ritornato al padre */
    int nr, nw;             /* per controlli read e write su/da pipe */
    int lastj;		        /* per salvare il valore di j se e' ultima linea letta dal figlio */
    /* ------------------------------------ */

    /* Salvo il numero dei file in una variabile */
    N = argc - 1; 

    /* Alloco memoria per l'array delle pipe per la comunicazione figlio-padre */
    if(!(pipedFP = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione figlio-padre!\n");
        exit(2);
    }

    /* Alloco memoria per l'array delle pipe per la comunicazione padre-figlio */
    if(!(pipedPF = (pipe_t*) malloc(N * sizeof(pipe_t)))) {
        printf("Errore: Impossibile allocare memoria per l'array delle pipe per la comunicazione padre-figlio!\n");
        exit(3);
    }

    /* Creazione delle N pipe figli-padre e delle N pipe padre-figli */
    for(n = 0; n < N; n++) {
        if(pipe(pipedFP[n]) < 0) {
            printf("Errore: Impossibile creare la pipe figlio-padre %d-esima!\n", n);
            exit(4);
        }
        if(pipe(pipedPF[n]) < 0) {
            printf("Errore: Impossibile creare la pipe padre-figlio %d-esima!\n", n);
            exit(5);
        }
    }

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre con pid=%d e sto per creare [%d] figli!\n", getpid(), N);
    printf("--------------------------\n");

    /* Creo N processi figli */
    for(n = 0; n < N; n++) {

        if((pid = fork()) < 0) {
            printf("Errore: Impossibile creare il processo figlio %d-esimo!\n", n);
            exit(6);
        }

        /* Codice del processo figlio */
        if(pid == 0) {

            /* Chiusura delle pipe non usate nella comunicazione con il padre */
            for (j = 0; j < N; j++) {
                close(pipedFP[j][0]);
                close(pipedPF[j][1]);
                if (n != j) {
                    close(pipedFP[j][1]);
                    close(pipedPF[j][0]);
                }
            }

            /* Apro il file in sola lettura */
            if((fd = open(argv[n + 1], O_RDONLY)) < 0) {
                printf("Errore: Impossibile aprire il file %s in sola lettura!\n", argv[n + 1]);
                exit(-1);
            }

            /* adesso il figlio legge dal file una linea alla volta */
            j=0;
            /* inizializziamo le stampe a 0 */
            stampe = 0;

            while(read(fd, &(linea[j]), 1)){
                if(linea[j] == '\n'){
                    lastj = j; /* salviamo l'ultimo indice */
                    j = 0; /* azzeriamo l'indice per le prossime linee */
                } else {
                    j++; /* incrementiamo l'indice per la prossima lettura */
                }
            }
            /* arrivati qui in linea abbiamo l'ultima linea del file e in lastj l'ultimo indice di tale linea */
	 	    /* inviamo il primo carattere (escluso il terminatore di linea) al padre */
            nw = write(pipedFP[n][1], &linea[0], 1);
            if(nw != 1){
                printf("Errore: impossibile scrivere il carattere %c sulla pipe figlio-padre %d-esima\n", linea[j - 1], n);
                exit(-1);
            }

            /* aspettiamo dal risposta da padre se stampare o meno */
            nr = read(pipedPF[n][0], &chControllo, 1);
            if(nr != 1){
                printf("Errore: impossibile leggere il carattere di controllo dalla pipe padre-figlio %d-esima\n", n);
                exit(-1);
            }

            if (chControllo == 'S') {
                
                /* stampiamo la linea */
                linea[lastj + 1] = '\0'; /* mettiamo il terminatore di stringa */
                printf("Sono il figlio di indice %d e pid %d e ho trovato l'ultima linea con primo carattere '%c' con codice ASCII minore degli altri nel file %s. Ecco la linea:\n%s", n, getpid(), linea[0], argv[n+1], linea);
                stampe++; /* incrementiamo il contatore delle stampe */
            }

            exit(stampe); /* return del figlio al padre */
        }
    }

    /* Codice del processo padre */

    /* Il padre chiude n lati delle pipe che non usa */
    for (n = 0; n < N; n++) {
        close(pipedFP[n][1]);
        close(pipedPF[n][0]);
    }

    chMin = 127; /* inizializziamo il carattere minimo a 500 un valore sicuramente maggiore di tutti i caratteri ASCII */
    for (n = 0; n < N; n++) {
        /* tentiamo di leggere il carattere dal figlio i-esimo: contestualmente viene aggiornato il valore del corrispondente elemento dell'array finito */
        nr = read(pipedFP[n][0], &car, 1);  /* nel caso la read torni un valore diverso da 1, il corrispondente valore di finito viene settato a 1 dato che la condizione e' vera! */
        if (nr != 1) {
            printf("PADRE: errore in lettura da pipe figlio-padre %d-esima\n", n);
            exit(7);
        }

        if (car < chMin) {
            /* dobbiamo aggiornare il massimo */
            chMin = car;
            /* debbiamo tenere conto dell'indice del processo che ha inviato il massimo */
            indice = n;
        }   
    }

    /* bisogna mandare ai figli l'indicazione giusta (S per scrivere, N per NON scrivere) */
    for (n = 0; n < N; n++) {
        if (n == indice) /* figlio che deve scrivere */
            chControllo = 'S';
        else chControllo = 'N';

        nw = write(pipedPF[n][1], &chControllo, 1); 
        if (nw != 1) {
            printf("PADRE non e' riuscito ad inviare nulla al figlio di indice %d \n", n);
        }
    }

    /* Il padre aspetta i figli salvando lo status */
    for (n = 0; n < N; n++) {
        if ((pidWaitedSon = wait(&status)) < 0) {
            printf("Errore in wait per il figlio %d-esimo!\n", n);
            exit(5);
        }
        if ((status & 0xFF) != 0)
            printf("Figlio %d-esimo con pid %d terminato in modo anomalo\n", n, pidWaitedSon);
        else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("--------------------------\n");
            printf("DEBUG: Il figlio %d-esimo con pid=%d ha ritornato %d (se 255 problemi)\n", n, pidWaitedSon, ritorno);
            printf("--------------------------\n");
        }
    }

    exit(0); /* return del padre al sistema */
}