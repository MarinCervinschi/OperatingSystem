### EX 6
Con un editor, scrivere un programma C che deve prevedere un numero variabile **N+1 di parametri** (con
N maggiore o uguale a 2, da controllare): 
- il primo parametro rappresenta il nome di file (F);
- gli altri N rappresentano singoli caratteri (C1 ...CN, da controllare). 

Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia da 0 a N-1) sono associati agli N caratteri `Cf` (con f = i+2). Ogni processo figlio Pi esegue in modo concorrente ed esamina il file F contando le occorrenze del
carattere associato `Cf`: per il conteggio deve essere usata una variabile di tipo `long int`; 

Terminata la lettura del file F, ogni figlio Pi deve comunicare al padre quante occorrenze di `Cf` ha trovato. Il padre deve
ricevere i conteggi inviati dai figli e li deve riportare sullo standard output specificando a quale carattere
`Cf` si riferisce ogni singolo conteggio. Al termine, ogni processo figlio Pi deve ritornare al padre il carattere
`Cf` associato. Il padre deve stampare su standard output il pid di ogni figlio e il valore ritornato.

**ATTENZIONE:** rispetto alla stampa fatta dal padre del valore tornato dal figlio si consideri quanto detto
per l’esercizio precedente!
Per risolvere questo problema si possono usare due protocolli di comunicazione; 

quindi si devono scrivere DUE programmi C, uno di nome **provaEsame2-a.c** e uno di nome **provaEsame2-b.c**:
- 6.a Nel programma provaEsame2-a.c si devono usare N pipe (una per ogni processo figlio su cui
viene scritto il numero di occorrenze del carattere Cf associato): in tale modo, il padre può
individuare a quale carattere si riferisce il conteggio inviato ricavandolo dall’indice della pipe!

**OSSERVAZIONE:** Vista la specifica di questa versione per ottenere N pipe si DEVE seguire quanto
mostrato nella lezione di Mercoledì 9 Maggio e che si riporta per l’esercizio corrente qui nel seguito!
- 6.b Nel programma provaEsame2-b.c si deve usare una sola pipe su cui ogni figlio scrive una
struct con due campi (il carattere Cf e il numero long int di occorrenze); questa soluzione può essere
accettabile visto che il testo non richiede che le informazioni inviate dai figli vengano recuperate
dal padre in un ordine specifico.

**OSSERVAZIONE:** nei testi recenti viene specificato se va usata una struct o altra str

### Come ottenere N pipe, con N non noto staticamente:

1) DEFINIZIONE ARRAY DINAMICO piped
```C
typedef int pipe_t[2]; /* definizione del TIPO pipe_t come array di 2
interi */
…
pipe_t *piped; /* array dinamico di pipe descriptors per comunicazioni
figli-padre */
```
2) ALLOCAZIONE ARRAY DINAMICO piped DI DIMENSIONE N – ATTENZIONE: DA CONTROLLARE SEMPRE!
```C
/* Allocazione dell'array di N pipe descriptors */
piped = (pipe_t *) malloc (N*sizeof(pipe_t));
if (piped == NULL) { 
    printf("Errore nella allocazione della memoria\n");
    exit(3); 
}
```
3) CREAZIONE DELLE N PIPE PER COMUNICAZIONE FIGLI-PADRE
```C
/* Creazione delle N pipe figli-padre */
for (int j = 0; j < N; j++) { 
    if(pipe(piped[j]) < 0) { 
        printf("Errore nella creazione della pipe\n");
        exit(); 
    }
}
```
4)
- 4.a) CHIUSURE LATI PIPE NON USATI DA FIGLIO Pi➔ ogni figlio eredita per copia dal padre l’array di
pipe (piped)
```C
/* Chiusura delle pipe non usate nella comunicazione con il padre */
for (int k = 0; k < N; k++) { 
    close(piped[k][0]);
    if (k != i) {
        close(piped[k][1]);
    }
}
```
- 4.b) CHIUSURE LATI PIPE NON USATI DAL PADRE dell’array di pipe (piped)
```C
/* padre chiude tutte le pipe che non usa */
for (int k = 0; k < N; k++) {
    close(piped[k][1]);
}
```
