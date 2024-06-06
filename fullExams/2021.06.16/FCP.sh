#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <num1 > 0> <num2 > 0> </dir> <dir> ..."
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo che il primo parametro sia numero positivo
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

H=$1 # variabile del testo

# controllo che il secondo parametro sia numero positivo
expr $2 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $2 -le 0 # controllo che il numero sia positivo
    then
        echo ERROR: $2 non strettamente positivo
        exit 4
    fi
else
    echo ERROR: $2 non numerico
    exit 5
fi

M=$2 # variabile del testo

shift # rimuovo il primo parametro
shift # rimuovo il secondo parametro

# controllo la validità delle gerarchie
for G 
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 6
        fi;;
    *) echo Error: $G non in forma assoluta; exit 7;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

for Q
do
    echo Fase per $Q
    FCR.sh $Q $H $M
done

