#!/bin/zsh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2|3)    echo ERROR: numero di paramtri non accettabile
            exit 1;;
*)          echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo $1, deve essere 0 < X < 4
expr $1 + 0  > /dev/null 2>&1
N1=$?
if test $N1 -ne 2 -a $N1 -ne 3
then # in questo caso è certamente numerico
    if test $1 -le 0 -o $1 -ge 4 # controllo che il numero sia 0 < X < 4
    then
        echo ERROR: $1 non strettamente positivo o non strettamente minore di 4
        exit 2
    fi
else
    echo ERROR: $1 non numerico
    exit 3
fi
X=$1 # nome indicato nel testo

# sposto il cursone in avanti di uno
shift 

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 4
        fi
    *) echo Error: $G non in forma assoluta; exit 5;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

livello=0

# esploro le Q gerarchie tramite il file ricorsivo FCR.sh
for G
do
    echo fase per $G
    FCR.sh $G $X $livello
done
