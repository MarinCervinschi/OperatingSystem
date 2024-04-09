#!/bin/zsh
#File FCR.sh

G=$1
C=$2
F=$3

# mi sposto nella gerarchia
cd $G

# scrivo il nome assoluto della dir nel file tmp
case $i in
*/$C?$C) pwd >> $F;; 
*);;
esac

# chiamata ricorsiva per le sotto-directory della gerarchia
for i in *
do
    if test -d $i -a -x $i
    then
        $0 `pwd`/$i $C $F
    fi   
done