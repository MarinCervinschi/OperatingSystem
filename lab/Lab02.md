
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


