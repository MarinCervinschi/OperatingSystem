#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
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
X=$1 # ATTENZIONE 'X' e' la variabile del testo

shift # sposto il cursore in avanti di uno

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 4
        fi;;
    *) echo Error: $G non in forma assoluta; exit 5;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# chiamate ricorsiva per esplorare le gerarchie
for G # ATTENZIONE 'G' e' la variabile del testo
do
    echo fase per $G
    echo "*******************************************"
    FCR.sh $G $X
done