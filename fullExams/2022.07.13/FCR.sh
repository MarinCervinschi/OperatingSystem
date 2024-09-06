#!/bin/sh
#File FCR.sh

G=$1
L=$2
TMP=$3

shift
shift
shift

# adesso il mio cursore punta al primo singolo carattere passato

# mi sposto nella gerarchia passata come parametro
cd $G

trovato=0

for F in *
do
    # controllo che sia un file leggibile
    if test -f $F -a -r $F
    then
        NL=`wc -l < $F` # numero di righe del file
        if test $NL -eq $L # controllo che il numero di righe sia uguale a L
        then
            for i # per ogni carattere in $* 
            do
                grep "$i" $F > /dev/null 2>&1 # controllo se esiste un'occorenza nel file
                if test $? -eq 0
                then
                    trovato=1
                else
                    trovato=0
                    break
                fi
            done
            if test $trovato -eq 1 # se ho trovato almeno un file
            then
                echo "SONO UN FILE BUONO - [$F]"
                echo `pwd`/$F >> $TMP
                trovato=0
            fi
        fi
    fi
done

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $L $TMP $*
    fi
done
