#!/bin/sh
#File FCR.sh

G=$1
X=$2
TMP=$3

# mi sposto nella gerarchia passata come parametro
cd $G

trovato=0 # variabile controllare se ho trovato almeno un file

for F in *
do # ATTENZIONE 'F' e' la variabile del testo
    # controllo che sia un file leggibile
    if test -f $F -a -r $F
    then
        NL=`wc -l < $F` # numero di righe del file
        if test $NL -ge $X # controllo che il numero di righe sia maggiore o uguale a X
        then
            if test $NL -lt 255 # controllo che il numero di righe sia strettamente minore di 255
            then
                echo `pwd`/$F >> $TMP # salvo il nome assoluto sul file temporaneo
                trovato=1 # aggiorno la variabile che ho trovato almeno un file
            fi
        fi
    fi
done

# cotrollo se ho trovato almeno un file
if test $trovato -eq 1
then
    echo "SONO UN DIRETTORIO VALIDO [`pwd`]"
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $X $TMP
    fi
done