
# Lab 02 - 14/03/2024 *SHELL*

What did you learn while building this project? What challenges did you face and how did you overcome them?

## RIDIREZIONE A VUOTO
**1) Usando la sola ridirezione dello standard output, azzerare un file precedentemente creato (nel caso il
contenuto sia importante farne prima una copia, casomai preservando i timestamps!)**
```shell
    cp -p file filedicopia
```
```shell
    cat > filedicopia
```
**2) Usando la sola ridirezione dello standard output, creare un file con un nome non esistente nella directory di
sistema tmp.**
```shell
  cd /
```
```shell
  cat > /tmp/file
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
    wc -m < p.txt
```
**22) Usando la ridirezione dello standard input e il comando-filtro wc, contare le parole del file p.txt.**
```shell
    wc -w < p.txt
```
**23) Verificare che cosa cambia nell’output dei precedenti 3 esercizi se invece che il comando-filtro wc si usa il
comando wc!**
```shell
    error
```
**24) Usando il comando wc su un file di nome pippo (che non deve esistere) e ridirigendo lo standard error su
/dev/null, verificare il valore di ritorno del comando.**
```shell
    wc pippo > /dev/null >&1
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

```
**27) Usando la ridirezione dello standard input e il comando-filtro head, selezionare la prima linea del file p.txt.**
```shell

```
**28) Usando la ridirezione dello standard input e il comando-filtro head, selezionare le prime 3 linee del file p.txt.**
```shell

```
**29) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare le ultime 10 linee del file p.txt.**
```shell

```
**30) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare l’ultima linea del file p.txt.**
```shell

```
**31) Usando la ridirezione dello standard input e il comando-filtro tail, selezionare le ultime 3 linee del file p.txt.**
```shell

```
**32) Utilizzando la soluzione di uno degli esercizi precedenti su HEAD e TAIL, ridirigere lo standard output in un file
di nome prova-head o prova-tail a seconda dei casi.**
```shell

```
**33) Facendo riferimento ad uno qualunque degli esercizi precedenti sui comandi-filtro HEAD e TAIL (anche per
tutti), provare anche le versioni comando HEAD e TAIL e quindi senza ridirezione dello standard input!
Attenzione però che per produrre dei risultati che vanno salvati, come nel punto 32), la ridirezione dello
standard output invece va usata.**
```shell

```
**34) Utilizzando il piping dei comandi, isolare in un file di nome p.txt.terza la terza linea a partire dall’inizio del file
p.txt.**
```shell

```
**35) Utilizzando il piping dei comandi, isolare in un file di nome p.txt.terzultima la terza linea a partire dalla fine del
file p.txt.**
```shell

```
## REV
**36) Usando la ridirezione dello standard input e il comando-filtro rev, verificarne il funzionamento su almeno uno
dei file a disposizione.**
```shell

```
## METACARATTERI [e]
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```
****
```shell

```


