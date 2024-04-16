# 07/09/2022
La parte in Shell deve prevedere un numero variabile di **parametri Q+1** (con Q maggiore o uguale a 2): 
- il primo parametro deve essere considerato un **numero intero strettamente positivo e dispari (X)**;
- gli altri Q devono essere nomi assoluti di directory che identificano Q gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in Q fasi, una per ogni gerarchia.
Il programma, per ognuna delle Q fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi ricorsivo,
**FCR.sh** – e deve cercare in ogni directory della gerarchia G:
- i file leggibili F la cui lunghezza in caratteri sia esattamente uguale a X: nel caso tali file F siano in posizione dispari* si deve riportare il loro nome assoluto sullo standard output. 

In ogni directory dove è stato trovato *almeno* un file (CHE SODDISFA LE CONDIZIONI PRECEDENTI), si deve invocare
la parte in C, passando come parametri i nomi dei file trovati (F1, F2, ...) che soddisfano la condizione precedente.

**NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:**
- una variabile di nome X per contenere il primo parametro di FCP.sh;
- una variabile di nome G per le singole gerarchie di ognuna delle Q fasi;
- una variabile di nome F per identificare, via via, i singoli file delle directory esplorate.

**OSSERVAZIONE:** se per provare la parte shell, si commenta la chiamata alla parte C, ricordarsi di togliere il commento prima della consegna!

\* **N.B.** Se una dir contiene: d1 (dir), d2 (dir), f1 (file leggibile di lunghezza X), f2 (idem), f3 (idem), f4 (idem), prova.txt (file leggibile
di lunghezza diversa da X), allora i file di posizione dispari che sarebbero selezionati sarebbero f1 e f3.
