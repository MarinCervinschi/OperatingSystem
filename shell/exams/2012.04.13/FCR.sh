#!/bin/zsh
#File FCR.sh

G=$1
LIVELLO=$2
T=$3
flag=$4
num=$5

# mi sposto nella gerarchia
cd $G

# fase A
if test $flag = "A"
then
    LIVELLO=`expr $LIVELLO + 1`
    $LIVELLO >> $T
fi

# fase B
if test $flag = "B"
then
    LIVELLO=`expr $LIVELLO + 1`
    if test $LIVELLO -eq $num # se il livello attuale = al numero passato del utente
    then
        echo sono `pwd` e queste sono le informazioni dei miei elementi
        ls -l
    fi
fi


# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $LIVELLO $T $flag $num
    fi
done