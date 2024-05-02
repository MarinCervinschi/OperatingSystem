/* File padreFigliConConteggioOccorrenze.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <string.h> /* STRING: strlen, strcpy, strcmp */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc < 4) {
        printf("Error: numero di parametri '%d' errato\n", argc);
        exit(1);
    }
    
    for (int i = 1; i < argc - 1; i++) {
        /* controllo che gli N parametri siano file */
        
        int fd1; /* variabile per valore di ritorno open */
        if ((fd1 = open(argv[i], O_RDONLY)) < 0) {
            printf("Errore in apertura file per '%s' -> FILE NON ESISTE\n", argv[i]);
            exit(2);
        }
        close(fd1);
    }

    /* controllo che l'ultimo parametro sia un singolo carattere */
    if (argv[argc - 1][1] != '\0') {
        printf("Error: %s non singolo carattere\n", argv[argc - 1]);
        exit(3);
    }
}

//Ritorna il numero di occorrenze del carattere Cx nel file F
long int contaOccorrenzeCarattere(const char *F, char Cx){
    /* Apertura file */
    int fd = open(F, O_RDONLY);
    int n;

    char buffer;
    long int occorrenze = 0;
    /* Lettura file carattere per carattere */
    while((n = read(fd, &buffer, 1)) > 0){
        if(buffer == Cx){
            occorrenze++;
        }
    }
    close(fd);
    return occorrenze;
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    char Ch = argv[argc - 1][0];
    int N = argc - 2;

    int pid;
    int pidPadre = getpid();
    printf("La pid del padre e': %d\n", pidPadre);
    printf("Queasto processo deve generare %d figli\n", N);
    
    pid_t *pidDeiFigli = malloc(N*sizeof(pid_t));
    
    if(pidDeiFigli == NULL) {
        printf("Errore nell'allocazione della memoria\n");
        exit(4);
    }
    
    /* Per la creazione di N figli */
    for(int i = 0; i < N; i++) {
        if ((pid = fork()) < 0) {
            /* Fork fallita */
            printf("Errore in fork\n");
            free(pidDeiFigli);
            exit(5);
        }
        
        if (pid == 0) {
            /* CODICE DEL FIGLIO*/
    
            printf("Figlio, pid: %d, indice %d\n", getpid(), i);
            exit(contaOccorrenzeCarattere(argv[i + 1], Ch));
    
            /*FINE CODICE DEL FIGLIO*/
        }
        printf("Generato figlio con PID = %d\n", pid);
        pidDeiFigli[i] = pid;
    }
    
    /* padre */
    pid_t pidFiglio;
    int status, ritorno;
    /* Il padre aspetta i figli salvando lo status */
    for(int i = 0; i < N; i++) {
        if ((pidFiglio = wait(&status)) < 0) {
            /* La wait non ha avuto successo */
            printf("Errore in wait\n");
            free(pidDeiFigli);
            exit(6);
        }
    
        int posizione = 0;
        for(int j = 0; j < N; j++) {
            if(pidDeiFigli[j] == pidFiglio){
                posizione = j;
                break;
            }
        }

        /* Posizione partendo da 0 */
        printf("Terminato figlio con PID = %d, creato per %d-esimo\n", pidFiglio, posizione);
        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            ritorno = WEXITSTATUS(status);
            printf("Il file %s contiene %d caratteri %c\n", argv[i + 1], ritorno, Ch);
        } else {
            /* Lo status riporta una terminazione anomala */
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    }
    /* Libero la memoria dove ho salvato i PID dei figli */
    free(pidDeiFigli);


    exit(0);
}