# EX 4
Con un editor, scrivere un programma in C **provaValoriWait.c**, che, partendo dal programma
status1.c mostrato a lezione (disponibile su GITHUB), modifichi il codice del processo figlio in modo
che legga (con una scanf) un numero intero (valore);

quindi il figlio deve verificare se valore è strettamente maggiore di 255 oppure se è negativo e in tal caso il figlio deve riportare su standard output che valore sarà troncato, altrimenti deve riportare che valore NON verrà troncato;

il figlio deve tornare al padre, con la exit, valore e il padre deve stampare su standard output il pid del figlio e il
valore ritornato. 

Si provi il funzionamento del programma fornendo via via i seguenti valori in input: 10,
125, 255, 256, 355, -1; 

per quali valori avviene il troncamento?