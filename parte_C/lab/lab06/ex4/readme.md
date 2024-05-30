### EX 4
Con un editor, scrivere un programma in C **13Lug22.c** che risolva la parte C dell’Esame del 13 Luglio 2022
che si riporta qui di seguito per comodità.

TESTO PARTE C: **ATTENZIONE LEGGERE ANCHE LA NOTA SEGUENTE AL TESTO!**

La parte in C accetta un numero variabile di **parametri Q+2** (con Q maggiore o uguale a 2), F, L e C1, …CQ,
che rappresentano rispettivamente le seguenti informazioni: il primo il nome assoluto di un file (F), il
secondo la lunghezza in linee di F (L, strettamente positivo da controllare) e gli ultimi Q devono essere
considerati singoli caratteri (da controllare). 

Il processo padre deve generare un numero di processi figli pari a Q: ogni processo figlio Pq è associato ad uno dei caratteri C1, …, CQ (in ordine).
Ognuno di tali processi figli Pq esegue concorrentemente e calcola il numero di occorrenze del proprio
carattere associato, per ognuna delle L linee del file F. I processi padre e figli devono sincronizzarsi
strettamente a vicenda utilizzando uno schema di sincronizzazione a ring che deve comprendere anche
il padre in modo che, per ognuna delle L linee del file F, sullo standard output siano scritte le seguenti
informazioni: 

- il padre deve riportare il numero di linea correntemente analizzata da tutti i processi figli;
    - (NB: la numerazione delle linee deve essere fatta partire da 1)
- Il nome del file; 

Il primo figlio (P0) deve riportare il numero di occorrenze del proprio carattere (C1) trovate nella linea corrente, insieme
con il proprio indice e il proprio PID; il secondo figlio (P1) deve riportare il numero di occorrenze del proprio
carattere (C1) trovate nella linea corrente, insieme con il proprio indice e il proprio PID; così via per tutti i
figli e per tutte le L linee del file F.

**ESEMPIO DI OUTPUT, SUPPONENDO DI AVERE 2 CARATTERI PASSATI E 2 LINEE NEL FILE F:**
```plaintext
Linea 1 del file /home/soELab/prova.txt
Figlio con indice 0 e pid 13290 ha letto 1 caratteri S nella linea corrente
Figlio con indice 1 e pid 13291 ha letto 2 caratteri n nella linea corrente
Linea 2 del file /home/soELab/prova.txt
Figlio con indice 0 e pid 13290 ha letto 2 caratteri S nella linea corrente
Figlio con indice 1 e pid 13291 ha letto 7 caratteri n nella linea corrente
```

Al termine dell’esecuzione, ogni figlio Pq ritorna al padre il numero (supposto strettamente minore di 255)
di occorrenze trovate nell’ultima linea del file F; il padre deve stampare su standard output il PID di ogni
figlio e il valore ritornato.

**NOTA BENE NEL FILE C main.c SI USI OBBLIGATORIAMENTE:**
- una variabile di nome Q per il numero di processi figli;
- una variabile di nome q per l’indice dei processi figli;
- una variabile di nome L per la lunghezza in linee del file F.

**OSSERVAZIONE1:** Diversamente da quanto visto a lezione, nella soluzione del 17 Febbraio 2021, il numero
di pipe deve essere una in più dei processi (quindi Q+1 e non solo Q), dato che si deve considerare nel ring
anche il padre, che nella soluzione invece vista a lezione faceva solo da ‘innesco’ per il ring. Questo cambia,
quindi, anche il calcolo per la pipe su cui scrivere, mentre quella da cui leggere rimane sempre quella
corrispondente all’indice del processo (la pipe q): invece, per quanto riguarda la pipe su cui scrivere, nella
soluzione vista a lezione si doveva usare la pipe (q+1)%Q, in modo che l’ultimo figlio scrivesse sulla pipe 0
che appunto chiudeva il ring sul figlio di indice 0, mentre, in questo caso, si deve semplicemente usare la
pipe q+1 che per l’ultimo figlio vale Q e lo collega al padre e poi il padre per far ripartire il ring scriverà
sulla pipe di indice 0! Poiché il padre è nel ring non sarà necessario lasciare aperti lati di pipe che NON
usa!

**OSSERVAZIONE2:** Ricordarsi che, come nel caso dei programmi provaEsame2-a.c e provaEsame2-b.c
dell’esercitazione del 9/05/2024, nonché del programma in C 9Set16.c dell’esercitazione del 16/05/2024,
l’apertura dell’unico file F deve essere effettuata da ogni figlio e NON dal padre, dato che ogni figlio deve
avere il proprio file-pointer per cercare il carattere associato!

**OSSERVAZIONE3:** La sincronizzazione richiesta è necessaria solo ed esclusivamente quando ogni singolo
figlio e il padre devono scrivere su standard output: quindi i figli devono leggere concorrentemente le linee
del proprio file cercando le occorrenze del proprio carattere associato e solo arrivati alla fine della linea
corrente devono mettersi in attesa dell’OK del figlio precedente (a parte il primo figlio che lo riceve dal
padre!).

OSSERVAZIONE4: Poiché questa specifica NON richiede la stampa della linea corrente, ogni figlio può
semplicemente leggere un carattere alla volta, senza bisogno di salvare i caratteri in un array e questa è la
ragione per cui il testo NON indicava la lunghezza massima che si poteva ipotizzare per le linee!