### EX 2
Con un editor, scrivere un programma C **pipe-SenzaClose.c** che, partendo dal programma
pipe.c mostrato a lezione (disponibile su GITHUB), elimini nel figlio la chiusura del lato di lettura della
pipe ed elimini nel padre la chiusura del lato di scrittura della pipe. 

Verificare, quindi, che la mancanza delle chiusure dei lati delle pipe non utilizzati porta a un comportamento scorretto, cioè ad un
DEADLOCK che sarà risolvibile solo abortendo l’esecuzione dei due processi con un ^C!