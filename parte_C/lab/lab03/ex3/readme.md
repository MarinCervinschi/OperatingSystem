### EX 3
Con un editor, scrivere un programma in C **myGrepConFork-ridStError.c** che, partendo dal
programma myGrepConFork.c* mostrato a lezione (disponibile su GITHUB), vada non solo ad
implementare la ridirezione dello standard output ma anche quella dello standard error (sempre su
/dev/null), in modo che se, ad esempio, si passa il nome di un file che non esiste non si abbia una stampa
a video dell’errore come invece si verificava con myGrepConFork.c, ma solo un riscontro dell’errore
nel valore tornato al padre. 

Si verifichi il funzionamento con un numero scorretto di parametri e poi
passando dei parametri in modo da provare i casi visti a lezione per il funzionamento di
myGrepConFork.c.