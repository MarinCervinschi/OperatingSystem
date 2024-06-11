#!/bin/sh
#File FCR.sh

G=$1
C=$2
temp=$3

# mi sposto nella gerarchia passata come parametro
cd $G
cont=0 # variabile per contare i file che soddisfano la specifica.

case $G in
*/$C?$C)	
    for F in *
    do
        # se file leggibile
        if test -f $F -a -r $F
        then
            cont=`expr $cont + 1`
        fi
    done

    if test $cont -gt 0
    then
        echo "Directory trovata con nome assoluto `pwd`"
        pwd >> $temp
    fi;;
esac

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $C $temp
    fi
done