
# Lab 02 - 14/03/2024 *SHELL*

What did you learn while building this project? What challenges did you face and how did you overcome them?

## RIDIREZIONE A VUOTO
**1) Usando la sola ridirezione dello standard output, azzerare un file precedentemente creato (nel caso il
contenuto sia importante farne prima una copia, casomai preservando i timestamps!)**
```shell
    cp -p file filedicopia
```
```shell
    > filedicopia
```
**2) Usando la sola ridirezione dello standard output, creare un file con un nome non esistente nella directory di
sistema tmp.**
```shell
  cd /
```
```shell
  > /tmp/file
```
## SORT
**3) Per questo esercizio usare il file di nome prova (quello creato nella precedente esercitazione), ma prima di
usarlo controllare che ci siano più parole in ogni linea e, in caso contrario, editare prima il file per fare in modo
appunto di avere più parole in ogni linea. Quindi. usando la ridirezione dello standard input e il comando-filtro
sort, verificare se il file di nome prova è ordinato alfabeticamente.**
```shell
  sort -C < prova
```
```shell
  echo $?
```
**4) Usando la ridirezione dello standard input e il comando-filtro sort, mostrare il contenuto del file prova ordinato
secondo il normale ordinamento alfabetico.**
```shell
  sort < prova
```
**5) Usando la ridirezione dello standard input e il comando-filtro sort, mostrare il contenuto del file prova ordinato
invertendo il normale ordinamento alfabetico.**
```shell
  sort -r < prova
```
**6) Per questo esercizio usare sempre il file di nome prova (come per il punto 3), ma prima di usarlo controllare
che ci siano più parole all’inizio di alcune linee che inizino sia con lettera maiuscola che minuscola, in caso
contrario, editare prima il file per fare in modo appunto di avere il formato sopra indicato. Quindi, usando la
ridirezione dello standard input e il comando-filtro sort, mostrare il contenuto del file prova ordinato secondo
il normale ordinamento alfabetico, ma ignorando la differenza fra maiuscole e minuscole.**
```shell
  sort -f < prova
```
**7) Usando la ridirezione dello standard input e il comando-filtro sort, mostrare il contenuto del file prova ordinato
secondo il normale ordinamento alfabetico (come nel punto 4), ma ridirigendo lo standard output su un file di
nome ordinato.**
```shell
  sort < prova > ordinato
```
**8) Usando la ridirezione dello standard input e il comando-filtro sort, verificare se il file di nome ordinato
(ottenuto con il precedente esercizio) è ordinato alfabeticamente, in modo analogo a quanto fatto nel punto
3) sul file di nome prova.**
```shell
  sort -C < ordinato
```
```shell
  echo $?
```
**9) Per questo esercizio usare sempre il file di nome prova (come per il punto 3 e 6), ma prima di usarlo controllare
che ci siano più righe duplicate o triplicate, in caso contrario, editare prima il file per fare in modo appunto di
avere il formato sopra indicato. Quindi, usando la ridirezione dello standard input e il comando-filtro sort,
mostrare il contenuto del file prova ordinato, ma attuando l’ordinamento alfabetico senza replicazioni e
scrivendo lo standard output su un file di nome ordinato-senza-doppi.**
```shell
  sort -u < prova > ordinato-senza-doppi
```
**10) Facendo riferimento ad uno qualunque degli esercizi precedenti sul comando-filtro SORT (anche per tutti),
provare anche la versione comando SORT e quindi senza ridirezione dello standard input! Attenzione però che
per produrre dei risultati che vanno salvati, come nel punto 9) (ma anche in altri), la ridirezione dello standard
output invece va usata.**
```shell
  SORT -uf prova > prova-di-SORT
```
## GREP
**11) Usando la ridirezione dello standard input e il comando-filtro grep, cercare nel file ordinato-senza-doppi le
linee che contengono una certa stringa (o anche un semplice carattere).**
```shell
  grep riga < ordinato-senza-doppi
```
**12) Usando la ridirezione dello standard input e il comando-filtro grep, cercare nel file ordinato-senza-doppi le
linee che contengono una certa stringa (o anche un semplice carattere), come fatto precedentemente,
mostrando anche i numeri di linea.**
```shell
  grep -n riga < ordianto-senza-doppi
```
**13) Assicurandosi di avere nel file ordinato-senza-doppi la stessa stringa scritta in maiuscola e in maiuscolo almeno
2-3 volte (altrimenti modificare il file in tal senso), usando la ridirezione dello standard input e il comando-
filtro grep, cercare nel file ordinato-senza-doppi le linee che contengono una certa stringa (o anche un
semplice carattere) ignorando maiuscole/minuscole.**
```shell
  grep -i riga < ordinato
```
**14) Usando la ridirezione dello standard input e il comando-filtro grep, cercare nel file ordinato-senza-doppi le
linee che NON contengono una certa stringa (o anche un semplice carattere).**
```shell
  grep -v riga < ordinato-senza-spazi
```
**15) Usando la ridirezione dello standard input e il comando-filtro grep, cercare nel file ordinato-senza-doppi le
linee che INIZIANO per una certa stringa (o anche un semplice carattere).**
```shell
  grep ^q < ordinato-senza-spazi
```
**16) Usando la ridirezione dello standard input e il comando-filtro grep, cercare nel file ordinato-senza-doppi le
linee che TERMINANO per una certa stringa (o anche un semplice carattere).**
```shell
  grep a$ < ordianto-senza-spazi
```
**17) Assicurandosi di avere nel file ordinato-senza-doppi almeno una linea che termina per il carattere ‘.’ (PUNTO)
(altrimenti modificare il file in tal senso), usando la ridirezione dello standard input e il comando-filtro grep,
cercare nel file ordinato-senza-doppi le linee che TERMINANO per il carattere ‘.’ (PUNTO).**
```shell
  grep "\.$" < ordinato-senza-spazi
```
**18) Utilizzando la soluzione di uno degli esercizi precedenti sul GREP, ridirigere lo standard output in un file di
nome prova-grep.**
```shell
  grep ^q < ordinato-senza-spazi > prova-grep
```
**19) Facendo riferimento ad uno qualunque degli esercizi precedenti sul comando-filtro GREP (anche per tutti),
provare anche la versione comando GREP e quindi senza ridirezione dello standard input! ! Attenzione però
che per produrre dei risultati che vanno salvati, come nel punto 18), la ridirezione dello standard output invece
va usata.**
```shell
  GREP "\.$" ordinato-senza-spazi > prova-grep-2
```
## WC
**20) Usando la ridirezione dello standard input e il comando-filtro wc, contare le linee del file p.txt (quello creato
nella precedente esercitazione).**
```shell
    wc -l < p.txt
```
**21) Usando la ridirezione dello standard input e il comando-filtro wc, contare i caratteri del file p.txt.**
```shell
    wc -c < p.txt
```
**22) Usando la ridirezione dello standard input e il comando-filtro wc, contare le parole del file p.txt.**
```shell
    wc -w < p.txt
```
**23) Verificare che cosa cambia nell’output dei precedenti 3 esercizi se invece che il comando-filtro wc si usa il
comando wc!**
```shell
    wc -l p.txt
```
```
    [ viene riportato anche il nome del file ]
```
**24) Usando il comando wc su un file di nome pippo (che non deve esistere) e ridirigendo lo standard error su
/dev/null, verificare il valore di ritorno del comando.**
```shell
    wc -l pippo 2> /dev/null
```
```shell
    echo $?
```
**25) Utilizzando il comando ps in piping con il filtro tee temp e in piping con wc –l, verificare: a) il numero
visualizzato; b) il contenuto del file di nome temp creato dal filtro tee (supponendo di non avere lanciato alcun
comando in background!).**
```shell
    ps | tee temp | wc -l
```
```
    4
```
```
      PID TTY           TIME CMD
    68853 ttys000    0:00.76 -zsh
    69939 ttys000    0:00.00 tee temp
    69940 ttys000    0:00.00 wc -l
```
## HEAD e TAIL
**26) Usando la ridirezione dello standard input e il comando-filtro head, selezionare le prime 10 linee del file p.txt
(quello creato nella precedente esercitazione).**
```shell
    head < p.txt
```
**27) Usando la ridirezione dello standard input e il comando-filtro head, selezionare la prima linea del file p.txt.**
```shell
    head -1 < p.txt
```
**28) Usando la ridirezione dello standard input e il comando-filtro head, selezionare le prime 3 linee del file p.txt.**
```shell
    head -3 < p.txt
```
**29) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare le ultime 10 linee del file p.txt.**
```shell
    tail < p.txt
```
**30) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare l’ultima linea del file p.txt.**
```shell
    tai -1 < p.txt
```
**31) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare le ultime 3 linee del file p.txt.**
```shell
    tail -3 < p.txt
```
**32) Utilizzando la soluzione di uno degli esercizi precedenti su HEAD e TAIL, ridirigere lo standard output in un file
di nome prova-head o prova-tail a seconda dei casi.**
```shell
    tail -3 < p.txt > prova-head
```
**33) Facendo riferimento ad uno qualunque degli esercizi precedenti sui comandi-filtro HEAD e TAIL (anche per
tutti), provare anche le versioni comando HEAD e TAIL e quindi senza ridirezione dello standard input!
Attenzione però che per produrre dei risultati che vanno salvati, come nel punto 32), la ridirezione dello
standard output invece va usata.**
```shell
    HEAD p.txt > prova-head
```
**34) Utilizzando il piping dei comandi, isolare in un file di nome p.txt.terza la terza linea a partire dall’inizio del file
p.txt.**
```shell
    head -3 p.txt | cat > p.txt.terza
```
**35) Utilizzando il piping dei comandi, isolare in un file di nome p.txt.terzultima la terza linea a partire dalla fine del
file p.txt.**
```shell
    tail -3 p.txt | cat > p.txt.terzultima
```
## REV
**36) Usando la ridirezione dello standard input e il comando-filtro rev, verificarne il funzionamento su almeno uno
dei file a disposizione.**
```shell
    rev < p.txt 
```
## METACARATTERI [e]
**37) Utilizzando esclusivamente la ridirezione a vuoto, creare diversi file con nomi che iniziano e terminano con
varie lettere dell’alfabeto maiuscole e minuscole e con numeri; creare anche un paio di directory con
l’opportuno comando. Verificare quindi il comportamento dei comandi:**
- a) echo [a-z]*
- b) echo [A-Z]*
- c) echo [0-9]*
- d) echo *[a-z]
- e) echo *[A-Z]
- f) echo *[0-9]**
```shell
    echo [a-z]*
```
**38) Rifare i comandi precedenti usando la negazione: ad esempio per a) echo [!a-z]***
```shell
    echo [!a-z]
```
**39) Utilizzare nuovamente i pattern precedenti utilizzando però il comando ls –l: che cosa cambia?**
```shell
    ls - [a-z]* 
```
## VARIABILI DI SHELL E DI AMBIENTE
**40) Memorizzare in una variabile di shell di nome a un valore scelto a proprio piacimento, quindi provare ad
eseguire il file comandi prova.sh visto a lezione (scaricabile da GITHUB). Quale è il risultato?**
```shell
    a=10
```
```shell
    ./prova.sh
```
```
    Il valore della variabile a è
    Il valore del comando PATH               /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    Il valore del comando HOME /Users/marin
```
**41) Rendere la variabile a variabile di ambiente e riprovare ad eseguire prova.sh. Quale è il risultato?**
```shell
    export a
```
```
    Il valore della variabile a è 10
    Il valore del comando PATH               /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    Il valore del comando HOME /Users/marin
```
**42) Verificare con il comando env, la presenza della variabile a nell’ambiente.**
```shell
    env
```
**43) Provare ad eseguire il file comandi prova1.sh visto a lezione (scaricabile da GITHUB). Quale è il risultato?**
```shell
    ./prova1.sh
```
```
    Il valore della variabile a è 10
    Il valore del commando PATH     /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    Il valore del commando HOME /Users/marin
    Il valore della variabile a ora è hello
```
**44) Verificare il valore della variabile a nella shell di partenza.**
```shell
    echo $a
```
**45) Provare ad eseguire il file comandi prova1.sh visto a lezione (scaricabile da GITHUB) usando sh -x. Quale è
il risultato?**
```shell
    sh -x prova1.sh
```
```
    + echo Il valore della variabile a è 10
    Il valore della variabile a è 10
    + echo Il valore del commando PATH /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    Il valore del commando PATH     /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    + echo Il valore del commando HOME /Users/marin
    Il valore del commando HOME /Users/marin
    + a=hello
    + echo Il valore della variabile a ora è hello
    Il valore della variabile a ora è hello
```
**46) Provare ad eseguire il file comandi provacomandi.sh visto a lezione (scaricabile da GITHUB). Quale è il
risultato?**
```shell
    ./provacomandi.sh
```
```
    SONO UN ALTRO ESEMPIO SEMPLICE DI FILE COMANDI
    La directory di partenza quindi la HOME directory
    /Users/marin
    la PATH     /opt/homebrew/bin:/opt/homebrew/sbin:/usr/local/bin:/System/Cryptexes/App/usr/bin:/usr/bin:/bin:/usr/sbin:/sbin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/local/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/bin:/var/run/com.apple.security.cryptexd/codex.system/bootstrap/usr/appleinternal/bin:/Library/Apple/usr/bin
    La PATH /
    La directory corrente
    /Users/marin/Documents/UNIMORE 2^anno/SISTEMI OPERATIVI/shell/mer.13.03.2024
    Ho cambiato directory
    La directory corrente
    /Users/marin/Documents/UNIMORE 2^anno/SISTEMI OPERATIVI/shell
    Verifica dove ti trovi dopo avermi eseguito e verifica anche il valore di PATH
```
**47) Verificare il valore della directory corrente e della variabile PATH nella shell di partenza.**
```shell
    pwd
```
```shell
    echo $PATH
```
**48) Memorizzare in una variabile di shell di nome x, il numero di linee del file p.txt e quindi visualizzarne il valore.**
```shell
    x=`wc -l p.txt`
```
```shell
    echo $x
```
**49) Memorizzare in una variabile di shell di nome y, il numero di linee del file prova e quindi visualizzarne il valore.**
```shell
    y=`wc -l prova`
```
```shell
    echo $y
```
**50) Memorizzare in una variabile di shell di nome z, la somma della variabile x e della variabile y e visualizzarne il
valore. Provare anche ad effettuare tutte le altre operazioni aritmetiche e quindi sottrazione, moltiplicazione,
divisione intera e resto intero della divisione!**
```shell
    z=`expr $x + $y`
```
```shell
    echo $z
```
**51) Con un editor, scrivere un file comandi prova-variabili.sh che visualizzi il valore delle variabili di shell x, y e z
inserendo anche dei commenti significativi. Rendere eseguibile tale file comandi (verificare che sia eseguibile
con ls –l prova-variabili.sh) e mandarlo in esecuzione. Quale è il risultato?**
```shell
    #!/bin/zsh
    echo Il valore della variabile x = $x
    echo Il valore della variabile y = $y
    echo Il valore della variabile z = $z
```
```shell
    chmod u+x prova-variabili.sh
```
```shell
    ls -l prova-variabili.sh
```
```shell
    ./prova-variabili.sh
```
**52) Rendere le variabili x, y e z variabili di ambiente e riprovare ad eseguire prova-variabili.sh. Quale è il risultato?**
```shell
    export x y z
```
```shell
   ./prova-variabili.sh
```
**53) Verificare con il comando env, la presenza di x, y e z nell’ambiente.**
```shell
    env
```
**54) Copiare il file comandi prova-variabili.sh nel file comandi di nome prova-variabili-bis.sh, quindi aggiungere in
fondo un comando che modifica il valore della variabile z e un comando che visualizza nuovamente il valore,
sempre inserendo commenti significativi. Provare ad eseguire prova-variabili-bis.sh. Quale è il risultato? Quale
valore ha la variabile z nella shell interattiva di partenza?**
```shell
    cp prova-variabili.sh prova-variabili-bis.sh
```
```shell
    z=5
    echo Il nuovo valore della variabile z = $z
```
