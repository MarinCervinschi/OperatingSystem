# EX 10
Scrivere un programma in C **myhead1.c** che deve essere invocato esattamente con **un parametro** che deve essere
considerato come la tipica opzione del comando-filtro head e quindi -n (dove n deve essere un numero).

Nei controlli da effettuare si deve considerare di controllare che il primo carattere dell’unico parametro passato deve essere il
carattere ‘-‘; quindi la conversione da stringa a numero (con relativo controllo che tale numero sia strettamente
positivo e valido, come fatto nei precedenti esercizi) deve prendere in considerazione la stringa il cui indirizzo iniziale
è &(argv[1][1]). 

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), il
programma si deve comportare come il comando-filtro head e quindi deve filtrare in uscita le prime numero linee
dello standard input.

**N.B.** La lettura deve avvenire, anche in questo caso, un carattere alla volta, dato che si deve cercare il carattere '\n'
riportando sempre contestualmente il carattere letto (anche lo ‘\n’) sullo standard output; il contatore del numero di
linee lo si faccia partire da 1 e quindi quando i caratteri ‘\n’ incontrati saranno arrivati a superare n si potrà concludere
il ciclo di lettura, ad esempio con un break. Si verifichi il funzionamento.