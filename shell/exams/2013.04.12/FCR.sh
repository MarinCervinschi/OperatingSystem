#!/bin/sh
#File FCR.sh

G=$1
S=$2
T=$3

# mi sposto nella gerarchia
cd $G

#la variabile trovato ci serve per capire se abbiamo trovato almeno un file
#leggibile con la terminazione richiesta
trovato=0

# fase A
for i *
do
    # controllo solo i file leggibili
    if test $flag = "A"
    then
        if test -f $i -a -r $i
        then
            case $i in
            *.$2) trovato=1;;
            esac
            if test $trovato -ne 0
            then
                break
            fi
        fi
    fi
    
done
if test $trovato -eq 1
then
    #abbiamo trovato un direttorio che soddisfa le specifiche e quindi inseriamo il suo
    #nome assoluto nel file temporaneo
    pwd >> $T
fi

# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $S $T
    fi
done