#!/bin/zsh
#File FCR.sh

G=$1
X=$2
T=$3

cd $G

for F in *
do
    # se file leggibile
    if test -f $F -a -r $F
    then
        NL=`wc -l < $F`
        if test $NL -eq $X # il numero di righe uguale a X
        then
            pwd/$F >> $T
        fi
    fi
done

for d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $X $T
    fi
done