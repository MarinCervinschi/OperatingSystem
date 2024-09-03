#!/bin/sh
#File FCR.sh

G=$1 #salvo il nome della gerarchia in una variabile per comodita'

# mi sposto nella gerarchia passata come parametro
cd $G

X=$2 # salvo la lunghezza in caratteri da cercare in una variabile
C=$3 # salvo il numero multiplo in una variabile 
TMP=$4 # salvo il nome del file temporaneo in una variabile

trovato=0 # variabile per tenere traccia se ho almeno un file che ripetta le condizioni

for F in *
do
    # controllo che sia una file leggibile
    if test -f $F -a -r $F
    then
        LENGTH=`wc -m < $F` # salvo la lunghezza in caratteri del file in una variabile
        if test $LENGTH -eq $X # se la lunghezza e' uguale al numero X
        then
            if test `expr $X % $C` -eq 0 # se e' multiplo di C
            then
                echo `pwd`/$F >> $TMP
                trovato=1
            fi
        fi
    fi
done

# se ho trovato almeno un file stampo il nome assoluto della directory
if test $trovato -eq 1
then
    echo "************************************"
    echo "Sono [`pwd`] e sono buono"
    echo "************************************\n"
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $X $C $TMP
    fi
done



