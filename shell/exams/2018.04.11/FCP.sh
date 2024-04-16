#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2)  echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)      echo DEBUG-OK: numero di parametri corretto;;
esac

expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $1 non strettamente positivo
        exit 2
    fi
else
    echo ERROR: $1 non numerico
    exit 3
fi

Y=$1 # salvo il numero nella variabile del testo

# mi sposto in avanti di uno cosi da avere le N gerarchie in $*
shift

# controllo le N gerarchie
for i
do
    # se in forma assoluta controllo che sia directory e traversabile
    case $i in
    /*) if test ! -d $i -a ! -x $i
        then
            echo ERROR: $i non directory o non traversabile
            exit 4
        fi;;
    *) echo ERROR: non in forma assoluta; exit 5;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/tmp$$

for i
do
    echo fase per $i
    FCR.sh $Y $i /tmp/tmp$$
done

# conto i file globalmente creati
NF=`wc -l < /tmp/tmp$$`

echo Il numero totale di file creati è $NF

for i in `cat /tmp/tmp$$`
do
    # come richiesto stampo i file trovati con i dettagli del caso
    echo Create il file $i
    case $i in
    *NO*)   echo Il file non contiene almeno 5 linee e quindi il file $i è vuoto;;
    *)      echo Il contenuto del file $i è: `cat < $i``;;
    esac
done

# cancello il file temporaneo
rm /tmp/tmp$$