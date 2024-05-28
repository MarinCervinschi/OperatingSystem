### EX 1
Con un editor, scrivere un programma C **8Giu16.c** che risolva la parte C dell’Esame del 8 Giugno 2016 che
si riporta qui di seguito per comodità.

La parte in C accetta un numero variabile **N+1 di parametri** (con N maggiore o uguale a 4) che
rappresentano i primi N nomi di file (F1...FN), mentre l’ultimo rappresenta un numero intero (H)
strettamente positivo e minore di 255 (da controllare) che indica la lunghezza in linee dei file: infatti, la
lunghezza in linee dei file è la stessa (questo viene garantito dalla parte shell e NON deve essere
controllato).

Il processo padre deve, per prima cosa, deve inizializzare il seme per la generazione random di numeri (come
illustrato nel seguito) e deve creare un file di nome “/tmp/creato” (Fcreato). Il processo padre deve,
quindi, generare N processi figli (P0…PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli
N file Fk (con k = i+1). Ogni processo figlio Pi deve leggere le linee del file associato Fk sempre fino alla
fine. I processi figli Pi e il processo padre devono attenersi a questo schema di comunicazione: per ogni
linea letta, il figlio Pi deve comunicare al padre la lunghezza della linea corrente compreso il terminatore
di linea (come int); 

Il padre usando in modo opportuno la funzione mia_random() (riportata nel seguito)
deve individuare in modo random, appunto, quale lunghezza (come int) considerare fra quelle ricevute,
rispettando l'ordine dei file, da tutti i figli Pi; individuata questa lunghezza, usando sempre in modo
opportuno la funzione mia_random()deve individuare un intero che rappresenterà un indice per la linea
della lunghezza considerata; 

Il padre deve comunicare indietro a tutti i figli Pi tale indice: ogni figlio Pi
ricevuto l’indice (per ogni linea) deve controllare se è ammissibile per la linea corrente e in tal caso deve
scrivere il carattere della linea corrente, corrispondente a tale indice, sul file Fcreato, altrimenti non deve
fare nulla e deve passare a leggere la linea successiva.

Al termine, ogni processo figlio Pi deve ritornare al padre il valore intero corrispondente al numero di
caratteri scritti sul file Fcreato (sicuramente minore di 255); il padre deve stampare su standard output il
PID di ogni figlio e il valore ritornato.

- Chiamata alla funzione di libreria per inizializzare il seme:
```c
#include <time.h>

int main(int argc, char **argv) {
    srand(time(NULL));
    /* ... */
    return 0;
}
```
- Funzione che calcola un numero random compreso fra 0 e n-1:
```c
#include <stdlib.h>

int mia_random(int n) {
    int casuale;
    casuale = rand() % n;
    return casuale;
}
```

**OSSERVAZIONE1:** Questo testo non lo dice esplicitamente (nei compiti recenti invece viene indicato), ma
la soluzione introduce un opportuno commento e ipotizza come ragionevole una lunghezza massima delle
linee (compreso il terminatore di linea); nella soluzione caricata sul sito specifico, si è supposta questa
lunghezza pari a 255 caratteri.

**OSSERVAZIONE2:** In questo caso, è necessario creare due array di pipe: il primo array deve contenere le
pipe orientate dai figli al padre e il secondo array, invece, deve contenere le pipe orientate dal padre ai
figli. Si faccia attenzione al codice che è necessario eseguano i figli e il padre per chiudere i lati NON usati
delle pipe.

**OSSERVAZIONE3:** Il padre è l’unico che utilizza l’intero (H) che indica la lunghezza in linee dei file dato che
per ogni linea letta dai figli dai propri file deve recuperare da ogni figlio le lunghezze calcolate dai figli;
quindi, nel padre, dopo le chiusure dei lati NON usati delle pipe, ci vogliono due for innestati, uno sul
numero di linee (uguali per ogni file) e uno sul numero dei figli.

**OSSERVAZIONE4:** Il padre prima di iniziare il for più interno, sopra citato, conviene che calcoli il numero
random, compreso da 0 a N-1, che andrà a identificare quale tra tutte le lunghezze della linea corrente
(identificata dal for esterno) è quella che deve considerare per la successiva randomizzazione; fare
attenzione che il padre deve comunque leggere TUTTE le lunghezze inviate da TUTTI i figli e non si può
fare un break per uscire dal for interno!

**OSSERVAZIONE5:** Una volta usciti dal for più interno, sempre nel for più esterno, il padre deve calcolare il
numero random usando la funzione mia-random fornita passando il valore della lunghezza identificato
precedentemente (tale valore, per come scritto nel testo sarà un valore compreso tra 0 e lunghezza-1);
quindi, questo numero random va inviato con un altro for interno a tutti i figli.

**OSSERVAZIONE6:** I figli per ogni linea letta dal file (N.B. un carattere alla volta fino allo ‘\n’) devono inviare
al padre la lunghezza della linea corrente compreso il terminatore di linea (come int) e, quindi, si devono
mettere in attesa dell’indice che gli manderà il padre; una volta ricevutolo, devono verificare se sia un
indice ammissibile per la loro linea corrente sulla base del valore della lunghezza calcolato (ed inviato al
padre).

**OSSERVAZIONE7:** Fare attenzione che se un figlio termina perché il file associato non esiste, allora il padre
termina in modo anormale perché riceve il segnale SIGPIPE; sul sito è stata caricata una versione che
installa una azione specifica in modo da intercettare questo caso: a livello di esame, sarebbe stato
considerato un errore per gli studenti che non avessero considerato questo caso, solo se qualche studente
ci avesse invece pensato!