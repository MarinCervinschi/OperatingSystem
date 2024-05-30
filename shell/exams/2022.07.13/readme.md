# 13/07/2022
La parte in Shell deve prevedere un numero variabile di **parametri Q+2** (con Q maggiore o uguale a 2): 
- il primo parametro deve essere il nome assoluto di una directory che identifica una gerarchia all’interno del file system (G)
- il secondo deve essere considerato un numero intero strettamente positivo (L);
- gli altri Q devono essere considerati singoli caratteri (C1, …CQ). 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in una singola fase.
Il programma deve esplorare la gerarchia G - tramite un file comandi ricorsivo, `FCR.sh` - e deve cercare tutti i file che
hanno lunghezza in linee uguale a L e che contengono (nel contenuto) almeno una occorrenza di TUTTI i caratteri C1,
…CQ. Si riporti il nome assoluto di ognuno di tali file F sullo standard output.

Al termine dell’unica fase, si deve riportare sullo standard output il numero totale di file trovati (che soddisfano la
condizione sopra indicata). Quindi, per ognuno dei file trovati, si deve invocare la parte in C, passando come parametri
F, L e i caratteri C1, …CQ.

**NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:**
- una variabile di nome `G` per il primo parametro;
- una variabile di nome `F` per identificare, via via, i singoli file per i quali si deve invocare la parte C;
- una variabile di nome `L` per la lunghezza in linee del file corrente;
- il nome `/tmp/nomiAssoluti` per il nome del file temporaneo.