#!/bin/zsh
#File FCR.sh

# dichiaro delle variabili per i parametri passati
G=$1
H=$2
M=$3

# mi sposto nella directory interessata
cd $G

# variabile per tenere traccia del numero di file trovati
cont=0

# variabile per tenere traccia dei nomi dei file trovati
files=

for F in * # nome del testo
do
    # se file
    if test -f $F
    then
        # controllo la lunghezza del nome del file
        case $F in
        ??) 
            # contro il numero di linee del file
            L=`wc -l < $F` 
            if test $L -eq $M
            then
                # aggiorno cont
                cont=`expr $cont + 1`
                # aggiungo il file ai files trovati
                files="$files $F"
            fi;;
        *)  ;;
        esac

    fi
done

# controllo se la directory rispetta le specifiche
if test $cont -lt $H -a $count -ge 2
then
    echo TROVATO directory `pwd`
    # invoco la parte in C
    echo invoco $0 $files $M
fi

# chiamata ricorsiva del file
for i in *
do
    if test -d $i -a -x $i
    then
        # passiamo la directory in forma assoluta
        $0 `pwd`/$i $H $M
    fi
done