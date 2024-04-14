#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1, deve essere il nome assoluto di una directory
# se è in forma assoluta controllo che sia directory e traversabile
case $1 in
/*) if test ! -d $1 -o ! -x $1
    then
        echo Error: $1 non directory o non traversabile
        exit 2
    fi
*) echo Error: $1 non in forma assoluta; exit 3;;
esac
G=$1 # nome del testo

# controllo $2, deve essere
case $2 in
*/*)    echo Errore: $2 non in forma relativa semplice; exit 4;;
*)      if test ! -d $2 # se in forma semplice controllo se directory
        then
            echo ERROR: non directory
            exit 5
        fi;;
esac
D=$2 # nome del testo

expr $3 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $3 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $3 non strettamente positivo
        exit 6
    fi
else
    echo ERROR: $3 non numerico
    exit 7
fi
H=$3 # nome del testo

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

FCr.sh $G $D $H