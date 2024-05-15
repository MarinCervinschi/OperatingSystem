#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

typedef struct {
    char c;
    long int n;
} tipoS;

void check_args(int argc, char *argv[], int N);
void create_pipe(int p[]);
void create_children(int N, char *argv[], int p[]);
void read_from_pipe(int p[], char *argv[]);
void wait_for_children(int N);

int main(int argc, char *argv[]) {
    int N = argc - 2;
    int p[2];

    check_args(argc, argv, N);
    create_pipe(p);
    create_children(N, argv, p);
    read_from_pipe(p, argv);
    wait_for_children(N);

    exit(0);
}

void check_args(int argc, char *argv[], int N) {
    if (argc < 4) {
        printf("Numero dei parametri errato %d: ci vogliono almeno tre parametri (il nome di un file e almeno due caratteri)\n", argc);
        exit(1);
    }

    for (int i = 0; i < N; i++) {
        if (strlen(argv[i + 2]) != 1) {
            printf("Errore nella stringa %s che non e' un singolo carattere\n", argv[i + 2]);
            exit(2);
        }
    }
}

void create_pipe(int p[]) {
    if (pipe(p) < 0) {
        printf("Errore nella creazione della pipe\n");
        exit(3);
    }
}


void child_process(int i, char *argv[], int p[]) {
    printf("DEBUG-Figlio %d con pid %d: sono associato al carattere %c\n", i, getpid(), argv[i + 2][0]);

    close(p[0]);

    int fdr = open(argv[1], O_RDONLY);
    if (fdr < 0) {
        printf("Errore nella apertura del file %s\n", argv[1]);
        exit(-1);
    }

    tipoS msg;
    msg.c = argv[i + 2][0];
    msg.n = 0L;

    char c;
    while (read(fdr, &c, 1) > 0) {
        if (c == argv[i + 2][0]) {
            msg.n++;
        }
    }

    write(p[1], &msg, sizeof(msg));
    exit(argv[i + 2][0]);
}

void create_children(int N, char *argv[], int p[]) {
    printf("DEBUG-Sono il processo padre con pid %d e sto per generare %d figli\n", getpid(), N);

    for (int i = 0; i < N; i++) {
        int pid = fork();

        if (pid < 0) {
            printf("Errore nella fork\n");
            exit(4);
        }

        if (pid == 0) {
            child_process(i, argv, p);
        }
    }

    close(p[1]);
}

void read_from_pipe(int p[], char *argv[]) {
    tipoS msg;
    while (read(p[0], &msg, sizeof(msg)) > 0) {
        printf("%ld occorrenze del carattere %c nel file %s\n", msg.n, msg.c, argv[1]);
    }
}

void wait_for_children(int N) {
    for (int i = 0; i < N; i++) {
        int pidFiglio, status, ritorno;

        if ((pidFiglio = wait(&status)) < 0) {
            printf("Errore wait\n");
            exit(5);
        }

        if ((status & 0xFF) != 0) {
            printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
        } else {
            ritorno = (int)((status >> 8) & 0xFF);
            printf("Il figlio con pid=%d ha ritornato %c (in decimale %d, se 255 problemi!)\n", pidFiglio, ritorno, ritorno);
        }
    }
}