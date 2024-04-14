#!/bin/zsh
#File FCR.sh

G=$1
F=$2
T=$3

# mi sposto nella gerarchia
cd $G

# controllo se esiste un file leggibile di nome F
if test -f $F -a -r $F
then
    sort -f < $F > sorted # creao un file ordinato sorted senza tenere contro delle maiuscole e minuscole
    echo `pwd`/sorted >> $T # riporto il nome assoluto del file nel file temporaneo
fi

# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $F $T
    fi
done
