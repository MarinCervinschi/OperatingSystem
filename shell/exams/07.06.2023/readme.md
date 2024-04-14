# 07/06/2023
La parte in Shell deve prevedere un numero variabile di **parametri Q+1** (con Q maggiore o uguale a 2):
- il primo parametro deve essere considerato un **numero intero (X) strettamente positivo** e **strettamente minore di
4**;
- gli **altri Q** devono essere **nomi assoluti di directory** che identificano Q gerarchie (G1, G2, …) all’interno del file
system.

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in Q fasi, una per ogni gerarchia.
Il
programma, per ognuna delle Q fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi ricorsivo,
**FCR.sh** – e deve cercare tutte le directory che si trovano a livello corrispondente al numero X.
Si riporti il nome assoluto di tali directory sullo standard output. In ogni directory trovata, si deve invocare la parte in C
passando come parametri i nomi di tutti i file leggibili che NON siano vuoti (F1, F2, ...) presenti in tale direttorio.

**NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:**
- una variabile di nome X per contenere il primo parametro di FCP .sh;
- una variabile di nome G per le singole gerarchie di ognuna delle Q fasi;
- una variabile di nome F per identificare, via via, i singoli file delle directory trovate a livello X.

**OSSERVAZIONE:** se per provare la parte shell, si commenta la chiamata alla parte C, ricordarsi di togliere il commento prima della consegna!