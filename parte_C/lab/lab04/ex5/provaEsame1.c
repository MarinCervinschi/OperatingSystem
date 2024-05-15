/* File provaEsame1.c */

#include <stdio.h> /* Standard I/O: printf, BUFSIZ */
#include <fcntl.h> /* File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR */
#include <stdlib.h> /* STanDard LIBrary: exit, malloc, calloc, free, atoi */
#include <unistd.h> /* UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END */
#include <sys/stat.h> /* SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG */
#include <sys/wait.h> /* SYStem WAIT: wait */
#include <ctype.h> /* ISoPeration: isalpha, isdigit */

/* funzione per controllare la validita' dei parametri */
void checkParams(int argc, char **argv) {
    /* controllo il numero di parametri */
    if (argc < 3) {
        printf("Error: numero di parametri '%d' errato\n", argc - 1);
        printf("Uso: %s file1 file2 ... fileN\n", argv[0]);
        exit(1);
    }
}

int main(int argc, char **argv) {
    checkParams(argc, argv);

    int N = argc - 1;
    char ch0, ch1;

    int pid;
    int p[2][2];
    if (pipe(p[0]) < 0) {
        printf("Error: pipe per p[0]\n");
        exit(2);
    }

    if (pipe(p[1]) < 0) {
        printf("Error: pipe per p[1]\n");
        exit(3);
    }

    printf("\n-----------------------------------------------------\n");
    printf("DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);
    printf("-----------------------------------------------------\n");

    for (int Pi = 0; Pi < N; Pi++) {
        if ((pid = fork()) < 0) {
            printf("Error: fork per il figlio %d-esimo\n", Pi);
            exit(4);
        }

        int f = Pi + 1;
        if (pid == 0) {
            printf("Sono il figlio %d con pid %d\n", Pi, getpid());

            /* chiusura lati pipe non utilizzati */
            close(p[0][0]);
            close(p[1][0]);
      		close(p[Pi % 2][1]); 
      			
            int fd = open(argv[f], O_RDONLY);
            if (fd < 0) {
                printf("##################################################\n");
                printf("Error: open del file '%s'\n", argv[f]);
                printf("##################################################\n");
                exit(-1);
            }

            char ch;
            while(read(fd, &ch, 1) > 0) {
                if ((Pi % 2 == 0) && isalpha(ch)) {
                    write(p[1][1], &ch, 1);
                } else if ((Pi % 2 == 1) && isdigit(ch)) {
                    write(p[0][1], &ch, 1);
                }
      		}

      		exit(ch);
        }
    }

    /* chiusura lati pipe non utilizzati */
    close(p[0][1]);
    close(p[1][1]);

    printf("I caratteri inviati dai figli sono:\n");
    int nr0 = read(p[0][0], &ch0, 1);
    int nr1 = read(p[1][0], &ch1, 1);

    int tot = 0;
    while ((nr0 != 0) || (nr1 != 0)) {
        tot += nr0 + nr1;

    	write(1, &ch1, nr1);
    	write(1, &ch0, nr0);
    	nr0 = read(p[0][0], &ch0, 1);
    	nr1 = read(p[1][0], &ch1, 1);
    }

    printf("\nI figli hanno inviato %d caratteri\n", tot);

    /*  attesa terminazione figli */
    int pidFiglio, status;
    for (int i = 0; i < N; i++) {
        pidFiglio = wait(&status);
        if (pidFiglio < 0) {
            printf("Error: wait per il figlio %d-esimo\n", i);
            exit(5);
        }

        if (WIFEXITED(status)) {
            printf("Il figlio %d-esimo ha ritornato %d\n", i, WEXITSTATUS(status));
        } else {
            printf("Il figlio %d-esimo non e' terminato correttamente\n", i);
        }
    }
    
    exit(0);
}