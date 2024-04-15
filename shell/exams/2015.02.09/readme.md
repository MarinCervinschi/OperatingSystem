# 09/02/2015

La parte in Shell deve prevedere **due parametri**: 
- il primo deve essere il **nome assoluto di una directory** che identifica una gerarchia (G) all’interno del file system;
- il secondo deve essere considerato un **numero intero strettamente positivo** (K). 

Il programma deve cercare nella gerarchia G specificata tutte le directory che
contengono almeno un file leggibile con lunghezza in linee pari a K: si riporti il nome assoluto di tali directory sullo
standard output. 

Al termine dell’intera esplorazione ricorsiva di G, per ogni file trovato Fi si deve richiedere
all’utente un numero Xi intero strettamente positivo e minore o uguale a K: quindi si deve invocare la parte in C
passando come parametri i nomi assoluti dei file trovati intervallati dal numero corrispondente chiesto all’utente
(perciò i parametri saranno: F0, X0, F1, X1, ... FN-1, XN-1).