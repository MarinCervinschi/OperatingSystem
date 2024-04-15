# 07/04/2017
La parte in Shell deve prevedere un numero variabile di **parametri N+1** (con N maggiore o uguale a 2):
- il primo parametro deve essere il **nome relativo semplice F di un file**;
- gli altri N devono essere **nomi assoluti di direttori** che identificano N
gerarchie (G1, G2, …) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è
organizzato in N fasi, una per ogni gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi
corrispondente - tramite un file comandi ricorsivo, **FCR.sh** - e deve contare globalmente tutti i file con nome relativo semplice sorted che saranno creati secondo quanto di seguito specificato:
- il file comandi ricorsivo FCR.sh deve cercare tutti i file leggibili il cui nome sia F;
- per ognuno di tali file deve produrre un file ordinato (di nome sorted) secondo l’ordine alfabetico, ma senza tenere
conto di minuscole/maiuscole.

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale di file creati globalmente. In seguito, per ogni file creato, si deve riportare sullo standard output il suo nome assoluto, e quindi la prima e
l'ultima linea del file.
(esattamente in questo ordine, con opportune frasi che facciano capire all’utente
che cosa si sta visualizzando).