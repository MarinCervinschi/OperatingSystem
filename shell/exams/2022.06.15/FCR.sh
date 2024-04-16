#!/bin/sh
#File FCR.sh

G=$1
T=$2

# mi sposto nella gerarchia passata come parametro
cd $G

for F in *
do
    # Se file leggibile e non vuoto
    if test -f "$F" -a -r "$F" -a -s "$F"
    then
        # numero di righe con almeno un carattere diverso da un carattere minuscolo
        NG=`grep '[^a-z \n]' $F | wc -l`
        if test $NG -eq 0
        then
            echo `pwd`/$F >> $T
            echo Trovato file che rispetta le specifiche : `pwd`/$F
        else
            echo File $F non contiene solo caratteri minuscoli
        fi
    fi
done

# chiamata ricorsiva per le sotto-directory
for D in *
do
    if test -d $D -a -x $D
    then
        FCR.sh `pwd`/$D $T
    fi
done