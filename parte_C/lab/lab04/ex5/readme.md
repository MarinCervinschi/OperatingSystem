### EX 5
Con un editor, scrivere un programma C **provaEsame1.c** che deve prevedere un numero variabile
N di parametri (con N maggiore o uguale a 2, da controllare) che rappresentano nomi di file (F1, F2. ...
FN). 

Il processo padre deve generare N processi figli (P0, P1, … PN-1): i processi figli Pi (con i che varia
da 0 a N-1) sono associati agli N file Ff (con f = i+1). Ogni processo figlio Pi esegue in modo concorrente
e deve leggere dal proprio file associato, comunicando al padre una selezione dei caratteri letti: in
particolare, i processi associati ai file dispari (F1, F3, ...) devono selezionare solo i caratteri alfabetici,
mentre quelli associati ai file pari (F2, F4, ...) solo i caratteri numerici. 

Il padre deve scrivere i caratteri ricevuti dai figli su standard output, alternando un carattere alfabetico e uno numerico, chiaramente fino a che l’alternanza può essere mantenuta, ma comunque tutti i caratteri ricevuti devono essere scritti
sullo standard output. Una volta ricevuti tutti i caratteri, il padre deve stampare su standard output il
numero totale di caratteri ricevuti e, quindi, scritti sullo standard output. Al termine, ogni processo figlio
Pi deve ritornare al padre l’ultimo carattere letto dal proprio file associato. Il padre deve stampare, su
standard output, i pid di ogni figlio con il corrispondente valore ritornato.

**OSSERVAZIONE:** Vista la specifica di questo testo, la cosa più semplice è definire due pipe: per ottenere
un codice ‘compatto’, si suggerisce di usare un array statico di 2 pipe e quindi `int p[2][2]`; 
la pipe `p[0]` può essere usata per la comunicazione fra i processi (dispari) che leggono dai file pari ed inviano
caratteri numerici al padre, mentre la pipe `p[1]` può essere usata per la comunicazione fra i processi
(pari) che leggono dai file dispari e inviano caratteri alfabetici al padre. 

**N.B.** Si può scegliere anche la semantica invertita: l’importante è selezionare la pipe giusta quando si devono chiudere i lati che non si usano e si deve inviare al padre!

**ATTENZIONE:** la stampa fatta dal padre del valore tornato dal figlio deve considerare che il figlio torna
un char! Si consiglia di aggiungere anche la stampa del valore tornato come int per intercettare
eventuali errori.