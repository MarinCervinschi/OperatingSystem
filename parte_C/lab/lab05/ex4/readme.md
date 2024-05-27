### EX 4
Con un editor, scrivere un programma in C **12Set18.c** che risolva la parte C dell’Esame del 12
Settembre 2018 che si riporta qui di seguito per comodità.

La parte in C accetta un **numero variabile N di parametri** (con N maggiore o uguale a 2, da controllare) che
rappresentano N nomi di file (F1, F2, ... FN).
Il processo padre deve generare N processi figli Pi (P0 … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N file Ff (con f= i+1). 

Ognuno di tali processi figli deve creare a sua volta un processo
nipote PPi (PP0 … PPN-1) associato sempre al corrispondente file Ff. Ogni processo figlio Pi e ogni nipote
PPi esegue concorrentemente andando a cercare nel file associato Ff tutte le occorrenze dei caratteri
numerici per il figlio e tutte le occorrenze dei caratteri alfabetici minuscoli per il nipote. Ognuno dei
processi figlio e nipote deve operare una modifica del file Ff: in specifico, ogni nipote deve trasformare
ogni carattere alfabetico minuscolo nel corrispondente carattere alfabetico maiuscolo, mentre ogni figlio
deve trasformare ogni carattere numerico nel carattere spazio. 

Una volta terminate le trasformazioni, sia i processi figli Pi che i processi nipoti PPi devono comunicare al padre il numero (in termini di long int) di trasformazioni effettuate. Il padre ha il compito di stampare su standard output, rispettando l'ordine dei file, il numero di trasformazioni ricevute da ogni figlio Pi e da ogni nipote PPi, riportando opportuni commenti esplicativi, che devono includere anche il nome del file che è stato interessato dalle
trasformazioni.

Al termine, ogni processo nipote PPi deve ritornare al figlio Pi un opportuno codice ed analogamente ogni
processo figlio Pi deve ritornare al padre un opportuno codice; il codice che ogni nipote PPi e ogni figlio
Pi deve ritornare è:

- a) 0 se il numero di trasformazioni attuate è minore di 256;
- b) 1 se il numero di trasformazioni attuate è maggiore o uguale a 256, ma minore di 512;
- c) 2 se il numero di trasformazioni attuate è maggiore o uguale a 512, ma minore di 768;
- d) etc.

Sia ogni figlio Pi e sia il padre devono stampare su standard output il PID di ogni nipote/figlio e il valore
ritornato.

**OSSERVAZIONE1:** In questo caso, devono essere previsti due array di pipe, uno per la comunicazione figli-
padre e uno per la comunicazione nipoti-padre e queste pipe le deve TUTTE creare il padre prima di creare
i figli!

**OSSERVAZIONE2:** La chiusura delle pipe nipoti-padre da parte di ogni figlio va assolutamente fatta SOLO
dopo la creazione del proprio nipote!

**OSSERVAZIONE3:** Come nel programma sostituisciCar.c dell’esercitazione del 20 Aprile 2023,
fare attenzione alla modalità di apertura del file associato, che deve essere aperto sia nel figlio che nel
nipote, e di come si debba operare la trasformazione.

**OSSERVAZIONE4:** Fare attenzione che, nonostante ogni figlio debba aspettare il proprio nipote per
stampare come richiesto PID e valore ritornato, i figli NON devono tornare al padre tale valore, ma devono
tornare un proprio valore, calcolato come indicato nel testo!