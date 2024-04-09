#!/bin/zsh
#File FCR.sh

G=$1
S=$2
T=$3

# mi sposto nella gerarchia
cd $G

# controllo se esiste un file che termini in .$S
if test -f *.$S
then
    # aggiungo la directory nel file tmp
    pwd >> $T
fi

# chiamata ricorsiva per le sotto-directory della gerarchia
for i in *
do
    if test -d $i -a -x $i
    then
        $0 `pwd`/$i $S $F
    fi   
done