# Lab 04 - 28/03/2024 *SHELL*
## LN (seguito)

**1) Creare una sottodirectory di nome provaDirBis nella propria HOME directory; verificare il numero di link
della sottodirectory creata; creare con un editor almeno un file in tale sottodirectory; usare i nomi assoluti dei
vari link della sottodirectory creata per visualizzarne il contenuto; cancellare la sottodirectory.**
```shell
  mkdir provaDirBis
```
```shell
  ls -lid provaDirBis
```
```
  [ 49340193 drwxr-xr-x  2 marin  staff  64 Apr  2 10:37 provaDirBis/ ]
```
```shell
  nv provaDirBis/file1
```
```shell
  cat ~/provaDirBis/file1
```
```shell
  rm -r provaDirBis
```
**2) Creare un link SOFTWARE di nome provaLinkSoftware per un file della propria HOME directory nella
sottodirectory provaDir (creata la scorsa esercitazione); verificare il numero di link, le proprietà del link
software e il suo uso.**
```shell
  ls -li file2
```
```
  [ 49341948 -rw-r--r--  1 marin  staff  20 Apr  2 10:51 file2 ]
```
```shell
  ln -s /Users/marin/file2 provaDir/provaLinkSoftware 
```
```shell
  ls -li provaDir/
```
```
  [ 49342382 lrwxr-xr-x  1 marin  staff  5 Apr  2 10:54 provaLinkSoftware -> file2 ]
```
**3) Cancellare (casomai dopo averne fatta una copia, se il contenuto è importante) il file della propria HOME
directory usato come sorgente del link SOFTWARE; verificare cosa succede ad usare il link SOFTWARE.**
```shell
  rm file2
```
```
  il link non riesce a trovare il file originale
```
**4) Dopo aver ricreato il file sorgente del link SOFTWARE, cancellare a questo punto il link SOFTWARE e verificare
che il file sorgente continui ad essere accessibile.**
```shell
  rm -r provaDir/
```
```shell
  cat file2
```
```
  NO Error
```
**5) Provare a creare un link HARDWARE di nome provaLinkDir, nella propria HOME directory, per la
sottodirectory provaDir: il comando ha successo?**
```shell
  ln provaDir ~/provaLinkDir
```
```
  [ ln: provaDir: Is a directory ]
```
**6) Dopo aver creato una sottodirectory di nome linkSw nella propria HOME directory, provare a creare un link
SOFTWARE di nome provaLinkDir per la sottodirectory provaDir nella nuova sottodirectory: il
comando ha successo?**
```shell
  mkdir linkSw
```
```shell
  ln -s provaDir linkSw/provaLinkDir
```
```
  Successo
```
```shell
  ls -li provaDir/
```
```
  [ 49344846 lrwxr-xr-x  1 marin  staff  4 Apr  2 11:10 provaLinkDir -> provaDir ]
```
## ESECUZIONE IN BACKGROUND
**7) Mandare in esecuzione con le opportune ridirezioni di standard output e di standard error il comando ls -lR /
usando l’esecuzione in background.**
```shell
  ls -lR / > output.txt 2> error.txt &
```
```
  [ [1] 35531 ]
```
```shell
  cat < output.txt
```
```shell
  cat < error.txt
```
**8) Verificare i processi attivi nella sessione prima che finisca il comando lanciato in background.**
```shell
  ps -lf
```
```
  PID TTY           TIME CMD
31108 ttys000    0:00.97 -zsh 
35531 ttys000    2:07.65 ls -lR /
```
```shell
  kill 35531
```
```
  [1]  + terminated  ls -lR / > output.txt 2> error.txt
```
## DATE
**9) Verificare la data (e l’ora corrente).**
```shell
  date
```
## DIFF
**10) Creare, con un editor oppure con la ridirezione dello standard output usando il comando-filtro cat, un file che
contenga almeno 5 o 6 linee; crearne una copia e quindi verificare il funzionamento del comando diff
utilizzando i due file prodotti.**
```shell
  nv provaDiff1
```
```
pippo
pluto
paperino
```
```shell
  cp -p provaDiff1 provaDiff2
```
```shell
  diff provaDiff1 provaDiff2
```
```
  No output
```
**11) Modificare con un editor alcune parti di uno dei due file precedentemente creati; quindi, verificare di nuovo
il funzionamento del comando diff utilizzando i due file prodotti.**
```shell
  nv provaDiff1
```
```
pluto
paperino
```
```shell
  diff provaDiff1 provaDiff2
```
```
    0a1
  > pippo
```