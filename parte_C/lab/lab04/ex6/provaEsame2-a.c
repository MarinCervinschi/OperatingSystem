/* file provaEsame2-a.c */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* versione con N pipe */

/* tipo che definisce una pipe */
typedef int pipe_t[2];

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc < 4) {
        printf("Error: numero di parametri '%d' errato\n", argc - 1);
        printf("Usage: %s <file> <char> <char> ...\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int N = argc - 2;
    long int count;

    /* controllo dei N caratteri*/
    for (int i = 2; i < argc; i++) {
        if (strlen(argv[i]) != 1) {
            printf("Error: il parametro %d non e' un carattere\n", i);
            exit(2);
        }
    }

    /* allocazione di N pipe */
    pipe_t *pipes = (pipe_t *)malloc(N * sizeof(pipe_t));
    if (pipes == NULL) {
        printf("##########################################\n");
        printf("Error: malloc failed nel allocare le pipe\n");
        printf("##########################################\n");
        exit(3);
    }
    
    /* creazione delle N pipe */
    for (int i = 0; i < N; i++) {
        if (pipe(pipes[i]) < 0) {
            printf("###################################################\n");
            printf("Error: pipe failed nella creazione della pipe %d\n", i);
            printf("###################################################\n");
            exit(4);
        }
    }

    printf("---------------------------------------------------------------------------\n");
    printf("DEBUG: Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);
    printf("---------------------------------------------------------------------------\n");

    int pid;
    /* generazione dei N figli */
    for (int i = 0; i < N; i++) {
        if ((pid = fork()) < 0) {
            printf("###################################################\n");
            printf("Error: fork failed nella generazione del figlio %d\n", i);
            printf("###################################################\n");
            exit(5);
        }

        if (pid == 0) {
            /* codice del figlio */
            printf("---------------------------------------------------------------------------\n");
            printf("DEBUG: Sono il figlio %d con pid %d -> sono associato al carattere '%c'\n", i, getpid(), argv[i + 2][0]);
            printf("---------------------------------------------------------------------------\n");

            /* chiusura delle pipe non utilizzate */
            for (int j = 0; j < N; j++) {
                close(pipes[j][0]);
                if (j != i) {
                    close(pipes[j][1]);
                }
            }

            /* apertura del file */
            int fd;
            if ((fd = open(argv[1], O_RDONLY)) < 0) {
                printf("###################################################\n");
                printf("Error: open failed nell'apertura del file %s\n", argv[1]);
                printf("###################################################\n");
                exit(-1);
            }

            /* lettura del file */
            char c;
            count = 0;
            while (read(fd, &c, 1) > 0) {
                if (c == argv[i + 2][0]) {
                    count++;
                }
            }

            /* scrittura del risultato sulla pipe */
            write(pipes[i][1], &count, sizeof(count));

            exit(argv[i + 2][0]); /* ritorno il carattere associato al figlio */
        }
    }

    /* codice del padre */
    /* chiusura delle pipe non utilizzate */
    for (int i = 0; i < N; i++) {
        close(pipes[i][1]);
    }

    /* lettura dei risultati dai figli */
    for (int i = 0; i < N; i++) {
        if (read(pipes[i][0], &count, sizeof(count)) > 0) {
            printf("---------------------------------------------------------------------------\n");
            printf("DEBUG: Sono il padre con pid %d -> il figlio %d ha trovato %ld occorrenze del carattere '%c'\n", getpid(), i, count, argv[i + 2][0]);
            printf("---------------------------------------------------------------------------\n");            
        }
    }  

    /* attesa dei figli */
    int pidFiglio, status;
    for (int i = 0; i < N; i++) {
        pidFiglio = wait(&status);
        if (pidFiglio < 0) {
            printf("###################################################\n");
            printf("Error: wait failed nell'attesa del figlio %d\n", i);
            printf("###################################################\n");
            exit(6);
        }

        if (WIFEXITED(status)) {
            printf("---------------------------------------------------------------------------\n");
            printf("DEBUG: Sono il padre con pid %d -> il figlio %d con pid %d ha ritornato %c\n", getpid(), i, pidFiglio, WEXITSTATUS(status));
            printf("---------------------------------------------------------------------------\n");
        } else {
            printf("---------------------------------------------------------------------------\n");
            printf("DEBUG: Sono il padre con pid %d -> il figlio %d con pid %d non e' terminato correttamente\n", getpid(), i, pidFiglio);
            printf("---------------------------------------------------------------------------\n");
        }
    }

    exit(0);
}