### EX 5
Con un editor, scrivere un programma in C **myCatConFork.c** che deve essere invocato esattamente
con 1 parametro che deve essere il nome del file che si vuole visualizzare. Il programma, dopo il controllo
sul numero di parametri, deve creare un processo figlio (come nei due esercizi precedenti). Il processo
figlio, dopo aver implementato la ridirezione dello standard input dal file il cui nome è passato come
parametro, deve invocare il programma mycat -mostrato a lezione (disponibile su GITHUB e che quindi
deve essere scaricato se non già fatto!)- usando una delle primitive della famiglia EXEC. Il padre deve
stampare su standard output il PID del figlio e il valore ritornato. 

Si verifichi il funzionamento con un numero scorretto di parametri e poi passando come parametro nomi di file esistenti e NON esistenti!
**OSSERVAZIONE:** chiaramente un analogo effetto si potrebbe ottenere anche invocando direttamente il
comando-filtro cat, ma si è preferito proporre di invocare mycat per differenziare questo esercizio dai
due esercizi precedenti: in GITHUB sarà comunque caricata anche questa versione denominata
myCatOriginaleConFork.c.