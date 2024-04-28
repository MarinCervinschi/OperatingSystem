# EX 14
Scrivere un programma in C **selezionaLunghezzaLinea.c** che deve essere invocato con esattamente **2 parametri**: 
- il primo deve essere considerato il **nome di un file F**;
- il secondo un **numero intero n strettamente positivo**.

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), si visualizzino su
standard output tutte le linee del file F la cui lunghezza, compreso il terminatore di linea, sia esattamente uguale a n
(insieme con la indicazione del numero d’ordine di tale linea) oppure si riporti che non esiste alcuna linea con
lunghezza uguale a n.

**N.B.** La soluzione è molto simile al programma selezionaLinea.c, ma in questo caso non si deve prevedere un
break nel ciclo di lettura, dato che potremmo avere più linee con la stessa lunghezza richiesta; si faccia attenzione che
se si deve contare anche il terminatore di linea, allora una volta individuato il carattere ‘\n’ in buffer[j] il controllo
sulla lunghezza della linea dovrà essere n == j+1. 

Si verifichi il funzionamento.