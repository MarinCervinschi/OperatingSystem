### EX 3
Con un editor, scrivere un programma C **pipe-Generico1.c** che, partendo sempre dal programma
pipe.c, deve andare a considerare però un diverso protocollo di comunicazione: in particolare deve
essere previsto che il figlio invii al padre stringhe di lunghezza generica e che il figlio, dopo aver letto una
linea (supposta non più lunga di 512 caratteri compreso il terminatore di linea) dal file passato come
parametro e averla trasformata in stringa (come nel programma originale), deve mandare al padre per
prima cosa la lunghezza della stringa, compreso il terminatore, e poi deve mandare la stringa; 

quindi il padre, per ogni linea letta dal figlio, riceve per prima cosa la lunghezza della stringa e poi deve usare
questa informazione per leggere il numero di caratteri che costituiscono la stringa; chiaramente, il padre
alla fine deve stampare via via le stringhe ricevute, analogamente al programma originale. 

Verificarne il funzionamento 
- i) con un numero di parametri sbagliato;
- ii) con un numero di parametri giusto, ma file non esistente;
- iii) con un numero di parametri giusto e file esistente; 

in particolare, si verifichi il funzionamento sia con i file usati per la verifica del programma pipe.c (input.txt e
input1.txt, entrambi disponibili su GITHUB) che, chiaramente, con almeno un file che presenta
lunghezze di linee NON fisse e NON note a priori!

**OSSERVAZIONE 1:** Si ricorda che il figlio, per leggere una linea da un file, deve leggere un carattere alla
volta, dato che si deve cercare il carattere '\n', salvando i caratteri nel buffer mess (di lunghezza 512,
come specificato nel testo) e quindi il modo più furbo per farlo è questo:
while (read (fd, &(mess[L]), 1) != 0) supponendo che L sia l’indice, inizializzato
a 0, che serve per inserire i singoli caratteri nel buffer mess.

**OSSERVAZIONE 2:** L’indice L, incrementato di 1 (dato che si deve mandare la lunghezza della stringa,
compreso il terminatore) deve essere la prima informazione inviata al padre.

**OSSERVAZIONE 3:** Per l’invio di queste due informazioni (lunghezza della stringa, rappresentata da L, e
stringa, rappresentata da mess) si DEVE usare la stessa pipe e NON se ne deve creare un’altra!

**OSSERVAZIONE 4:** Per l’invio della stringa rappresentata da mess si DEVE fare attenzione ad usare nella
write il valore di L che rappresenta appunto la lunghezza della stringa, compreso il terminatore!