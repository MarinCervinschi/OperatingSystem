# 15/06/2022

La parte in Shell deve prevedere un numero variabile di **parametri Q**(con Q maggiore o uguale a 3): 
- che devono essere **nomi assoluti di directory** che identificano Q gerarchie (G1, G2, …) all’interno del file
system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in Q fasi, una
per ogni gerarchia.
Il programma, per ognuna delle Q fasi, deve esplorare la gerarchia G corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** – e deve contare globalmente tutti i file che saranno cercati secondo quanto di seguito
specificato. 

Il file comandi ricorsivo FCR.sh deve cercare in ogni gerarchia G che esista almeno un file (F)
di lunghezza non nulla e che contenga (nel suo contenuto) solo caratteri di tipo alfabetico minuscolo: per
ogni file trovato F, si deve riportare, contestualmente, il suo nome assoluto sullo standard output. Al termine
di tutte le Q fasi, si deve riportare sullo standard output il numero N di file trovati e si deve invocare la parte
in C, passando come parametri i nomi dei file trovati (F1, F2, ... FN).

**NOTA BENE NEI DUE FILE COMANDI SI USI OBBLIGATORIAMENTE:**
- una variabile di nome G per le singole gerarchie di ognuna delle Q fasi;
- il nome /tmp/nomiAssoluti per il file temporaneo;
- una variabile di nome N per contenere il numero dei file trovati globalmente;
- una variabile di nome F per identificare, via via, i singoli file delle directory esplorate in FCR.sh.