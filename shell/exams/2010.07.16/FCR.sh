#!/bin/zsh
#File FCR.sh

G=$1
D=$2
H=$3

# mi sposto nella gerarchia
cd $G


files=

# se esiste una directory di nome D
if test -d $D
then
    # mi sposte nella directory
    # itero sul contenuto
    for f in *
    do
        if test -f $f -a -r $f # se file leggibile
        then
            if test $H -eq `wc -l < $f` # controllo il numero di righe, deve essere uguale a H
            then
                files="$files $f" # salvo i file per la parte c
            fi
        fi
    done
    cd ..
fi

if test "$files"
then
    echo TROVATO DIRETTORIO `pwd`/$D
    echo CHIAMO PARTE C
    partec $file $H
fi

# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $D $H
    fi
done