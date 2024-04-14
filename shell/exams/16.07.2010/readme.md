# 16/07/2010
La parte in Shell deve prevedere **3 parametri:**
- il primo deve essere il **nome assoluto di un direttorio** che identifica una gerarchia (G) all’interno del file system;
- il secondo deve essere il **nome relativo semplice di un direttorio (D)**;
- il terzo parametro deve essere considerato **un numero intero strettamente positivo (H)**.

Il programma deve cercare nella gerarchia G specificata tutti i direttori di nome D che contengono almeno un
file che abbia un numero di linee uguale a H. Si riporti il nome assoluto di tali direttori sullo standard output.

In ognuno di tali direttori trovati, si deve invocare la parte in C, passando come parametri i nomi dei file
trovati (F0, F1, ... FN-1) che soddisfano la condizione precedente e il numero intero H.