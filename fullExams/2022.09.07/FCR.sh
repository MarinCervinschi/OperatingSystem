#!/bin/sh
#File FCR.sh

G=$1
X=$2

# mi sposto nella gerarchia passata come parametro
cd $G

files= # variabile per salvare i file che rispettano i criteri
posizione=0

# ATTENZIONE 'F' e' la variabile del testo
for F in *
do
    #controlliamo solo i nomi dei file per il discorso della posizione!
    if test -f $F
    then 	
        posizione=`expr $posizione + 1`
        #ora controlliamo la leggibilita' come indicato nella specifica!
        if test -r $F
        then 	
            NC=`wc -c < $F` # numero di caratteri del file
            if test $NC -eq $X # controllo che il numero caratteri sia esattamente X
            then
                if test `expr $posizione % 2` -eq 1 # se si trova in una posizione dispari
                then
                    echo "SONO UN FILE BUONO [`pwd`/$F]"
                    files="$files $F" # aggiungo il file alla lista
                fi
            fi
        fi
    fi
done

# cotrollo se ho trovato dei file
if test "$files"
then
   echo "DEBUG-CHIAMO PARTE C con file [$files]"
   main $files
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
