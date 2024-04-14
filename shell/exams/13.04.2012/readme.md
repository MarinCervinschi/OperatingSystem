# 13/04/2012
La parte in Shell deve prevedere **un solo parametro**:
- deve essere il **nome assoluto di un direttorio** che identifica una gerarchia (G) all’interno del file system.

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in due fasi (Fasi A e B).
Il programma nella fase A deve esplorare la gerarchia G specificata - tramite un file comandi ricorsivo, **FCR.sh** - e
deve contare globalmente i livelli di cui è costituita la gerarchia G (inclusa la radice).

Al termine dell’intera esplorazione ricorsiva di G, si deve riportare sullo standard output il numero di livelli
totali della gerarchia G. Quindi il programma passa nella fase B. In questa fase B, il programma deve chiedere
all’utente un numero pari compreso fra 1 e il numero di livelli totali calcolati nella faseA: quindi si deve
reinvocare **FCR.sh** in modo da cercare nella gerarchia G specificata (inclusa la radice) tutti i direttori che si trovano
al livello corrispondente al numero pari specificato dall’utente e per ognuno di essi si devono visualizzare
**TUTTE**le informazioni associate agli elementi presenti **esclusi i file nascosti**.

**NOTA BENE:** FCR dovrà prevedere dei parametri ulteriori per differenziare l'esecuzione delle diverse Fasi.