# 20/04/2011

La parte in Shell deve prevedere **tre parametri**: 
- il primo deve essere il **nome assoluto di un direttorio** che identifica una gerarchia (G) all’interno del file system;
- il secondo parametro deve essere il **nome relativo semplice** di un file (F)
- il terzo parametro deve essere considerato un **numero intero positivo** (N). 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in generale in tre fasi (Fasi
A, B e C).
Il programma deve cercare nella gerarchia G specificata (inclusa la radice) - tramite un file comandi ricorsivo,
**FCR.sh** - tutti i direttori che contengono un file che ha nome relativo F: si riporti il nome assoluto di tali direttori
sullo standard output e si contino globalmente i file che soddisfano la condizione indicata (Fase A).

Al termine dell’intera esplorazione ricorsiva di G, si deve riportare sullo standard output il numero totale di file
(NF) che soddisfano la condizione indicata. In caso NF sia minore di N, il programma passa alla Fase B: si deve
reinvocare FCR in modo da cercare nella gerarchia G specificata (inclusa la radice) tutti i direttori che NON
contengono un file con nome relativo F, riportando sullo standard output il nome assoluto dei direttori trovati e
creando un file vuoto con nome relativo F all'interno di ognuno.

Quindi, se è stato necessario eseguire la Fase B, si deve passare alla Fase C in cui si deve verificare la situazione
risultante invocando nuovamente FCR come per la Fase A.

**NOTA BENE:** FCR dovrà prevedere un parametro ulteriore rispetto a G, F e N per differenziare l'esecuzione
delle diverse Fasi.