#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1, deve essere un numero X dispari > 0
expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $1 non strettamente positivo
        exit 2
    fi
    # Verifico che il parametro sia un numero dispari
    if test `expr $1 % 2` -eq 0
    then
        echo Error: $1 pari, deve essere dispari
        exit 3
    else
        echo DEBUG-OK: $1 dispari
    fi
else
    echo ERROR: $1 non numerico
    exit 4
fi
X=$1 # variabile del testo

shift # mi sposto in avanti di 1 con il cursore

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 5
        fi;;
    *) echo Error: $G non in forma assoluta; exit 6;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# chiamate ricorsiva per esplorare le gerarchie
for G
do
    echo "fase per $G \n"
    FCR.sh $G $X
done