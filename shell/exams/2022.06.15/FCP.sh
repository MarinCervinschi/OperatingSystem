#!/bin/sh
#File FCP.sh

# controllo il numero dei parametri
case $# in
0|1|2) 	echo ERROR: numero di paramtri non accettabile
        exit 1;;
*)		echo DEBUG-OK: numero di parametri corretto;;
esac


# controllo la validità delle gerarchie
for G
do
    # se sono in forma assoluta controllo che siano directory e traversabile
    case $G in
    /*) if test ! -d $G -o ! -x $G
        then
            echo Error: $G non directory o non traversabile
            exit 2
        fi;;
    *) echo Error: $G non in forma assoluta; exit 3;;
    esac
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

# creo un file temporaneo
> /tmp/nomiAssoluti

# chiamate ricorsiva per esplorare le gerarchie
for G
do
    echo "fase per $G \n"
    FCR.sh $G /tmp/nomiAssoluti
done

# variabile del testo per contare i file trovati
N=`wc -l < /tmp/nomiAssoluti`

echo Abbiamo trovato in totale $N file con solo caratteri minuscoli

# invoco la parte c
echo main.c 
#`cat /tmp/nomiAssoluti`

#cancello il file temporaneo
rm /tmp/nomiAssoluti