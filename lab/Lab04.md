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
  ln -s file2 provaDir/provaLinkSoftware 
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
  ps
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
## PARTE SHELL DI TESTI DI ESAMI
**OSSERVAZIONE: Per tutti i testi che NON sono di una prima prova in itinere, ma di un compito completo, al posto della
invocazione della parte C, si inserisca un echo che illustri con quali parametri andrebbe invocata la parte C!**
### a) TESTO PARTE SHELL DELL’ESAME DEL 15 FEBBRAIO 2017
**La parte in Shell deve prevedere due parametri:** 
- il primo deve essere il nome assoluto di una directory che
identifica una gerarchia (G) all’interno del file system;
- il secondo parametro deve essere considerato un numero
intero X strettamente positivo.

**Il programma deve cercare nella gerarchia G specificata tutte le directory che
contengono almeno un file leggibile con lunghezza in linee pari X e il cui contenuto del file sia tale per cui tutte le
sue linee contengano almeno un carattere numerico.**

**Si riporti il nome assoluto di tali directory sullo standard
output e quindi i nomi di tutti i file trovati (F1, F2, … FN). Quindi in ogni directory trovata, chiesta conferma
all’utente, si deve invocare la parte in C, passando come parametri i nomi dei file trovati (F1, F2, … FN) e la loro
lunghezza in linee X.**
```shell
  nv FCP.sh
```
```shell
#!/bin/zsh
#File FCP.sh

# controllo del numero di parametri
if test $# -ne 2
then
        echo ERROR: Usage is: $0 [/directory] [number > 0]
        exit 1
fi

# controllo il nome assoluto del primo parametro
case $1 in
/*)     ;;
*/*)    echo ERROR: $1 non in forma assoluta
        exit 2;;
esac

# controllo il valore del secondo parametro, deve essere strettamente maggiore di zero
if test $2 -le 0
then
        echo ERROR: $2 deve essere maggiore di 0
        exit 3
fi

# chiamo G il nome assoluto della directory e X il numero strettamente maggiore di zero
G=$1
X=$2

PATH=`pwd`:$PATH
export PATH
./FCR.sh $G $X
echo HO FINITO TUTTO
```
```shell
  nv FCR.sh
```
```shell
#!/bin/zsh
#File FCR.sh

G=$1
X=$2

# mi sposto nella directory passata come parametro
cd $G

count=0
FILES=

# esploro da directory corrente
for i in *
do
        # cerco file leggibile
        if test -f $i -a -r $i
        then
                # controllo la lunghezza in linee
                n=`wc -l < $i`

                if test $n -eq $X
                then
                        # controllo che ogni riga contenga almeno un numero
                        if ! grep -q -v '[0-9]' $i
                        then
                                count=`expr $count + 1`
                                FILE="$FILES $i"
                        fi
                fi
        fi
done

if test $count -gt 0
then
        echo La directory `pwd` contiene $count files
        echo $FILES
fi

echo "main.c $FILES $X"

# la chiamata ricorsiva per proseguire
for i in *
do
        # se directory traversabile
        if test -d $i -a -x $i
        then
                ./FCR.sh `pwd`/$i $X
        fi
done
```
```shell
  chmod u+x FCP.sh FCR.sh
```
```shell
  ./FCP.sh /files 5
```
```shell

```
```shell

```
```shell

```
```shell

```
```shell

```
```shell

```
```shell

```
```shell

```
