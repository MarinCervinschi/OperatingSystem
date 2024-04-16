# 11/04/2014

La parte in Shell deve prevedere **N parametri:** (con N maggiore o uguale a 2):
- devono essere **nomi assoluti di direttori** che identificano N gerarchie (G1, G2, … GN) all’interno del file system. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi specificata -
tramite un file comandi ricorsivo, **FCR.sh** - e deve contare globalmente per ogni gerarchia Gi tutti i file leggibili che soddisfano la seguente specifica:
- il contenuto del file deve essere tale per cui tutte le sue linee iniziano con il carattere ‘a’.

Al termine di tutte le N fasi, per ognuna delle gerarchie Gi, si deve riportare sullo standard output il nome della
gerarchia Gi e il numero totale di file di quella gerarchia che soddisfano la specifica precedente (file trovati);
inoltre, si deve riportare sullo standard output il nome assoluto di ogni file trovato chiedendo contestualmente
all’utente un numero X: tale numero deve essere usato per riportare sullo standard output le prime X linee del
file trovato corrente.