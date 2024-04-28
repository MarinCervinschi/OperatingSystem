# EX 2
Con un editor, scrivere un programma in C **parametri2.c** che deve essere invocato esattamente con **3 parametri**:
- il primo parametro deve essere considerato il nome di un file;
- il secondo un numero intero N strettamente positivo;
- il terzo deve essere considerato un singolo carattere C.

Dopo aver fatto il controllo che il numero dei parametri sia giusto (controllo STRETTO), si devono controllare anche i **‘tipi’** dei parametri: 
- per il controllo che il primo parametro sia il nome di un file si può usare la primitiva `open` in lettura e in caso di insuccesso uscire (come visto negli esercizi
mostrati a lezione); 
- per il controllo che il secondo parametro sia un numero intero si può usare la funzione di libreria
`atoi` e sul valore risultante N verificare che se minore o uguale a 0 uscire;
- per il controllo che il terzo parametro sia un singolo carattere si può scegliere 
    - a) se usare la funzione di libreria `strlen` (in questo caso ricordarsi di includere l’header
file con le funzioni per operare sulle stringhe) e sul valore risultante verificare che se diverso da 1 uscire oppure 
    - b) si può verificare che il secondo carattere della stringa (argv[3][1]) se diverso da ‘\0’ (terminatore di stringa) uscire. 
    
Dopo aver fatto tutti i controlli, si visualizzi su standard output il nome dell’eseguibile e il numero dei parametri (come
nell’esercizio precedente) e, quindi, il valore dei tre parametri (secondo il loro significato) inserendo opportune frasi
che facciano capire all’utente che cosa si sta visualizzando. 

Si verifichi il funzionamento sia in assenza di parametri o con un numero minore di 3 o maggiore di 3 (casi errati) che con il numero giusto di parametri, ma di ‘tipo’ non corretto
(file non esistente, stringa che non corrispondente ad un numero > 0, stringa NON costituita da un solo carattere) e
infine il funzionamento corretto.