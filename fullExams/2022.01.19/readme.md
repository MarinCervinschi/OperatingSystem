# Esame 19 Gennaio 2022

## Testo parte Shell
La parte in Shell deve prevedere un numero variabile di parametri Q+2 (con Q maggiore o uguale a 2): 
- il primo parametro (`C`) deve essere considerato un numero intero strettamente positivo dispari;
- il secondo parametro (`X`) deve essere considerato un numero intero strettamente positivo pari;
- gli altri `Q` devono essere nomi assoluti di directory che identificano Q gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in `Q` fasi, una per ogni
gerarchia.
Il programma, per ognuna delle Q fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi
ricorsivo, `FCR.sh` – e deve cercare tutte le directory che contengono almeno un file leggibile la cui lunghezza
in caratteri sia uguale a `X` e sia anche un multiplo intero di `C`. Si riporti il nome assoluto di tali directory
sullo standard output. Al termine di tutte le `Q` fasi, si deve riportare su standard output il numero totale di file
trovati globalmente (che soddisfano le condizioni sopra riportate) e si deve invocare la parte in C, passando
come parametri i nomi assoluti di tutti i file trovati globalmente e il numero `C`.

### NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:
- una variabile di nome `C` per contenere il primo parametro di `FCP.sh`;
- una variabile di nome `X` per contenere il secondo parametro di `FCP.sh`;
- una variabile di nome `G` per le singole gerarchie di ognuna delle `Q` fasi;
- il nome `/tmp/nomiAssoluti` per il file temporaneo;
- una variabile di nome `F` per identificare, via via, i singoli file delle directory esplorate;