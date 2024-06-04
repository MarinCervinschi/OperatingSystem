#!/bin/sh
#File FCP.sh


# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <num > 0> <gerarchia1> <gerarchia2> ..."
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo che il primo parametro sia un numero
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

X=$1 # salvo il numero di parametri (variabile X del testo)

shift # tolgo il primo parametro

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

for G
do
    echo SHELL: fase per $G
    # chiamo lo script FCP.sh passandogli i parametri X (numero) G (gerarchia) e 0 (livello)
    FCR.sh $G $X 0
done