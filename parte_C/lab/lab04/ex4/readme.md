### EX 4
Con un editor, scrivere un programma C **pipe-Generico2.c** che, partendo sempre dal programma
pipe.c, deve andare a considerare però un ulteriore protocollo di comunicazione: in particolare, il
figlio, dopo aver letto una linea (sempre supposta non più lunga di 512 caratteri compreso il terminatore
di linea) dal file passato come parametro e averla trasformata in stringa (come nel programma originale),
deve mandare direttamente la stringa al padre (come nell’esercizio originale - si consideri però
l’OSSERVAZIONE 4 precedente!); 

quindi il padre, poiché diversamente dall’esercizio originale e dal precedente esercizio, NON conosce la lunghezza delle singole stringhe inviate dal figlio, deve ricevere via via i singoli caratteri inviati dal figlio fino al terminatore di stringa e poi (solo dopo aver ricevuto TUTTA la stringa, dato che deve incrementare il contatore delle stringhe ricevute) deve stampare la stringa corrente
e così via per ogni stringa inviata dal figlio, analogamente al programma originale.

**OSSERVAZIONE:** Si segnala che lo stesso schema usato per leggere una linea da un file da parte del figlio
si deve analogamente usare nel padre per andare a leggere un carattere alla volta dalla pipe, dato che si
deve cercare il carattere '\0', salvando i caratteri nel buffer mess (di lunghezza 512, come specificato nel
testo) e quindi il modo più furbo per farlo è questo:
```c
while (read(piped[0], &(mess[L]), 1) != 0)
```
supponendo sempre che L sia l’indice, inizializzato a 0, che serve per inserire i singoli caratteri nel buffer mess.