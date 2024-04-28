# EX 13
Scrivere un programma in C **selezionaLinea.c** che deve essere invocato esattamente con **2 parametri**:
- il primo deve essere considerato il **nome di un file F**;
- il secondo un **numero intero n strettamente positivo**.

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), si visualizzi su standard output la linea n-
esima del file F (si può supporre la lunghezza massima di ogni linea del file pari a 255 caratteri) se esiste, oppure si
riporti che tale linea non esiste.

**N.B.** La lettura deve avvenire, anche in questo caso, un carattere alla volta, dato che si deve cercare il carattere '\n',
ma in questo caso i caratteri devono essere salvati in un buffer di opportuna lunghezza (256 perché si considera utile
inserire anche il terminatore di stringa quando si sarà identificata la linea giusta); 

Il modo più furbo per farlo è questo:
while (read (fd, &(buffer[j]), 1) != 0) supponendo che j sia l’indice, inizializzato a 0, che scorre
gli elementi del buffer. Inoltre, anche in questo caso, il contatore del numero di linee lo si faccia partire da 1 e quindi
quando i caratteri ‘\n’ incontrati saranno arrivati a n si potrà concludere il ciclo di lettura, ad esempio con un break,
dopo aver chiaramente stampato la linea cercata (N.B. per usare la printf, bisogna trasformare la linea in una stringa!)
e aver cambiato valore alla variabile trovata (si veda dopo); se invece non viene trovata la linea, basandosi
appunto sul valore della variabile trovata, si deve dare una indicazione all’utente in tal senso! 

Si verifichi il funzionamento.