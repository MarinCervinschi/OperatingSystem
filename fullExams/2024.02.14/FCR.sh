#!/bin/sh
#File FCR.sh

G=$1 # variabile del testo
X=$2 # variabile del testo

# mi sposto nella gerarchia passata come parametro
cd $G

shift # tolgo il primo parametro
shift # tolgo il secondo parametro

# ora in $* ho le stringhe

files= # variabile per salvare i file che rispettano i criteri

for F in *
do
    # controllo che sia un file leggibile
    if test -f $F -a -r $F
    then
        NL=`wc -l < $F` # numero di righe del file
        if test $NL -ge $X # controllo che il numero di righe sia maggiore o uguale a X
        then
            files="$files $F" # aggiungo il file alla lista
        fi
    fi
done

# cotrollo se ho trovato dei file

if test "$files"
then
    echo "Sono `pwp` e ho trovato almeno un file leggibile con lunghezza in linee maggiore o uguale a $X"
    # per ogni file trovato
    for F in $files
    do
        echo DEBUG-CHIAMO PARTE C con file $F e $*
        main $F $*
    done
fi

# chiamata ricorsiva per le sotto-directory
for G in *
do
    # se directory traversabile
    if test -d $G -a -x $G
    then
        FCR.sh `pwd`/$G $X $*
    fi
done
