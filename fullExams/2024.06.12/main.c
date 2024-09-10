/* File main.c */
/* Standard C = C11 */

#include <fcntl.h>    /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdio.h>    /* Standard I/O: printf, BUFSIZ */
#include <stdlib.h>   /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <string.h>   /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/types.h> /* SYStem TYPES: pid_t */
#include <sys/wait.h>  /* SYStem WAIT: wait */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */

typedef int pipe_t[2]; /* Definizione di un tipo pipe_t come array di 2 interi */

#define PERM 0644

typedef char L[250];

int main(int argc, char **argv) {
    /* -------- Variabili locali ---------- */
    int N; /* numero di file: i processi figli saranno il doppio! */
    /* ATTENZIONE 'N' variabile del testo */
    int pid;         /* variabile per fork */
    pipe_t *pipe_ps; /* array di pipe per la comunicazione dai figli primi della
                        coppia ai figli secondi della coppia */
    int fd;          /* variabile per open */
    L linea;        /* variabile per la linea corrente (pari/dispari) letta dai figli dal proprio file */
    /* ATTENZIONE 'linea' variabile del testo */
    char *FCreato;   /* variabile per nome file da creare da parte dei processi figli primi della coppia */
    int fcreato;     /* variabile per creat */
    /* ATTENZIONE 'fcreato' variabile del testo */
    int nro;        /* variabile per il valore massimo della lunghezza delle linee pari/dispari dei file */
    /* ATTENZIONE 'nro' variabile del testo */
    int status, pidFiglio, ritorno; /* per wait */
    int n, j;                       /* indici per cicli */
    /* ATTENZIONE 'n' variabile del testo */
    int nr, nw; /* per controllo su read/write */
    int nrLinea;

    /* ------------------------------------ */

    /* Controllo sul numero di parametri: N deve essere maggiore o uguale a 1 */
    if (argc < 2) {
        printf("Errore numero parametri, dato che argc=%d\n", argc);
        exit(1);
    }

    /* calcoliamo il numero dei file */
    N = argc - 1;

    ritorno = 0;

    printf("--------------------------\n");
    printf("DEBUG: Sono il padre e devo creare 2*[%d] processi figli\n", N);
    printf("--------------------------\n");

    /* allocazione memoria dinamica per pipe_ps */
    pipe_ps = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipe_ps == NULL) {
        printf("Errore nella malloc per le pipe\n");
        exit(2);
    }

    /* creazione delle pipe */
    for (n = 0; n < N; n++) {
        if (pipe(pipe_ps[n]) != 0) {
            printf("Errore creazione delle pipe\n");
            exit(3);
        }
    }

    /* creazione dei processi figli: ne devono essere creati 2*N */
    for (n = 0; n < 2 * N; n++) {
        pid = fork();
        if (pid < 0) {
            printf("Errore nella fork con indice %d\n", n);
            exit(4);
        } 
        
        if (pid == 0) {
            if (n < N) /* siamo nel codice dei figli primi della coppia */
            {
                printf("--------------------------\n");
                printf("DEBUG: PRIMO DELLA COPPIA-Figlio di indice [%d] e pid=%d, associato al file [%s]\n", 
                        n, getpid(), argv[n + 1]);
                printf("--------------------------\n");

                /* chiudiamo le pipe che non servono */
                /* ogni figlio PRIMO della coppia scrive solo sulla pipe_ps[n] */
                for (j = 0; j < N; j++) {
                    close(pipe_ps[j][0]);
                    if (j != n) {
                        close(pipe_ps[j][1]);
                    }
                }

                /* ogni figlio deve aprire il suo file associato */
                fd = open(argv[n + 1], O_RDONLY);
                if (fd < 0) {
                    printf("Impossibile aprire il file %s\n", argv[n + 1]);
                    exit(-1);
                }

                nro = 0;
                nrLinea = 1;
                while (read(fd, &(linea[nro]), 1)) {
                    if (linea[nro] == '\n') {
                        if (nrLinea % 2 == 1) { /* la linea dispari */
                            /* Invio come prima cosa la lunghezza della linea corrente */
                            nw = write(pipe_ps[n][1], &nro, sizeof(nro));
                            if (nw != sizeof(nro)) {
                                printf("Errore in scrittura su pipe %d\n", n);
                                exit(-1);
                            }

                            /* Invio come seconda cosa la linea stessa */
                            nw = write(pipe_ps[n][1], &linea, nro * sizeof(char));
                            if (nw != nro * sizeof(char)) {
                                printf("Errore in scrittura su pipe %d\n", n);
                                exit(0);
                            }
                            if (ritorno < nro) {
                                ritorno = nro;
                            }
                        }
                        nro = 0;
                        nrLinea++;
                    } else {
                        nro++;
                    }
                }

            } else /* siamo nel codice dei figli secondi della coppia */
            {
                printf("--------------------------\n");
                printf("DEBUG: SECONDO DELLA COPPIA-Figlio di indice [%d] e pid=%d, associato al file [%s]\n", 
                        n, getpid(), argv[n - N + 1]);
                printf("--------------------------\n");

                /* n figli secondi della coppia devono creare il file specificato */

                /* Alloco memoria per il nome del file da creare */
                /* una stringa che deve essere lunga quanto il nome del file associato + 1 char per il '.' 3 char per 'max' e 1 per il terminatore */
                if(!(FCreato = (char*) malloc((strlen(argv[n - N + 1]) + 5) * sizeof(char)))) {
                    printf("Errore: Impossibile allocare memoria per il nome del file da creare!\n");
                    exit(-1);
                }

                /* copiamo il nome del file associato */
                strcpy(FCreato, argv[n - N + 1]);
                /* concateniamo la stringa specificata dal testo */
                strcat(FCreato, ".max");

                /* Creazione file */
                if ((fcreato = creat(FCreato, PERM)) < 0) {
                    printf("Errore in creazione file '%s'\n", FCreato);
                    exit(-1);
                }

                /* chiudiamo le pipe che non servono */
                /* ogni figlio SECONDO della coppia legge solo da pipe_ps[n - N]*/
                for (j = 0; j < N; j++) {
                    close(pipe_ps[j][1]);
                    if (j != n - N) {
                        close(pipe_ps[j][0]);
                    }
                }

                /* Apertura file in lettura */
                if ((fd = open(argv[n - N + 1], O_RDONLY)) < 0) {
                    printf("Errore in apertura file '%s' in lettura\n", argv[n - N + 1]);
                    exit(-1);
                }

                nro = 0;
                nrLinea = 0;
                while (read(fd, &(linea[nro]), 1)) {
                    if (linea[nro] == '\n') {
                        if (nrLinea % 2 == 0) { /* la linea pari */

                            /* leggo la lunghezza della linea dispari passata dal altro processo */
                            nr = read(pipe_ps[n - N][0], &ritorno, sizeof(ritorno));
                            if (nr != sizeof(ritorno)) {
                                printf("Errore in lettura da pipe %d\n", n - N);
                                exit(-1);
                            }

                            /* leggo la linea dispari */
                            L buffer;
                            nr = read(pipe_ps[n - N][0], buffer, ritorno * sizeof(char));
                            if (nr !=  ritorno * sizeof(char)) {
                                printf("Errore in lettura da pipe %d\n", n - N);
                                exit(-1);
                            }

                            /* se la linea dispari ha una lunghezza maggiore o uguale scrivo la linea dispari */
                            if (ritorno >= nro) {
                                nro = ritorno;
                                for (j = 0; j < nro; j++) {
                                    write(fcreato, &buffer[j], 1);
                                }
                                write(fcreato, "\n", 1);
                            } else { /* altrimenti scrivo la linea pari letta */
                                for (j = 0; j < nro; j++) {
                                    write(fcreato, &linea[j], 1);
                                }
                                write(fcreato, "\n", 1);
                                ritorno = nro;
                            }
                        }
                        nro = 0;
                        nrLinea++;
                    } else {
                        nro++;
                    }
                }
            }
            exit(ritorno);
        }
    }

    /*codice del padre*/
    /* chiudiamo tutte le pipe, dato che le usano solo i figli */
    for (n = 0; n < N; n++) {
        close(pipe_ps[n][0]);
        close(pipe_ps[n][1]);
    }

    /* Attesa della terminazione dei figli */
    for(n=0; n< N * 2; n++){
        if ((pidFiglio=wait(&status)) < 0)
        {
            //La wait non ha avuto successo
            printf("Errore in wait\n");
            exit(5);
        }

        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            ritorno = WEXITSTATUS(status);
            printf("Il figlio di pid %d e' ritornato con %d lunghezza max trovata, se 255 problemi!\n", pidFiglio, ritorno);
        } else {
            //Lo status riporta una terminazione anomala
            printf("DEBUG: Il figlio e' terminato in modo anomalo\n");
        }
    }

    exit(0);
}