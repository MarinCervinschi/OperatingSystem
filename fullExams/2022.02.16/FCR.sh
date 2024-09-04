#!/bin/sh
#File FCR.sh

G=$1 # salvo la gerarchia in una variabile
C=$2 # salvo il carattere da cercare in una variabile
TMP=$3 # salvo il file temporaneo in una variabile

# mi sposto nella gerarchia passata come parametro
cd $G

trovato=0 # variable per tenere traccia se ho trovato almeno un file nella dir corrente

for F in *
do
    if test -f $F -a -r $F # se file leggibile
    then
        grep "$C" $F > /dev/null 2>&1
        if test $? -eq 0
        then
            echo `pwd`/$F >> $TMP
            trovato=1
        fi
    fi
done

# se ho trovato almneo un file stampo la dir corrente
if test $trovato -eq 1
then
    echo "Sono [`pwd`] e sono valido"
fi

# chiamata ricorsiva per le sotto-directory
for D in *
do
    # se directory traversabile
    if test -d $D -a -x $D
    then
        FCR.sh `pwd`/$D $C $TMP
    fi
done