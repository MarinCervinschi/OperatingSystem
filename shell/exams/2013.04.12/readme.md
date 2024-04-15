# 12/04/2013
La parte in Shell deve prevedere **tre parametri**: 
- il primo deve essere il **nome assoluto di un direttorio** che identifica una gerarchia (G) all’interno del file system;
- il secondo deve essere una **stringa (S)**;
- il terzo parametro deve essere considerato un **numero intero strettamente positivo (N)**. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in due fasi (Fasi A e B).
Il programma nella fase A deve esplorare la gerarchia G specificata - tramite un file comandi ricorsivo, **FCR.sh** - e
deve contare globalmente tutti i direttori (inclusa la radice) che contengono almeno un file
leggibile il cui nome abbia terminazione .S.

Al termine dell’intera esplorazione ricorsiva di G, si deve riportare sullo standard output il numero totale di
direttori della gerarchia G che soddisfano la condizione precedente insieme con il loro nome assoluto. Quindi il
programma passa nella fase B solo se è il numero totale di direttori totali è strettamente maggiore di N.

In questa fase B, il programma deve chiedere all’utente un numero X compreso fra 1 e N: quindi si deve selezionare il
direttorio corrispondente al numero X specificato dall’utente e di tale direttorio si deve riportare su standard
output il nome assoluto (*) e la prima linea di tutti i file leggibili il cui nome abbia terminazione .S.

**NOTA BENE:** Per svolgere la fase B si può sia reinvocare il file comandi ricorsivo **FCR.sh** sia prevedere una
soluzione alternativa.

LO STUDENTE DEVE RIPORTARE IN MODO CHIARO IN UN COMMENTO QUALE DELLE DUE ALTERNATIVE HA SEGUITO.

(*) Precisazione detta durante lo svolgimento della prova!