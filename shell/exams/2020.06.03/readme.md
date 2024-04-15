# 03/06/2020

La parte in Shell deve prevedere un numero variabile di parametri **N+1** (con N maggiore o uguale a 2): 
- il primo parametro deve essere considerato un singolo carattere C;
- gli altri N devono essere **nomi assoluti di directory** che identificano N gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** - e deve contare globalmente tutte le directory D che hanno le caratteristiche di seguito
specificate. 

Il file comandi ricorsivo FCR.sh deve cercare tutte le directory D il cui nome sia di 3 caratteri e i cui
caratteri dispari, sempre nel nome, siano uguali al carattere C.

Al termine di tutte le N fasi, si deve riportare sullo standard output:
* a) il numero totale di directory D trovate globalmente (che soddisfano la condizione sopra indicata);
* b) i nomi assoluti delle directory D trovate e, contestualmente, per ogni directory D si deve chiedere all’utente,
chiamandolo Elena, se vuole o meno visualizzare il contenuto della directory D compresi anche gli elementi
nascosti.

**NOTA BENE NEL FILE COMANDI FCP.sh SI USI OBBLIGATORIAMENTE:**
- una variabile di nome C per il primo parametro;
- il nome /tmp/nomiAssoluti per il file temporaneo
- una variabile di nome answer per ricevere la risposta di Elena