# 05/04/2019

La parte in Shell deve prevedere un numero variabile di parametri **N+1** (con N maggiore o uguale a 2): 
- i primi N devono essere **nomi assoluti di directory** che identificano N gerarchie (G1, G2, …GN) all’interno del file system;
- l’ultimo parametro deve essere considerato una semplice stringa **S**. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** - e deve contare globalmente tutti i file che hanno le caratteristiche di seguito specificate. 

Il file comandi ricorsivo FCR.sh deve cercare in tutte le directory ogni file leggibile e scrivibile con nome relativo semplice
S.txt; si dovrà quindi salvare in modo opportuno contestualmente la lunghezza in caratteri e il nome assoluto del
file trovato. 

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale di file trovati
globalmente. In seguito, per ogni file trovato, si deve riportare la sua lunghezza in caratteri sullo standard output
e quindi il suo nome assoluto, (entrambe queste informazioni precedentemente salvate): quindi si deve richiedere
all’utente se si vuole o meno ordinare il file e, in caso affermativo, si devono riportare su standard output il file
ordinato secondo il normale ordine alfabetico, senza differenziare maiuscole e minuscole, altrimenti si deve
riportare una opportuna frase.