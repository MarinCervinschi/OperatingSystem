#!/bin/sh
#File FCR.sh

cd $1
# il primo livello verra' contato come livello 1
conta=`expr $3 + 1`  # variabile conta LOCALE a questo script

# ci serve per raccogliere i nomi dei file leggibili NON vuoti
files=

if test `expr $conta % 2` -eq 0 # siamo al livello pari e quindi bisogna raccogliere i nomi di tutti i file leggibili non vuoti
then
    echo "TROVATA dir `pwd` che si trova a un livello pari"
    for F in *  # F variabile indicata dal testo
    do
        if test -f $F -a -r $F
        then
            if test `wc -l < $F` -eq $2 # se il file ha esattamente $2 righe
            then
              files="$files $F" # aggiungo il file alla lista
            fi
        fi
    done
    # se ho trovato almeno un file
    if test "$files"
    then
        echo DEBUG-CHIAMO PARTE C con file $files
        main $files
    else
        echo NESSUN file che soddisfa le specifiche e quindi niente chiamata parte C
    fi
fi

for i in *
do
    if test -d $i -a -x $i
    then
        # echo RICORSIONE in `pwd`/$i  con terzo paramentro uguale a $conta
        FCR.sh `pwd`/$i $2 $conta
    fi
done