#!/bin/sh
#File FCR.sh

G=$1
T=$2

# mi sposto nella gerarchia passata come parametro
cd $G

for f in *
do
    # se file leggibile
    if test -f $f -a -r $f
    then
        NumRighe=`wc -l < $f` # conto il numero totale di righe

        if test $NumRighe -ne 0 # controllo che il file non sia vuoto
        then
            NumRigheConA=`grep '^a*' | wc -l` # conto il numero di righe che cominciano con il carattere 'a'

            # se sono uguali significa che tutte le righe di questo file cominciano con il carattere 'a'
            if test $NumRighe -eq $NumRigheConA
            then
                echo `pwd`/$i >> $T # scrivo il valore assoluto del file nel file temporaneo
            fi
        fi
    fi
done

# chiamata ricorsiva per le sotto-directory
for $d in *
do
    if test -d $d -a -x $d
    then
        FCR.sh `pwd`/$d $T
    fi
done