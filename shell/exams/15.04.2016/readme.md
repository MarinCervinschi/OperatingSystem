# 15/04/2016
La parte in Shell deve prevedere un numero variabile di parametri **N+1** (N maggiore o uguale a 2): 
- i primi N parametri devono essere **nomi assoluti di directory** che identificano N gerarchie (G1, G2, …) all’interno del file
system; 
- l’ultimo parametro deve essere considerato un **numero intero X strettamente positivo**. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni
gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** - e devono contare globalmente tutte le directory che soddisfano le seguenti due specifiche: 
1) devono contenere solo file (e non sotto-directory)
2) devono contenere solo file la cui lunghezza in linee sia strettamente maggiore di X. 

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale
delle directory trovate globalmente che soddisfano la specifica precedente (directory trovate). 

Inoltre, per ogni directory trovata, si deve riportare sullo standard output il suo nome assoluto, e quindi per ognuno dei file (file
corrente) in esso contenuto deve essere riportato sullo standard output il suo nome assoluto e contestualmente
la linea X-esima del file corrente a partire dalla fine del file.