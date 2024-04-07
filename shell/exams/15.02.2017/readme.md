# 15/02/2017

La parte in Shell deve prevedere **due parametri**:
- il primo deve essere il **nome assoluto di una directory** che
identifica una gerarchia (G) all’interno del file system;
- il secondo parametro deve essere considerato un **numero
intero X strettamente positivo**.

Il programma deve cercare nella gerarchia G specificata tutte le directory che
contengono almeno un file leggibile con lunghezza in linee pari X e il cui contenuto del file sia tale per cui tutte le sue linee contengano almeno un carattere numerico.

Si riporti il nome assoluto di tali directory sullo standard
output e quindi i nomi di tutti i file trovati (F1, F2, … FN). Quindi in ogni directory trovata, chiesta conferma
all’utente, si deve invocare la parte in C, passando come parametri i nomi dei file trovati (F1, F2, … FN) e la loro
lunghezza in linee X.