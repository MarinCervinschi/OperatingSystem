# EX 1
Con un editor, scrivere un programma in C **padreFiglioConStatus.c** che per prima cosa deve
riportare su standard output il pid del processo corrente (processo padre) e poi deve creare un processo
figlio: ricordarsi che il padre deve controllare il valore di ritorno della fork per assicurarsi che la creazione
sia andata a buon fine. 

Il processo figlio deve riportare su standard output il proprio pid e il pid del
processo padre. Quindi, il processo figlio deve generare, in modo random, un numero intero compreso
fra 0 e 99. Al termine, il processo figlio deve ritornare al padre il valore random generato (sicuramente
compreso fra 0 e 99) e il padre deve riportare su standard output il PID del figlio e il valore ritornato: 

**N.B.** ricordarsi che il padre deve controllare sempre il valore di ritorno della wait e l’eventuale terminazione
anormale del figlio!

**OSSERVAZIONE**: per generare numeri random usare quanto segue:
- a) Chiamata alla funzione di libreria srand per inizializzare il seme (da fare, ad esempio, nel padre e che
richiede di aggiungere un ulteriore include rispetto ai soliti):
```c
#include <time.h>
srand(time(NULL));
```
- b) Funzione che calcola un numero random compreso fra 0 e n-1 (da chiamare nel figlio):
```c
#include <stdlib.h>
int mia_random(int n) {
    int casuale;
    casuale = rand() % n;
    return casuale;
}
```
