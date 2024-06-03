#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <parametro1> <parametro2> ..."
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    # controllo che il numero sia strettamente positivo e strettaente minore di 4
    if test $1 -le 0 -o $1 -ge 4
    then
        echo ERROR: $1 non strettamente positivo o strettamente minore di 4
        exit 2
    fi
else
    echo ERROR: $1 non numerico
    exit 3
fi

X=$1 # salvo il primo parametro (variabile X del testo)

shift # elimino il primo parametro

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

for Q
do
    echo fase per $Q
    # chiama lo script FCR.sh con i parametri X e Q e 0 rappresenta il livello 0
    ./FCR.sh $Q $X 0
done

