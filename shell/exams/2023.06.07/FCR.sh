#!/bin/zsh
#File FCR.sh

G=$1
X=$2
livello=$3

# mi sposto nella gerarchia
cd $G

#Aumento di livello perché sono entrato in una cartella
livello=`expr $livello + 1`

# se siamo al livello richiesto stampo il suo nome assoluto
if test $livello -eq $X
then
    echo Cartella trovata : `pwd`
    file_leggibili=
    for F in *
    do
        #Se leggibile e non vuoto
        if test -f "$F" -a -r "$F" -a -s "$F"
        then
            file_leggibili="$file_leggibili $F"
        fi
    done
    #Se ho trovato almeno un file
    if test "$file_leggibili"
    then
        echo Chiamerei main.c con $file_leggibili
    else
        echo Nessun file a specifica, non chiamo main.c
    fi
    exit 0
fi

#Se dobbiamo ancora arrivare al livello desiderato
if test $livello -lt $X
then
    # chiamata ricorsiva per le sottodirectory
    for F in *
    do
        if test -d $F -a -x $F
        then
            FCR.sh $G $X 
        fi
    done
fi
