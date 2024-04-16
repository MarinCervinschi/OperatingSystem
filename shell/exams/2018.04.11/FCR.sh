#!/bin/zsh
#File FCR.sh

# creao delle variabili per i parametri
Y=$1
G=$2
F=$3

# itero sul contenuto della directory
for f in *
do
    # controllo se file leggibile
    if test -f $f -a -r $f
    then
        # conto il numero di linee
        NR=`wc -l < $f`
        if test $NR -ge $Y # num righe >= Y
        then
            if test $NR -ge 5 # num righe >= 5 allora il file buono
            then
                # creo il file con la 5 riga e aggiungo il file al file tmp
                head -5 $f | tail -1 > $f.quinta
                echo `pwd`/$f.quinta >> $F 
            else
                # non abbastanza linee, aggiungo il file al file tmp
                > $f.NOquinta
                echo `pwd`/$f.NOquinta >> $F
            fi
        fi
    fi
done

# chiamata ricorsiva per le sotto-directory
for i in *
do
    if test -d $i -a -x $i
    then
        $0 $Y $i $F
    fi
done