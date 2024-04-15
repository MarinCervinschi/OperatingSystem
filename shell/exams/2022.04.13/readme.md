# 11/04/2022

La parte in Shell deve prevedere un numero variabile di **parametri Q+1** (con Q maggiore o uguale a 2): 
- il primo parametro deve essere considerato un numero intero strettamente positivo (X);
- gli altri Q devono essere nomi assoluti di directory che identificano Q gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in Q fasi, una per ogni gerarchia.
Il programma, per ognuna delle Q fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** – e deve contare globalmente tutti i file leggibili la cui lunghezza in linee sia uguale a X.

Al termine di ognuna delle Q fasi, si deve riportare sullo standard output -per la gerarchia corrispondente- il
numero totale di file trovati (che soddisfano la condizione sopra indicata).
Quindi, al termine di tutte le Q fasi, si deve procedere ad un controllo sui file trovati: tale controllo deve prendere
sempre a riferimento i file trovati nella prima gerarchia (G1) e quindi per ognuno di tali file si deve controllare se
il contenuto è uguale al contenuto di ognuno dei file trovati nelle altre Q-1 gerarchie, riportando sullo standard
output una opportuna frase di spiegazione per l’utente.

ad esempio:
I file **/home/utente/ger1/d2/d3/f8** e **/home/utente/ger2/d21/d32/f82** sono uguali

**NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:**
- una variabile di nome X per contenere il primo parametro di FCP.sh;
- il nome /tmp/nomiAssoluti per la parte iniziale del nome dei file temporanei
- una variabile di nome G per le singole gerarchie di ognuna delle Q fasi;
- una variabile di nome F per identificare, via via, i singoli file delle directory esplorate