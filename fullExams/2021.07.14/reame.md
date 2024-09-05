# Esame 14 Luglio 2021
## TESTO PARTE SHELL
La parte in Shell deve prevedere un numero variabile di parametri `Q`+2 (con `Q` maggiore o uguale a 2): 
- i primi `Q` devono essere nomi assoluti di directory che identificano `Q` gerarchie (G1, G2, …) all’interno del file system;
- gli ultimi due parametri devono essere considerati numeri interi strettamente positivi (`H` e `M`). 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in `Q` fasi, una per ogni gerarchia.
Il programma, per ognuna delle `Q` fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi ricorsivo, `FCR.sh` – e deve cercare tutte le directory che contengono un numero strettamente minore di `H` ma maggiore o uguale a 2 di file (F1, F2, ...) il cui nome sia costituito da esattamente 2 caratteri e con lunghezza in linee esattamente uguale a `M`. Si riporti il nome assoluto di tali directory sullo standard output. 

In ognuna di tali directory trovate, si deve invocare la parte in C, passando come parametri i nomi dei file trovati (F1, F2, ...) che soddisfano la condizione precedente e il numero `M`.

### NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:
- una variabile di nome `H` per contenere il penultimo parametro di `FCP.sh`;
- una variabile di nome `M` per contenere l’ultimo parametro di `FCP.sh`;
- una variabile di nome `G` per le singole gerarchie di ognuna delle `Q` fasi;
- una variabile di nome `F` per identificare, via via, i singoli file delle directory esplorate;
- una variabile di nome `cont` per contare i file che soddisfano la specifica.