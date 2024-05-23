### EX 2
Con un editor, scrivere un programma in C **31Mag19.c** che risolva la parte C dell’Esame del 31 Maggio
2019 che si riporta qui di seguito per comodità.

La parte in C accetta un numero variabile N di parametri **maggiore o uguale a 3** (da controllare) che
rappresentano nomi assoluti di file F1...FN. Il processo padre deve generare N processi figli: i processi figli
Pi sono associati agli N file Fh (con h = i+1). 

Ognuno di tali figli deve creare a sua volta un processo nipote PPi: ogni processo nipote PPi esegue concorrentemente e deve ordinare il file Fh secondo il normale ordine alfabetico, senza differenziare maiuscole e minuscole, usando in modo opportuno il comando sort di UNIX/Linux. Ogni processo figlio Pi deve ricevere solo la PRIMA linea inviata dal suo processo nipote PPi e deve inviare al processo padre una struttura dati, che deve contenere tre campi: 

1) c1, di tipo int, che deve contenere il PID del nipote; 
2) c2, di tipo int, che deve contenere la lunghezza della linea compreso il terminatore di linea; 
3) c3, di tipo char[250]*, che deve contenere la linea corrente ricevuta dal nipote. 

Il padre deve ricevere, rispettando l'ordine dei file, le singole strutture inviate dai figli e deve stampare su standard output, per ogni struttura ricevuta, ognuno dei campi insieme al nome del file cui le informazioni si riferiscono: si faccia attenzione al fatto che è demandato al padre il compito di trasformare, in una stringa, la linea ricevuta nel campo c3 di ogni struttura! 

Al termine, ogni processo figlio Pi deve ritornare al padre la lunghezza della linea inviata al padre, ma non compreso il terminatore di linea e il padre deve stampare su standard output il PID di ogni figlio e il valore ritornato.

*Ogni linea si può supporre che abbia una lunghezza massima di 250 caratteri, compreso il terminatore
di linea e il terminatore di stringa.

**OSSERVAZIONE:** In questo caso risulta opportuno seguire il testo e quindi usare il comando sort (e non il
comando-filtro sort), in modo da avere un codice del nipote con meno istruzioni, chiaramente passando
il nome del file nella execlp!

**N.B.** Sul sito si trovano altre tre versioni del testo con le rispettive soluzioni: quella riportata qui è la
versione dei turni 1 e 2.