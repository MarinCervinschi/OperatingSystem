### EX 1
Con un editor, scrivere un programma in C `9Giu14.c` che risolva la parte C dell’Esame del 9 Giugno
2014 che si riporta qui di seguito per comodità.

La parte in C accetta un numero variabile di parametri (maggiore o uguale a 2, da controllare) che
rappresentano N nomi assoluti di file F1...FN.
Il processo padre deve generare N processi figli (P0…PN-1): ogni processo figlio è associato al
corrispondente file. Ognuno di tali processi figli deve creare a sua volta un processo nipote (PP0…PPN-1):
ogni processo nipote PPi esegue concorrentemente calcolando la lunghezza in linee del file associato
usando in modo opportuno il comando-filtro wc di UNIX/Linux.

Ogni processo figlio Pi deve convertire in termini di valore intero* (lunghezza) quanto scritto in termini di
caratteri sullo standard output dal comando wc eseguito dal processo nipote PPi; quindi ogni figlio Pi deve
comunicare tale lunghezza al padre. 
Il padre ha il compito di ricevere, rispettando l'ordine dei file, il valore lunghezza inviato da ogni figlio Pi, calcolando via via la somma (come long int) di tutti i valori ricevuti e
stampando alla fine la somma totale (sempre come long int) su standard output.

Al termine, ogni processo figlio Pi deve ritornare al padre il valore di ritorno del proprio processo nipote
PPi e il padre deve stampare su standard output il PID di ogni figlio e il valore ritornato.

*Chiaramente il testo assume che il valore di lunghezza di ogni possibile file passato come parametro sia
rappresentabile con un intero del linguaggio C; quindi la corrispondente soluzione può fare riferimento
a questa ipotesi senza bisogno di specificarlo.

**OSSERVAZIONE1:** Si ricorda quanto detto per la soluzione dell’esame del 5 Giugno 2015 relativamente
alla pipe che serve al nipote per comunicare con il figlio: risulta più efficace che ogni figlio crei una singola
pipe prima di creare il nipote, che in totale saranno N pipe, ma appunto considerate singolarmente.

**OSSERVAZIONE2:** Il testo originale che trovate sul sito riporta l’indicazione del comando wc; infatti,
all’epoca, veniva lasciato allo studente la capacità di capire che in realtà era meglio usare il comando-filtro
wc, chiaramente inserendo un opportuno commento: in questo modo, analogamente a quanto abbiamo
visto in SHELL, i nipoti scrivono semplicemente un numero sullo standard output che essendo collegato al
lato di scrittura della pipe consentirà al figlio, in modo semplice, di ricevere solo questa informazione e
NON anche il nome del file cui il comando wc si riferisce! Nei testi attuali, la specifica invece è puntuale e
quindi se c’è scritto di usare un comando si dovranno passare il parametro nella EXEC, mentre se c’è scritto
di usare un comando-filtro bisognerà implementare la ridirezione dello standard input!

**OSSERVAZIONE3:** Fare attenzione che il nipote (cioè il comando-filtro) wc NON scrive un numero sullo
standard input, ma un insieme di caratteri numerici che terminano con uno ‘\n’; quindi, ogni figlio dovrà
andare a leggere tutti questi caratteri numerici, come visto nella soluzione dell’esame del 5 Giugno 2015;
differentemente però dalla soluzione dell’esame del 5 Giugno 2015, tali caratteri vanno salvati in un buffer
di caratteri; una volta terminata la lettura, nel buffer in corrispondenza del caratter ‘\n’ (FARE
ATTENZIONE A CALCOLARE correttamente l’indice!) si dovrà inserire il terminatore di stringa (‘\0’) e quindi
poi la strina risultante potrà essere convertita, come usuale, con la funzione di libreria atoi.