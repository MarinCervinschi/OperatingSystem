# EX 5
Con un editor, scrivere un programma in C **contaOccorrenze.c** che deve essere invocato esattamente con **2 parametri**: 
- il primo deve essere considerato il nome di un file (F);
- il secondo deve essere considerato un singolo carattere Cx. 

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), si visualizzi su
standard output il nome dell’eseguibile e i parametri e quindi si calcoli quante occorrenze (in termini di long int) del
carattere Cx sono presenti nel file F e si visualizzi tale valore su standard output inserendo opportune frasi che facciano
capire all’utente che cosa si sta visualizzando.

**N.B.** La lettura dal file, in questo caso, DEVE essere fatta un carattere alla volta dato che si deve individuare uno
specifico carattere, come spiegato a lezione. Si verifichi il funzionamento sia con il numero non corretto di parametri
che con il numero giusto di parametri, ma di ‘tipo’ non corretto e infine il funzionamento corretto.