### EX 6
Scrivere un programma in C **padreFigliNipotiConExec.c** che deve prevedere un numero
variabile N di parametri (con N maggiore o uguale a 3, da controllare) che rappresentano nomi di file (F1,
F2. ... FN). 

Il processo padre deve generare N processi figli (P0, P1, … PN-1, indicati nel seguito Pi): i
processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f = i+1, quindi IN ORDINE!).
Ogni processo figlio Pi deve, per prima cosa, creare un file FOut il cui nome deve risultare dalla
concatenazione del nome del file associato Ff con la stringa “.sort”. Quindi, ogni processo figlio Pi deve
creare, a sua volta, un processo nipote PPi: ogni processo nipote PPi esegue concorrentemente e deve
ordinare il file Ff secondo il normale ordinamento alfabetico usando in modo opportuno il comando-filtro
sort di UNIX/Linux riportando il risultato di tale comando sul file FOut.

Al termine, ogni processo nipote PPi deve ritornare al figlio Pi (che corrisponde al proprio padre) il valore
ritornato dal comando sort (in caso di insuccesso nella esecuzione della primitiva exec deve essere tornato
il valore -1) e, a sua volta, ogni processo figlio Pi lo deve ritornare al padre (nonno nei confronti dei nipoti).
Il padre deve stampare, su standard output, i PID di ogni figlio con il corrispondente valore ritornato.