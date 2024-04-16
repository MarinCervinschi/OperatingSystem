#!/bin/zsh
#File FCR.sh

# definisco delle variabili per i parametri passati
G=$1
S=$2
F=$3

# mi sposto nella gerarchia
cd $G

# se esiste il file leggibile e scrivibile di nome S.txt
if test -f $S.txt -a -r $i -a -w $S.txt
then
    # inserisco nel file tmp il nome assoluto e il numero di caratteri del file
    echo `wc -c < $S.txt` `pwd`/$S.txt >> $F
fi

# chiamata ricorsiva per le sotto-directory della gerarchia
for i in *
do
    if test -d $i -a -x $i
    then
        $0 `pwd`/$i $S $F
    fi   
done