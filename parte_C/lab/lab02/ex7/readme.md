# EX 7
Scrivere un programma in C **padreFigliConConteggioOccorrenze.c** che deve prevedere
un numero variabile N+1 di parametri: i primi N (con N maggiore o uguale a 2, da controllare) che
rappresentano N nomi di file (F1, F2. ... FN), mentre l’ultimo rappresenta un singolo carattere Cx (da
controllare). 

Dopo aver fatto tutti i controlli (quelli indicati), il processo padre deve generare N processi
figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f = i+1).
Ogni processo figlio Pi deve leggere dal file associato contando le occorrenze del carattere Cx.
Al termine, ogni processo figlio Pi deve ritornare al padre il numero di occorrenze (supposto minore di
255) e il padre deve stampare su standard output il pid di ogni figlio e il valore ritornato.

**SUGGERIMENTO PER CODICE FIGLI:** poiché l’indice dei figli varia da 0 a N-1, quando ogni figlio dovrà
identificare il file che deve essere aperto, si dovrà usare l’indice del figlio + 1 per selezionare il giusto nome
del file da argv. In questo caso, possiamo delegare ai singoli figli il controllo che i singoli parametri
(escludendo l’ultimo) siano nomi di file! 

**ATTENZIONE:** in caso di errore nella open, il figlio deve tornare al
padre un valore che faccia capire al padre che il figlio è incorso in un errore; considerando che la specifica
indica che il numero di occorrenze può essere supposto minore di 255, il valore tornato dai figli se la open
fallisce può essere -1 che verrà interpretato dal padre come 255! Quindi ad esempio la stampa del padre
può essere variata, rispetto a quanto riportato sopra, nel seguente modo:
```c
printf("Il figlio con pid=%d ha ritornato %d (se 255 problemi!)\n", pidFiglio, ritorno);
```