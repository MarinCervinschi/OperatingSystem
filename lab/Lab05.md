# Lab 05 - 04/04/2024 *SHELL*
## 15/04/2015

La parte in Shell deve prevedere un numero variabile di parametri N+1 (N maggiore o uguale a 2): 
- i primi N parametri devono essere nomi assoluti di directory che identificano N gerarchie (G1, G2, …) all’interno del file
system; 
- l’ultimo parametro deve essere considerato un numero intero X strettamente positivo. 

Il comportamento atteso dal programma, dopo il controllo dei parametri, è organizzato in N fasi, una per ogni
gerarchia.
Il programma, per ognuna delle N fasi, deve esplorare la gerarchia Gi corrispondente - tramite un file comandi
ricorsivo, **FCR.sh** - e devono contare globalmente tutte le directory che soddisfano le seguenti due specifiche: 
1) devono contenere solo file (e non sotto-directory)
2) devono contenere solo file la cui lunghezza in linee sia strettamente maggiore di X. 

Al termine di tutte le N fasi, si deve riportare sullo standard output il numero totale
delle directory trovate globalmente che soddisfano la specifica precedente (directory trovate). 

Inoltre, per ogni directory trovata, si deve riportare sullo standard output il suo nome assoluto, e quindi per ognuno dei file (file
corrente) in esso contenuto deve essere riportato sullo standard output il suo nome assoluto e contestualmente
la linea X-esima del file corrente a partire dalla fine del file.
## FCP.sh
```shell
#!/bin/zsh
#File FCP.sh

# controllo sul numero di parametri 
if test $# -lt 2
then
    echo ERROR: $# deve essere maggiore o uguale a 2
    exit 1
fi

# definisco una variabile per salvare l'ultimo parametro
X=
# defininsco una variabile per identificare l'ultimo parametro
count=0
for i
do 
    # controllo i primi N parametri
    count=`expr $count + 1`
    if test $count -ne $#
    then
        #controllo che sia in forma assoluta
        case $i in
        # se in forma assoluta controllo che sia directory e traversabile
        /*) if test ! -d $i -a ! -x $i
            then
                echo ERROR: $i non directory o non attraversabile
                exit 2
            fi;;
        *)  echo ERROR: non in forma assoluta
            exit 3;;
        esac
    else 
        # controllo l'ultimo che deve essere un numero
        expr $i + 0 > /dev/null 2>&1
        N1=$?

        if test $N1 -ne 2 -a $N1 -ne 3 
        then
        	echo numerico $i #siamo sicuri che numerico
        	if test $i -le 0
            then
        		echo $i non strettamente positivo
               	exit 4
            fi
        else
          	echo $i non numerico
          	exit 5
        fi
        X=$i
    fi 
done
#settiamo la variabile PATH e la esportiamo
PATH=`pwd`:$PATH
export PATH

# creo file
touch /tmp/temp 

count=0
#invocazione del file comando ricorsivo
for i
do
    count=`expr $count + 1`
    if test $count -ne $#
    then
        FCR.sh $i $X
    fi
done

# stampo il numero totale di file trovati
n=`wc -l < /tmp/temp | tr -d ' '`
echo HO trovato $n directory che soddisfano le ricchieste

# cancello il file temporaneo per le prox chiamate
rm /tmp/temp
```
## FCR.sh
```shell
#!/bin/zsh
#File FCR.sh

cd $1

for i in *
do
    # se directory vai più in profondità
    if test -d $i -a -x $i
    then
        FCR.sh $i $X
        # se il file non ha riportato errori stampo il nome assoluto della directory con i file al suo interno
        res=$?

        if test $res -eq 0
        then
            # aggiungo una direcory trovata globalmente
            echo "1" >> /tmp/temp
            # stampo il risultato 
            echo Il nome assoluto della directory: `pwd`/$i
            echo Tutti i file trovati
            for file in "$i"/*
            do
                echo `pwd`/$i/$file
                echo Linea $2 a partire dalla fine: `tail -n $2 "$file" | head -n 1`
            done
        fi
        exit 1
    else 
        # controllo nel caso sia una file, il numero di righe 
        if test ! -f $i -o ! -r $i
        then 
            exit 2
        else 
            # se file controllo che le linee siano > X
            n=`wc -l < $i`
            if test "$n" -lt "$2"
            then
                exit 3
            fi
        fi
    fi
done
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
```shell
  
```
```shell
  
```
