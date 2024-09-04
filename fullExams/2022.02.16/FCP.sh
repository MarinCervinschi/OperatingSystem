#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo "ERROR: numero di paramtri [$#] non accettabile"
        echo "Uso: $0 <char> </ger1> ... </gerN>"
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac

# controllo che il primo carattere sia un char minuscolo
case $1 in
[a-z])	echo DEBUG-OK: primo parametro;;
*)	echo $1 non singolo carattere o non minuscolo; exit 2;;
esac
#salviamo il parametro: il nome della variabile da usare era specificato nel testo
C=$1

shift

# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 3
        fi;;
    *) echo Error: $G non in forma assoluta; exit 4;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
:> /tmp/nomiAssoluti

# chiamate ricorsiva per esplorare le gerarchie
for G
do
    echo fase per $G
    FCR.sh $G $C /tmp/nomiAssoluti
done

N=`wc -l < /tmp/nomiAssoluti` # N variabile del testo

if test $N -ge 2
then
    echo DEBUG-CHIAMO PARTE C con file `cat /tmp/nomiAssoluti`
    #main `cat /tmp/nomiAssoluti` $C
fi

#cancello il file temporaneo
rm /tmp/nomiAssoluti
