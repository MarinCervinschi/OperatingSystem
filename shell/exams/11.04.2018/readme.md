# 11/04/2018

La parte in Shell deve prevedere un numero variabile di parametri **N+1** (con N maggiore o uguale a 2): 
- il primo parametro deve essere considerato un **numero intero Y strettamente positivo**;
- gli altri N devono essere **nomi assoluti di directory** che identificano N gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh**- e deve contare globalmente tutti i file che saranno creati secondo quanto di seguito specificato.

Il file comandi ricorsivo FCR.sh deve cercare in tutte le directory ogni file leggibile f1 con lunghezza in linee
maggiore o uguale Y; si dovrà quindi selezionare la singola linea numero 5 a partire dall’inizio del file che dovrà
essere scritta in un file appositamente creato avente nome f.quinta;
in caso, il file sia più corto e non sia possibile selezionare la linea sopra specificata bisogna creare un file vuoto di nome f.NOquinta.

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale di file creati globalmente. In seguito, per ogni file creato,
si deve riportare sullo standard output il suo nome assoluto, e quindi il suo contenuto con opportune frasi che
facciano capire all’utente che cosa si sta visualizzando.

**NOTA BENE:** avendo usato l’indicazione generica f per ogni file che soddisfa le specifiche indicate, quando nel seguito si usa
la notazione f.quinta e f.NOquinta si intende che al posto della f si deve mettere il nome del file!