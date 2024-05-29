### EX 3
Con un editor, scrivere un programma in C **14Giu17.c** che risolva la parte C dell’Esame del 14 Giugno 2017
che si riporta qui di seguito per comodità.

La parte in C accetta un numero variabile **N+1 di parametri**(con N maggiore o uguale a 1, da controllare)
che rappresentano i primi N nomi assoluti di file (F1, F2, ... FN) mentre l’ultimo rappresenta un singolo
carattere (Cx) (da controllare): si può ipotizzare che la lunghezza di tutti i file sia uguale (senza verificarlo).

Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a
N-1) sono associati agli N file FK (con K=i+1). Ogni processo figlio Pi deve leggere i caratteri del file
associato FK cercando le occorrenze del carattere Cx, sostituendole eventualmente con i caratteri inviati
dal padre. Ogni figlio Pi, per ogni occorrenza trovata, deve comunicare al padre la posizione (in termini di
long int) di tale occorrenza a partire dall’inizio del file*. 

Il padre deve ricevere le posizioni (come long int) inviate dai figli nel seguente ordine: prima deve ricevere dal figlio P0 la prima posizione inviata, poi deve
ricevere dal figlio P1 la prima posizione inviata e così via fino a che deve ricevere dal figlio PN-1 la prima
posizione inviata; quindi, deve procedere a ricevere le seconde posizioni inviate dai figli (se esistono) e
così via. La ricezione di posizioni da parte del padre deve terminare quando ha ricevuto tutte le posizioni
inviate da tutti i figli Pi. 

Per ogni posizione ricevuta, il padre deve riportare sullo standard output: l’indice
del figlio che gli ha inviato la posizione, il nome del file in cui è stata trovata l’occorrenza del carattere Cx
e (naturalmente) la posizione ricevuta. Quindi, per ogni posizione ricevuta, il padre deve chiedere
all’utente il carattere con cui deve essere sostituita la specifica occorrenza; nel caso l’utente inserisca una
linea vuota, questo deve essere interpretato dal padre come indicazione di non sostituire l’occorrenza
corrente. 
Il padre, per ogni posizione, deve comunicare al figlio corrispondente o il carattere da sostituire
oppure se può proseguire con la ricerca di altre occorrenze del carattere Cx.

Al termine, ogni processo figlio Pi deve ritornare al padre il numero di sostituzioni effettuate nel proprio
file (supposto strettamente minore di 255); il padre deve stampare su standard output il PID di ogni figlio
e il valore ritornato.

*Si precisi, come commento nel codice, se il primo carattere del file viene considerato in posizione 0 o in
posizione 1.

**OSSERVAZIONE1:** Come nel programma sostituisciCar.c dell’esercitazione dell’11 Aprile 2024, fare
attenzione alla modalità di apertura del file associato e di come si debba operare la trasformazione.

**OSSERVAZIONE2:** Nella soluzione che si trova sul sito specifico, si è deciso di considerare che la
numerazione della posizione inizi da 1: si veda commento nel codice.

**OSSERVAZIONE3:** Poiché, in questo caso, il padre (dopo aver ricevuto una singola posizione da un figlio)
deve inviare un carattere (con cui deve essere sostituita la specifica occorrenza o la linea vuota) solo a tale
figlio, il ciclo di iterazione che serve al padre per recuperare tutte le posizioni inviate da tutti i figli, può
essere basato esclusivamente su una singola variabile finito (inizializzata a 0, che vuole dire che nessun
figlio è finito, mentre 1 vorrà dire che tutti i figli sono finiti), piuttosto che sull’array dinamico finito e sulla
funzione finitof(), usati per la soluzione dell’11 Luglio 2018, vista a lezione.

**OSSERVAZIONE4:** Nella soluzione che si trova sul sito specifico, si è deciso di usare la read(0,…,…) per far
leggere il padre da standard input quanto indicato dall’utente e quindi il carattere con cui deve essere
sostituita la specifica occorrenza oppure la linea vuota (cioè solo lo ‘\n’). In alternativa, si può usare la
scanf, ma in ogni modo bisogna fare attenzione a scartare il carattere corrispondente all’INVIO/RET da
tastiera, nel caso di inserimento del carattere con cui deve essere sostituita la specifica occorrenza!