# EX 7
Con un editor, scrivere un programma in C **selezionaMultipli.c** che deve essere invocato esattamente con **2 parametri**: 
- il primo deve essere considerato il **nome di un file F**;
- il secondo un **numero intero n strettamente positivo**. 

Dopo aver fatto tutti i controlli necessari (sul numero dei parametri e sul loro ‘tipo’), si visualizzi su standard
output tutti i caratteri del file F che si trovano in posizione multipla di n insieme con l’indicazione del numero di tale
multiplo (ad esempio scrivendo su standard output “Il carattere multiplo x-esimo all'interno del file XXX e' y” dove x
è il numero del multiplo, XXX il nome del file e y è il carattere). 

Si verifichi il funzionamento.

**OSSERVAZIONE:** Questo esercizio può essere risolto in due modi:
- a) La lettura può avvenire a multipli di n (quindi via via una lettura di n caratteri in una volta sola!) e tutte le volte
che si riescono a leggere n caratteri si riporta sullo standard output appunto l’n-esimo carattere. 
    - **N.B.** In questo caso bisogna allocare dinamicamente un array di n caratteri (NON SI POSSONO USARE I VARIABLE LENGHT
ARRAY!) e controllare l’avvenuta creazione!
        - ➔ questa versione la si chiami **selezionaMultipli1.c**
- b) Dopo aver calcolato la lunghezza in caratteri del file utilizzando la primitiva lseek, si può impostare un ciclo
all’interno del quale si va a calcolare la posizione multipla di n a cui spostarsi e, se questa è corretta, sempre con
la primitiva lseek si deve spostare il File Pointer nella posizione giusta e quindi si può leggere direttamente il
singolo carattere cercato! 
    - ➔ questa versione la si chiami **selezionaMultipli2.c**

Si verifichi che i caratteri scritti dalle due versioni siano gli stessi!