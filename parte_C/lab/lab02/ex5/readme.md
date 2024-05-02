# EX 5
Con un editor, scrivere un programma in C **padreFigliMultipli.c** che deve essere invocato
esattamente con 1 parametro che deve essere considerato un numero intero N strettamente positivo e
strettamente minore di 255. 

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri, sul loro
‘tipo’ e vincoli sopra indicati), per prima cosa il programma deve riportare su standard output il pid del
processo corrente (processo padre) insieme con il numero N. Quindi, il processo padre deve generare N
processi figli (P0, P1, … PN-1, indicati nel seguito Pi). Ognuno di tali figli Pi deve riportare su standard
output il proprio pid insieme con il proprio indice d’ordine (i).

Al termine, ogni processo figlio Pi deve ritornare al padre il proprio indice d’ordine (sicuramente
strettamente minore di 255) e il padre deve stampare su standard output il pid di ogni figlio e il valore
ritornato.

**SUGGERIMENTO PER LA CREAZIONE DEGLI N FIGLI DA PARTE DEL PADRE:**
```c
int N; /* numero di figli */
int pid; /* pid per fork */
int i; /* indice per i figli */
/* creazione figli */
for (i = 0; i < N; i++) {
    if ((pid=fork()) < 0) { 
        <stampa e uscita> 
    }
    if (pid == 0) { 
        /* codice figlio */
        <istruzioni specifiche del figlio>
        exit(<VALORE>);
    }
} /* fine for */
```
**OSSERVAZIONE IMPORTANTISSIMA:** fare attenzione che nel codice dei figli ci sia la presenza di una
invocazione alla primitiva exit per fare in modo che ogni processo figlio termini e NON esegua il ciclo for,
che invece deve essere eseguito solo dal padre!

**SUGGERIMENTO PER L’ATTESA DEGLI N FIGLI DA PARTE DEL PADRE:**
```c
int pidFiglio, status, ritorno; /* per wait e valore di ritorno figli */
for (i = 0; i < N; i++) {
    pidFiglio = wait(&status);
    if (pidFiglio < 0) { 
        <stampa e uscita> 
    }
    if ((status & 0xFF) != 0) {
        printf("Figlio con pid %d terminato in modo anomalo\n", pidFiglio);
    } else {
        ritorno=(int)((status >> 8) & 0xFF);
        printf("Il figlio con pid=%d ha ritornato %d\n", pidFiglio, ritorno);
    }
}
```
**N.B. Volendo dopo la wait si possono usare le MACRO apposite!**
- **ALTRA OSSERVAZIONE IMPORTANTISSIMA:** fare attenzione che l’ordine con cui terminano i processi figli
è completamente NON deterministico e quindi NON si potrà mai supporre con il codice mostrato
precedentemente di poter riportare l’indice dei figli che via via terminano. Per avere questa informazione,
considerare l’esercizio seguente!